
import sys
import iface_verifydocs

class PrintToFile():
	def __init__(self, fname):
		self.f=open(fname,'w')
	def write(self, string):
		self.f.write(string)
	def close(self):
		self.f.close()

from iface_get import iface_get

def go(starget, starget2, targettable):
	stdoutStd = sys.stdout
	stdoutFile = PrintToFile('docs_out.txt')
	
	sys.stdout = stdoutFile
	print '''
# Constants, from IFaceTable.cxx
ScApp.SCFIND_WHOLEWORD
ScApp.SCFIND_MATCHCASE 
ScApp.SCFIND_WORDSTART 
ScApp.SCFIND_REGEXP
ScApp.SCFIND_POSIX
...many others...

# ScApp methods
ScApp.Trace(s)
ScApp.MsgBox(s)
ScApp.OpenFile(s)
ScApp.GetProperty(s)
ScApp.SetProperty(s, v)
ScApp.UnsetProperty(s)
ScApp.UpdateStatusBar(bUpdateSlowData)

# Menu commands'''
	f=open(starget2,'r')
	isStart=False
	out = []
	for line in f:
		if not isStart:
			if 'rgFriendlyNamedIDMConstants[] =' in line:
				isStart = True
		else:
			if '};' in line:
				break
			else:
				out.append(line.split('",')[0].replace('{"',''))
	assert isStart
	for part in out:
		#~ print 'void\tScApp.fn'+part+'()'
		print 'ScApp.'+part+'()'
	f.close()
	
	print '''
# Pane methods (all apply to ScOutput as well)
ScEditor.Append(txt)
ScEditor.Insert(npos, txt)
ScEditor.Remove(npos1, npos2)
ScEditor.Textrange(npos1, npos2)
ScEditor.FindText(s,n1=0,n2=-1,wholeWord=False,matchCase=False,regExp=False, nFlags=0)

	'''
	
	sys.stdout = stdoutStd
	
	out = iface_verifydocs.go(target, targettable,modifyEntries = True)
	sys.stdout = stdoutFile
	
	for o in out:
		#~ if o.name=='AddRefDocument': continue ???
		
		if o.type == 'get':
			assert o.name.startswith('Get')			
		if o.type == 'set':
			assert o.name.startswith('Set')
		
		sname = o.name
		if 'stringresult' not in o.args:
			rettype=o.returntype.replace('position','pos')
			print rettype + '\tScEditor.'+sname + o.args.replace(',)',')')
		else:
			assert o.returntype=='int'
			sargs = o.args.split(',')[0] + ')'
			
			print 'string' + '\tScEditor.'+ sname+ sargs
		
		if o.docs: print o.docs.replace('#','')
	
	
	
	stdoutFile.close()


#~ target = r'C:\pydev\hackscite\scintilla\include\Scintilla.iface'
#~ target2 = r'C:\pydev\hackscite\scite\src\pythonextension.cxx'
target = r'C:\Users\bfisher\Desktop\scite1\1newer1\scintilla_include\Scintilla.iface'
target2 = r'C:\Users\bfisher\Desktop\scite1\1newer1\src\pythonextension.cxx'
targettable = r'C:\Users\bfisher\Desktop\scite1\1newer1\src\ifacetable.cxx'
go(target, target2,targettable)



