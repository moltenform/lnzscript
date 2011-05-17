
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

dictDoNotDocument = {
'Null':1, #pointless
'AddRefDocument':1, 'ReleaseDocument':1, 
'GetDocPointer':1, 'SetDocPointer':1, 
'FindText':1, #FindText is overridden by explicitly exposed FindText
'GetTextRange':1, #GetTextRange is overridden by explicitly exposed Textrange
'GetStyledText':1, #uses a textrange, can't be used yet.
'AddStyledText':1, #uses cells, can't be used yet.
'AddText':1, #use .Write() method instead for the time being
'GetCurLine':1, #overridden
'CopyText':1, #overridden
'AppendText':1, #use .Append() method
'GetText':1, #use GetAllText


}
dictOverrideRemoveEmptyFirstArg = {
"AutoCStops":1,
"AutoCSelect":1,
"ReplaceSel":1,
"SetText":1,
"SetLexerLanguage":1,
"LoadLexerLibrary":1,
}



def go(starget, starget2, targettable):
	stdoutStd = sys.stdout
	stdoutFile = PrintToFile('docs_out.txt')
	
	sys.stdout = stdoutFile
	
	print '''
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
# Pane methods (can be used with ScEditor or ScOutput)
ScEditor.Write(txt) to write text to the current position
ScEditor.GetAllText() returns all text in the file
ScEditor.Append(txt)
ScEditor.Insert(npos, txt)
ScEditor.Remove(npos1, npos2)
ScEditor.Textrange(npos1, npos2)
ScEditor.FindText(s,n1=0,n2=-1,wholeWord=False,matchCase=False,regExp=False, nFlags=0)
ScEditor.GetCurLine() get text in current line
	'''
	
	sys.stdout = stdoutStd
	
	out = iface_verifydocs.go(target, targettable,modifyEntries = True)
	sys.stdout = stdoutFile
	
	for o in out:
		
		if o.type == 'get':
			assert o.name.startswith('Get')			
		if o.type == 'set':
			assert o.name.startswith('Set')
		
		# exceptions....
		if o.name=='FindText':
			continue 
		#we don't document these
		if o.name in dictDoNotDocument:
			continue
		
		sname = o.name
		if 'stringresult' not in o.args:
			rettype=o.returntype.replace('position','pos')
			sargs = o.args.replace(',)',')')
			if sname in dictOverrideRemoveEmptyFirstArg: assert sargs.startswith('(,'); sargs=sargs.replace('(,','(')
			print rettype + '\tScEditor.'+sname + sargs
		else:
			assert o.returntype=='int'
			sargs = o.args.split(',')[0] + ')'
			
			print 'string' + '\tScEditor.'+ sname+ sargs
		
		if o.docs: print o.docs.replace('#','')
	
	
	print '''
	
# Constants, from IFaceTable.cxx
ScApp.SCFIND_WHOLEWORD
ScApp.SCFIND_MATCHCASE 
ScApp.SCFIND_WORDSTART 
ScApp.SCFIND_REGEXP
ScApp.SCFIND_POSIX
...many others...'''

	stdoutFile.close()
	

target = r'..\scintilla\include\Scintilla.iface'
target2 = r'..\scite\src\pythonextension.cxx'
targettable = r'..\scite\src\ifacetable.cxx'
go(target, target2,targettable)



