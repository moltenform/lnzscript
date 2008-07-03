import sys
import os

import StringIO

# Set the working directory to the first parameter passed to me
d = sys.argv[1]
os.chdir(d)

import script_create


def main():
	#check if I even need to generate this.
	#newestSource = 0, os.stat, st_mtime 
	
	#parse files
	aMethods = script_create.processAllSource()
	
	
	# generate c++ headers and code
	objConnections = ConnectionToScriptOutputFile()
	objCppAu3 = ImplementationOutputFile('../functions_au3')
	objCppQt = ImplementationOutputFile('../functions_qt')
	objCppNircmd = ImplementationOutputFile('../functions_nircmd')
	for method in aMethods:
		if method.implementation == 'c++_au3':
			objCppAu3.addHeader(method.renderHeader())
			objCppAu3.addCode( method.renderCode())
			objConnections.addMethod(method)
		elif method.implementation == 'c++_qt':
			objCppQt.addHeader(method.renderHeader())
			objCppQt.addCode( method.renderCode())
			objConnections.addMethod(method)
		elif method.implementation == 'c++_nircmd':
			objCppNircmd.addHeader(method.renderHeader())
			objCppNircmd.addCode( method.renderCode())
			objConnections.addMethod(method)
	
	objCppQt.writeFile()
	objCppNircmd.writeFile()
	objCppAu3.writeFile( {'%%%INSERT_PROPERTY_CREATION_HERE%%%' : objConnections.render() })
	



class ImplementationOutputFile():
	outHeaders =None
	outCode=None
	strFilename = None
	def __init__(self, strFilename):
		self.outHeaders = StringIO.StringIO()
		self.outCode = StringIO.StringIO()
		self.strFilename = strFilename
		print >>self.outCode,'\n','//THIS IS A GENERATED FILE Do not make changes to this file - they will be overwritten','\n'
	def addHeader(self, s):
		print >> self.outHeaders,s
	def addCode(self, s):
		print >> self.outCode, s
	
	def writeFile(self, dictCustomReplacements = None): 
		strTemplate = script_create.readfile(self.strFilename+'.cpp.template')
		
		if dictCustomReplacements:
			for key in dictCustomReplacements: strTemplate=strTemplate.replace(key, dictCustomReplacements[key])
		strTemplate = strTemplate.replace('%%%INSERT_FUNCTIONS_HERE%%%', self.outCode.getvalue())
		if not self._alreadyExists(self.strFilename+'.cpp', strTemplate):
			fout = open(self.strFilename+'.cpp', 'w')
			fout.write(strTemplate)
			fout.close()
		
		strTemplate = script_create.readfile(self.strFilename+'.h.template')
		strTemplate = strTemplate.replace('%%%INSERT_HEADERS_HERE%%%', self.outHeaders.getvalue())
		if not self._alreadyExists(self.strFilename+'.h', strTemplate):
			fout = open(self.strFilename+'.h', 'w')
			fout.write(strTemplate)
			fout.close()

	def _alreadyExists(self, srtFilename, strWholeFile):
		#if the exact same file already exists, don't write it. The main advantage is that the file isn't "touched" and gcc won't rebuild it.
		strWholeExistingFile = script_create.readfile(srtFilename)
		return strWholeFile==strWholeExistingFile


class ConnectionToScriptOutputFile():
	nameSpacesSeen = None
	outConnection = None
	def __init__(self):
		self.outConnection = StringIO.StringIO()
		self.nameSpacesSeen = {}
	def addMethod(self, objMethod):
		self.nameSpacesSeen[objMethod.namespace] = 1
		print >>self.outConnection, 'obj%s.setProperty("%s", eng->newFunction(%s));' %(objMethod.namespace, objMethod.functionname, objMethod.getImplName())
	def render(self):
		strOut = ''
		strOut += '\n\t' + self._renderNamespaceCode()
		strOut += '\n\t' + self.outConnection.getvalue()
		strOut += '\n\t' + script_create.readfile('object_properties.cpp') #flags like Window.MAXIMIZE
		return strOut
		
	def _renderNamespaceCode(self):
		sConnections = ''
		for namespace in self.nameSpacesSeen:
			sConnections += '\n\t QScriptValue obj%s = eng->newObject();'%namespace #create object
			sConnections += '\n\t eng->globalObject().setProperty("%s",obj%s);'%(namespace,namespace) #expose object
		return sConnections

main()