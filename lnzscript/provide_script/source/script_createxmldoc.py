import sys
import os
import operator 

if len(sys.argv)>1:
	# Set the working directory to the first parameter passed to me
	d = sys.argv[1]
	os.chdir(d)

import script_create

class Section_repr():
	name = ''
	doc = ''
	namespaces = None
	def __init__(self, strName):
		self.namespaces = []
		self.name = strName

class Namespace_repr():
	name = ''
	doc = None
	sectionname = None
	functions = None
	def __init__(self,strName):
		self.functions = []
		self.name = strName
	

def createDoc():
	txt = script_create.readfile('object_documentation.cpp')
	lines = txt.replace('\r\n','\n').split('\n')
	
	#first, create section objects. In the future we may have a place to independently specify these
	sections = {}
	for line in lines:
		if line.startswith('///Section:'):
			param, sectionname = script_create.parseParamEntry(line)
			#if we haven't seen this yet, create it.
			if sectionname not in sections:
				sections[sectionname] = Section_repr(sectionname)
				sections[sectionname].doc = '' 
				print sectionname
				#no general documentation for sections yet.
			
	#now, create namespace objects
	namespaces = {}
	currentNamespace = None
	for line in lines:
		if line.strip()=='' or (line.startswith('//') and not line.startswith('///')): continue
		if line.startswith('///'):
			param, data = script_create.parseParamEntry(line)
			if param=='Namespace':
				currentNamespace = Namespace_repr(data)
			elif param=='Section':
				currentNamespace.sectionname = data
			elif param=='Enddoc':
				#rejoin lines of doc
				currentNamespace.doc = '\n'.join(currentNamespace.doc)
				
				#place in dict
				namespaces[currentNamespace.name] = currentNamespace
				#assign to its section
				if currentNamespace.sectionname==None: raise Exception, 'Error: No section designated for namespace %s',currentNamespace.name
				if currentNamespace.sectionname not in sections:  raise Exception, 'Error: section %s not found, specified by namespace %s'%(currentNamespace.sectionname, currentNamespace.name)
				sections[currentNamespace.sectionname].namespaces.append(currentNamespace)
				currentNamespace = None
			elif param=='Doc':
				#starting documentation...
				currentNamespace.doc = []
		else:
			currentNamespace.doc.append(line)
	
	#now, add all of the functions
	aFunctions = script_create.processAllSource()
	for obj in aFunctions:
		ns = obj.namespace
		if ns not in namespaces: raise Exception, 'In function %s, namespace %s does not exist.'%(obj.functionname, obj.namespace)
		namespaces[ns].functions.append(obj)
	

	if len(sys.argv)>2:
		# Set the working directory to the second parameter passed to me
		d = sys.argv[2]
		os.chdir(d)
	
	#finally, write the xml
	fout = open(r'documentation.xml','w')
	fout.write('<?xml version="1.0" encoding="UTF-8"?>')
	fout.write('<?xml-stylesheet type="text/xsl" href="viewdoc.xsl"?>')
	fout.write('<launchorzdoc version="0.4">')
	
	i = 0
	#actually, don't sort the keys, so that "launchors" is before "language"
	for key in sections.keys():
		section = sections[key]
		fout.write('<section name="%s">'%xmlescape(section.name))
		if section.doc: fout.write('<section_doc>%s</section_doc>'%xmlescape(section.doc))
		for namespace in sorted(section.namespaces, key=operator.attrgetter('name')):
			fout.write('<namespace name="%s">'%xmlescape(namespace.name))
			if namespace.doc: fout.write('<namespace_doc>%s</namespace_doc>'%xmlescape(namespace.doc))
			for function in sorted(namespace.functions, key=operator.attrgetter('functionname')):
				i+=1
				if function.functionname.startswith('_'): continue #this is an undocumented function; don't include it.
				function.args = function.args.replace('INTDEFAULT','default')
				function.args = function.args.replace('string window','string strWindow')
				
				if function.instanceMethod==True: sInstanceParam = ' instance="true" '
				else: sInstanceParam = ''
				fout.write('<function name="%s" args="%s" returns="%s" impl="%s"%s>'%(xmlescape(function.functionname),xmlescape(function.args),xmlescape(function.returns),xmlescape(function.implementation),sInstanceParam))
				if function.doc: fout.write('<doc>%s</doc>'%xmlescape(function.doc))
				if function.example: fout.write('<example>%s</example>'%xmlescape(function.example))
				fout.write('</function>')
			fout.write('</namespace>')
		
		fout.write('</section>')
	
	fout.write('</launchorzdoc>')
	fout.close()
	print len(aFunctions), i
	

def xmlescape(s):
	return s.replace('\r\n','\n').replace('\n','[[br]]').replace('&','&amp;').replace('<','&lt;').replace('>','&gt;').replace('"','&quot;').replace("'",'&apos;')
	
def main():
	print
	createDoc()
	
main()