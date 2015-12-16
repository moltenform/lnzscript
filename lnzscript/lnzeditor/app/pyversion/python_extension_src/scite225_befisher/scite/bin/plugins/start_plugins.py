
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

def putArgsOnNewlines():
	ssel = ScEditor.GetSelText()
	assert( ssel.count('(') == 1 and ssel.count(')') == 1)
	sbefore = ssel[0:ssel.index('(')+1]
	sinside = ssel[ssel.index('(')+1:ssel.index(')')]
	safter = ssel[ssel.index(')'):]
	sinside = sinside.replace(', ', ',\r\n\t')
	srep = sbefore + '\r\n\t' + sinside + safter
	
	ScEditor.BeginUndoAction()
	ScEditor.Clear()
	ScEditor.InsertText(srep, ScEditor.GetCurrentPos())
	ScEditor.SetAnchor(ScEditor.GetCurrentPos() + len(srep))
	#don't use Write. we want it all selected
	ScEditor.EndUndoAction()
	
def magicReplace():
	ssel = ScEditor.GetSelText()
	if not ssel:
		print 'No selection'
		return
	if '@@@'  in ssel:
		print '@@@ is invalid.'
		return
	if not '@'  in ssel:
		print 'No @ seen.'
		return
	bIsNumeric = not '@@'  in ssel
	if bIsNumeric:
		nNumber=-1
		sin = ssel.split('\n')
		for i in range(len(sin)):
			if '@' in sin[i]: nNumber+= 1
			sin[i] = sin[i].replace('@', str(nNumber))
		sout = '\n'.join(sin)
	else:
		sExample = '\nExample:\n var a@Foo@=some["@@"];\n var a@Bar@=some["@@"];'
		sin = ssel.split('\n')
		marker = '$!$__mrk$$'
		for i in range(len(sin)):
			if '@' not in sin[i]: continue
			assert marker not in sin[i]
			stmp = sin[i]
			stmp = stmp.replace('@@',marker)
			astmp = stmp.split('@')
			print astmp
			assert len(astmp)==3, 'Invalid number of single @. '+sExample
			thepiece = astmp[1]
			astmp[0] = astmp[0].replace(marker, thepiece)
			astmp[2] = astmp[2].replace(marker, thepiece)
			sin[i] = astmp[0] + thepiece + astmp[2]
		sout = '\n'.join(sin)

	ScEditor.BeginUndoAction()
	ScEditor.Clear()
	ScEditor.InsertText(sout, ScEditor.GetCurrentPos())
	ScEditor.SetAnchor(ScEditor.GetCurrentPos() + len(sout))
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
#grab onto selection

