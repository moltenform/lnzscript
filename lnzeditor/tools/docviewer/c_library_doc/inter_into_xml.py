import os,sys
try:
	os.chdir('input_files')
except:
	print 'cannot find directory input_files. try unzipping the inputfiles.zip.'
	sys.exit(1)

order = '''math.gen.txt
memory.gen.txt
strings.gen.txt
io.gen.txt
files.gen.txt
sys.gen.txt
time.gen.txt
misc.gen.txt
'''.replace('\r\n','\n').split('\n')
files=[file for file in os.listdir('.') if file.endswith('.gen.txt')]
for file in files: 
	if file not in order: raise Exception, 'File '+file+' not in order.'


def main():
	fout = open('..\\cdoc.xml','w')
	fout.write('<?xml version="1.0" encoding="UTF-8"?>')
	fout.write('<?xml-stylesheet type="text/xsl" href="viewdoc.xsl"?>')
	fout.write('<launchorzdoc library="c" version="1.0">')
	fout.write('<!-- from eric huss, http://www.acm.uiuc.edu/webmonkeys/book/c_guide/ -->')
	fout.write('<!-- processed into xml by Ben Fisher -->')
	fout.write('<section name="C">')
	
	for filename in order:
		if filename:
			print filename
			alltxt = open(filename,'r').read()
			alltxt = alltxt.replace('<!!!>','')
			
			nsname = getname(alltxt, filename)
			fout.write('<namespace name="%s">'%nsname)
			process(alltxt, fout)
			fout.write('</namespace>')

	fout.write('</section>')
	#other sections could be GNU extensions, c99 , and so on
	fout.write('<section name="tables">')
	fout.write('<namespace name="ASCII table" empty="true"><namespace_doc>')
	fout.write(open('ascii_table.txt','r').read())
	fout.write('</namespace_doc></namespace>')
	fout.write('</section>')
	
	fout.write('</launchorzdoc>')
	fout.close()

import re
reGsec = re.compile(r'===Section:([^=]+)=')
def getname(alltxt, filename):
	#~ m = reGsec.match(alltxt)
	#~ if '===Section:' in alltxt: print 'secthe'
	#~ if not m: raise Exception, 'no section title found.'
	#~ print str(m.group(1))
	#~ return str(m.group(1))
	return {
'math.gen.txt' : 'Math',
'memory.gen.txt' : 'Memory',
'strings.gen.txt' : 'Strings',
'io.gen.txt' : 'IO',
'files.gen.txt' : 'Files',
'sys.gen.txt' : 'System',
'time.gen.txt' : 'Time',
'misc.gen.txt' : 'Misc',
	} [filename]

def process(alltxt, fout):
	alltxt = alltxt.replace('\r\n','\n').split('\n')
	results = []
	
	lastName = lastProto=lastHeader=lastDoc = ''
	state = 'outside' #one of outside/proto/header/doc
	
	for line in alltxt:
		if line.startswith('===Section:'): continue
		elif line=='---!header':
			state = 'header'
		elif line=='---!doc':
			state = 'doc'
		elif line=='---!end':
			results.append(FnRepr(lastName , lastProto,lastHeader,lastDoc))
			lastName = lastProto=lastHeader=lastDoc = ''
			state='outside'
		elif line.startswith('---'):
			lastName = line.replace('---:','').replace('---','')
			state='proto'
		else:
			if state=='proto': lastProto+='\n'+line
			elif state=='header': lastHeader+='\n'+line
			elif state=='doc': lastDoc+='\n'+line
	
	for res in results:
		fout.write(res.toXml())
		
def xmlescape(s):
	return s.replace('&','&amp;').replace('<','&lt;').replace('>','&gt;').replace('"','&quot;').replace("'",'&apos;')


class FnRepr():
	name = ''
	syntax = ''
	header = ''
	doc = ''
	def __init__(self, name,syntax,header,doc):
		self.name=name.strip()
		self.syntax=syntax.strip()
		self.header=header.strip()
		self.doc=doc.strip()
	
	def toXml(self):
		s = ''
		s+='<function name="%s" fullsyntax="%s">' % (xmlescape(self.name),xmlescape(self.syntax))
		sdoc = xmlescape('('+self.header+'). '+self.doc)
		s+='<doc>%s</doc>'% sdoc
		s+='</function>'
		
		return s
		
main()