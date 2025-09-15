import sys
import os

try:
	import io
except ImportError:
	import StringIO as io

# Set the working directory to the first parameter passed to me
d = sys.argv[1]
os.chdir(d)

import script_create


def main():

	#parse files
	aMethods = script_create.processAllSource()

	os.chdir('..')
	# generate c++ headers and code
	objConnections = ConnectionToScriptOutputFile('functions_expose')
	objCppAu3 = ImplementationOutputFile('functions_au3')
	objCppQt = ImplementationOutputFile('functions_qt')
	objCppWinext = ImplementationOutputFile('functions_winext')
	for method in aMethods:
		if method.implementation == 'c++_au3':
			objCppAu3.addHeader(method.renderHeader())
			objCppAu3.addCode(method.renderCode())
			objConnections.addMethod(method)
		elif method.implementation == 'c++_qt':
			objCppQt.addHeader(method.renderHeader())
			objCppQt.addCode(method.renderCode())
			objConnections.addMethod(method)
		elif method.implementation == 'c++_winext':
			objCppWinext.addHeader(method.renderHeader())
			objCppWinext.addCode(method.renderCode())
			objConnections.addMethod(method)
		elif method.implementation == 'Javascript':
			pass
		else:
			assert False, 'unknown impl ' + method.implementation

	objCppQt.writeFile()
	objCppAu3.writeFile()
	objCppWinext.writeFile()
	objConnections.writeFile()


def alreadyExists(strFilename, strWholeFile):
	#if the exact same file already exists, don't write it. The main advantage is that the file isn't "touched" and gcc won't rebuild it.
	if not os.path.exists(strFilename):
		return False
	strWholeExistingFile = script_create.readfile(strFilename)
	return strWholeFile == strWholeExistingFile


class ImplementationOutputFile(object):
	outHeaders = None
	outCode = None
	strFilename = None

	def __init__(self, strFilename):
		self.outHeaders = io.StringIO()
		self.outCode = io.StringIO()
		self.strFilename = strFilename
		print(
			'\n',
			'//THIS IS A GENERATED FILE Do not make changes to this file - they will be overwritten',
			'\n',
			file=self.outCode
		)

	def addHeader(self, s):
		print(s, file=self.outHeaders)

	def addCode(self, s):
		print(s, file=self.outCode)

	def writeFile(self, dictCustomReplacements=None):
		strTemplate = script_create.readfile(self.strFilename + '.cpp.template')

		if dictCustomReplacements:
			for key in dictCustomReplacements:
				strTemplate = strTemplate.replace(key, dictCustomReplacements[key])
		strTemplate = strTemplate.replace('%%%INSERT_FUNCTIONS_HERE%%%', self.outCode.getvalue())
		if not alreadyExists('./gen/' + self.strFilename + '.cpp', strTemplate):
			fout = open('./gen/' + self.strFilename + '.cpp', 'w')
			fout.write(strTemplate)
			fout.close()

		strTemplate = script_create.readfile(self.strFilename + '.h.template')
		strTemplate = strTemplate.replace('%%%INSERT_HEADERS_HERE%%%', self.outHeaders.getvalue())
		if not alreadyExists('./gen/' + self.strFilename + '.h', strTemplate):
			fout = open('./gen/' + self.strFilename + '.h', 'w')
			fout.write(strTemplate)
			fout.close()


class ConnectionToScriptOutputFile(object):
	nameSpacesSeen = None
	outConnection = None
	strFilename = None

	def __init__(self, strFilename):
		self.outConnection = io.StringIO()
		self.nameSpacesSeen = {}
		self.strFilename = strFilename

	def addMethod(self, objMethod):
		self.nameSpacesSeen[objMethod.namespace] = 1
		print(
			'obj%s.setProperty("%s", eng->newFunction(%s));' %
			(objMethod.namespace, objMethod.functionname, objMethod.getImplName()),
			file=self.outConnection
		)

	def writeFile(self):
		strOut = ''
		strOut += '\n\t' + self._renderNamespaceCode()
		strOut += '\n\t' + self.outConnection.getvalue()
		strOut += '\n\t' + script_create.readfile('./source/object_properties.cpp') #flags like Window.MAXIMIZE

		strTemplate = script_create.readfile(self.strFilename + '.cpp.template')
		strTemplate = strTemplate.replace('%%%INSERT_PROPERTY_CREATION_HERE%%%', strOut)
		if not alreadyExists('./gen/' + self.strFilename + '.cpp', strTemplate):
			fout = open('./gen/' + self.strFilename + '.cpp', 'w')
			fout.write(strTemplate)
			fout.close()

	def _renderNamespaceCode(self):
		sConnections = ''
		for namespace in self.nameSpacesSeen:
			sConnections += '\n\t QScriptValue obj%s = eng->newObject();' % namespace #create object
			sConnections += '\n\t eng->globalObject().setProperty("%s",obj%s);' % (namespace, namespace) #expose object
		return sConnections


main()
