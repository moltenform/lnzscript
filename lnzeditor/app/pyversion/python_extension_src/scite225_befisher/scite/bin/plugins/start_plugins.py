
# SciTE Python Extension
# Ben Fisher, 2011

from CScite import ScEditor, ScOutput, ScApp

def switchCppHeader():
	import os
	cppendings = ('.cpp','.c','.cxx')
	curFile = ScApp.GetFilePath()
	if not curFile: return
	if curFile.lower().endswith('.h'):
		try: doesExistIndex = map(lambda s: os.path.exists(curFile.replace('.h',s)), cppendings).index(True)
		except ValueError: print 'Could not find cpp.'; return
		else: nextFile = curFile.replace('.h',cppendings[doesExistIndex])
	else:
		try: doesExistIndex = map(lambda s: curFile.endswith(s), cppendings ).index(True)
		except ValueError: print 'Not a cpp header'; return
		nextFile = curFile.replace(cppendings[doesExistIndex],'.h')
		if not os.path.exists(nextFile): print 'Could not find .h.'; return
	ScApp.OpenFile(nextFile)


def deleteNewlines():
	ssel = ScEditor.GetSelText()
	if not ssel:
		print 'No selection'
		return
		
	ScEditor.BeginUndoAction()
	srep = ssel.replace('\r\n',' ').replace('\n',' ')
	ScEditor.Clear()
	ScEditor.InsertText(srep, ScEditor.GetCurrentPos())
	ScEditor.SetAnchor(ScEditor.GetCurrentPos() + len(srep))
	#don't use Write. we want it all selected
	ScEditor.EndUndoAction()
	
def numericReplace():
	ssel = ScEditor.GetSelText()
	if not ssel:
		print 'No selection'
		return
	if '##' not in ssel:
		print '## not found. have one per line'
		return
	ScEditor.BeginUndoAction()
	sout = []
	sin = ssel.split('\n')
	for i in range(len(sin)):
		sout.append(sin[i].replace('##',str(i)))
	srep = '\n'.join(sout)
	ScEditor.Clear()
	ScEditor.InsertText(srep, ScEditor.GetCurrentPos())
	ScEditor.SetAnchor(ScEditor.GetCurrentPos() + len(srep))
	#don't use Write. we want it all selected
	ScEditor.EndUndoAction()

def numericReplace():
	sexample = 'case "aa": print "aa"\ncase "bb": print "##"\ncase "cc": print "##"'
	ssel = ScEditor.GetSelText()
	if not ssel:
		print 'No selection'
		return
	if '##' not in ssel:
		print '## not found.'; print sexample
		return
	
	sout = []
	sin = ssel.split('\n')
	if '##' in sin[0]:
		print '## should not be in first line'; print sexample
	
	#split by tokens/word boundaries, including whitespace.
	#one needs to have limitations-like-no space in the item of interest.
	#RULES: no whitespace
	#each should have the same number of 
	nParts = len(sin[0].split())
	for line in sin[1:]:
		if len(line.split())!=nParts:
			print 'This line has different # of words: ',line
			return
	firstline = sin[0].split()
	for line in sin[1:]:
		thisline = line.split()
		discrepOne = -1; discrepTwo = -1
		for i in range(len(thisline)):
			if thisline[i]!=firstline[i]:
				if discrepOne!=-1 and discrepTwo!=-1:
					print 'Only should be 2 differences.'; return
				elif discrepOne!=-1 and discrepTwo==-1:
					discrepTwo = i
				#~ elif 
	
	for i in range(len(sin)):
		sout.append(sin[i].replace('##',str(i)))
	srep = '\n'.join(sout)
	ScEditor.BeginUndoAction()
	ScEditor.Clear()
	ScEditor.InsertText(srep, ScEditor.GetCurrentPos())
	ScEditor.SetAnchor(ScEditor.GetCurrentPos() + len(srep))
	#don't use Write. we want it all selected
	ScEditor.EndUndoAction()


def DoCiInterfaces():
	ssel = ScEditor.GetSelText()
	if not ssel.startswith('I') or ' ' in ssel:
		print 'expected to start with I, like IFileStoreFile'
		return
	srep = 'CIPtr<%s> spi%s;'%(ssel, ssel[1:])
	
	ScEditor.BeginUndoAction()
	ScEditor.Clear()
	ScEditor.InsertText(srep, ScEditor.GetCurrentPos())
	ScEditor.SetAnchor(ScEditor.GetCurrentPos() + len(srep))
	#don't use Write. we want it all selected
	ScEditor.EndUndoAction()

#then: faster search/replae
#grab onto selectionns
#also lines w repeated stuff
#~ case foo: print 'foo'
#~ case bar: print 'bar'
