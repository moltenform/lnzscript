#makekeumod doesn't work

from CScite import ScEditor, ScOutput, ScApp
import exceptions

def expectThrow(fn, sExpectedError, TypeException=exceptions.RuntimeError):
	try:
		fn()
	except TypeException,e:
		print 'Pass:',sExpectedError, str(e).split('\n')[-1]
	else:
		print 'Fail: expected to throw '+sExpectedError

def testSciteCallsApp(nTest):
	if nTest==1:
		ScApp.Trace( 'trace')
		ScApp.Trace( 'trace')
		#result should be tracetrace with no whitespace between
		ScApp.MsgBox( 'mbox')
	if nTest==2:
		ScApp.OpenFile('c:\\nps.txt')
		print 'Output'
		print 'traced'
	if nTest==3:
		ScApp.UnsetProperty('a.new.prop')
		assert ScApp.GetProperty('tabbar.visible') == '1'
		assert ScApp.GetProperty('margin.width') == '16'
		assert ScApp.GetProperty('a.new.prop') == ''
		for prop in ('tabbar.visible', 'margin.width', 'a.new.prop'):
			print '%s=%s'%(prop, ScApp.GetProperty(prop))
		ScApp.SetProperty('a.new.prop', 'newval')
		assert ScApp.GetProperty('a.new.prop') == 'newval'
		print 'a.new.prop=' + ScApp.GetProperty('a.new.prop')
		
	if nTest==4:
		ScApp.UpdateStatusBar()
	if nTest==5:
		ScApp.UpdateStatusBar(True)
	if nTest==6:
		assert ScApp.SCFIND_WHOLEWORD == 2
		assert ScApp.SCFIND_MATCHCASE == 4
		assert ScApp.SCFIND_WORDSTART == 0x00100000
		assert ScApp.SCFIND_REGEXP == 0x00200000
		assert ScApp.SCFIND_POSIX == 0x00400000
		expectThrow( lambda: ScApp.NON_PROPERTY, 'not found')
		

#~ def testSciteCallsApp(nTest):
	#~ if nTest==0:
	#~ if nTest==1:
	#~ if nTest==2:
	#~ if nTest==3:
	#~ if nTest==4:
	#~ if nTest==5:
	#~ if nTest==6:
	#~ if nTest==7:
	
def testSciteCallsPane(nTest, objPane):
	from exceptions import AttributeError
	if nTest==0:
		expectThrow( (lambda:CScite.pane_Append(1, 'a', 'b')), 'wrong # args')
		expectThrow( (lambda:objPane.XXX()), 'noattribute', TypeException=AttributeError)
		expectThrow( (lambda:objPane.fnNothing()), 'not find fn')
		expectThrow( (lambda:objPane.fn()), 'not find fn')
		expectThrow( (lambda:objPane.fnClearAll(1)), 'wrong#args')
		expectThrow( (lambda:objPane.fnSetWhitespaceBack(1,1,1)), 'wrong#args')
		expectThrow( (lambda:objPane.fnAppendText('a','b','c','d')), 'wrong#args')
		expectThrow( (lambda:objPane.fnAppendText('a','a')), 'int expected')
		expectThrow( (lambda:objPane.fnAppendText(False,False)), 'string expected')
		
	if nTest==1:
		objPane.Append('_appendtext')
		objPane.Append('_appendtext')
		objPane.Append('_appendtext')
		
	if nTest==2:
		objPane.Append('1234567')
		objPane.Insert(2, 'aaa')
		
	if nTest==3:
		s = objPane.Textrange(2,4)
		print 'chars 2-4 are:'+s
		print 'findtext:', objPane.FindText('lookit')
		print 'findwhole:', objPane.FindText('lookit', wholeWord=True)
		print 'findcase:', objPane.FindText('lookit', matchCase=True)
		print 'findinrange:', objPane.FindText('lookit', 0, 2,50)
		
	#~ if nTest==4:
		
	#~ if nTest==5:
	#~ if nTest==6:
	#~ if nTest==7:

def testSciteCallsPaneFn(nTest, objPane):
	if nTest==1:
		n = objPane.GetTextLength(); print 'GetTextLength', n
		n = objPane.GetUseTabs(); print 'GetUseTabs', n
		n = objPane.GetLexer(); print 'GetLexer', n
		n = objPane.GetCursor(); print 'GetCursor', n
		s = objPane.GetWhitespaceChars(); print 'GetWhitespaceChars', s
		#this is bad - ir should throw, is set only
		s = objPane.GetWhitespaceChars(); print 'GetWhitespaceChars', s
	if nTest==2:
		objPane.fnAssignCmdKey #iface_void, {iface_keymod, iface_int}},
		objPane.fnCopyText # iface_void, {iface_length, iface_string}},
		objPane.fnGetLine #iface_int, {iface_int, iface_stringresult}},
		objPane.fnGetSelText # iface_int, {iface_void, iface_stringresult}},
		objPane.fnGetLexerLanguage # iface_int, {iface_void, iface_stringresult}},
		objPane.fnPositionFromLine #  iface_position, {iface_int, iface_void}},
		objPane.fnGotoLine #void,  {iface_int, iface_void}},
		objPane.fnSetWhitespaceBack # iface_void, {iface_bool, iface_colour}},
		objPane.fnAppendText #iface_void, {iface_length, iface_string}},
		objPane.fnClearAll # iface_void, {iface_void, iface_void}}
		
		ScOutput.fnClearAll()
		#~ objPane.fnAssignCmdKey(makeKeyMod(ord(','), fCtrl=True), 2180 ) #or ScApp.IDM_ABOUT
		objPane.fnAssignCmdKey(ScEditor.MakeKeymod(ord(','), fCtrl=True), ScApp.IDM_ABOUT ) #or ScApp.IDM_ABOUT
		objPane.fnCopyText(len('foo'), 'foods')
		s = objPane.fnGetLine(2); print 'fnGetLine(2)', s
		s = objPane.fnGetSelText(); print 'fnGetSelText', s
		s = objPane.fnGetLexerLanguage(); print 'fnGetLexerLanguage', s
		n = objPane.fnPositionFromLine(2); print 'PositionFromLine(2)', n
		ret = objPane.fnGotoLine( 3 ); assert ret == None
		
	if nTest==3:
		objPane.fnSetWhitespaceBack(True, 0x00ff0000) #first turn on view whitespace
		objPane.fnAppendText(len('_append_'), '_append_')
		return False
	#~ if nTest==4:
	#~ if nTest==5:
	#~ if nTest==6:
	#~ if nTest==7:

#~ def testSciteCallsApp(nTest):
	#~ if nTest==0:
	#~ if nTest==1:
	#~ if nTest==2:
	#~ if nTest==3:
	#~ if nTest==4:
	#~ if nTest==5:
	#~ if nTest==6:
	#~ if nTest==7:



def OnStart():
	print 'See OnStart'

def OnOpen(sFilename):
	print 'See OnOpen'
	pass

def OnClose(sFilename):
	print 'See OnClose'
	pass
	
def OnSwitchFile(sFilename):
	print 'See OnSwitchFile'
	pass
	
def OnBeforeSave(sFilename):
	print 'See OnBeforeSave'
	pass
	
def OnSave(sFilename):
	print 'See OnSave'
	pass
	
def OnSavePointReached():
	print 'See OnSavePointReached'
	pass
	
def OnSavePointLeft():
	print 'See OnSavePointLeft'
	pass

testLevel = 1
def OnKey( keycode, fShift, fCtrl, fAlt):
	global testLevel
	
	if not (keycode>=ord('0') and keycode<=ord('9')):
		return True #pass
	
	if fCtrl and not fShift and not fAlt:
		ScOutput.fnClearAll()
		print 'setting testlevel to '+str(keycode-ord('0'))
		testLevel = keycode-ord('0')
		return False
	elif not fCtrl and not fShift and not fAlt:
		ScOutput.fnClearAll()
		nTest = keycode-ord('0')
		if testLevel == 1: testSciteCallsApp(nTest)
		if testLevel == 2: testSciteCallsAppFn(nTest)
		if testLevel == 3: testSciteCallsPane(nTest, scEditor)
		if testLevel == 4: testSciteCallsPaneFn(nTest, scEditor)
		if testLevel == 5: testSciteCallsPaneProp(nTest, scEditor)
		if testLevel == 6: testSciteCallsPane(nTest, ScOutput)
		if testLevel == 7: testSciteCallsPaneFn(nTest, ScOutput)
		if testLevel == 8: testSciteCallsPaneProp(nTest, ScOutput)
		return False
		

def OnChar(nChar):
	# returning False here does nothing
	pass

def OnDoubleClick():
	print 'See OnDoubleClick'
	pass

	
def OnMarginClick():
	print 'See OnMarginClick'
	pass

def OnTipStart(pos, word):
	print 'See OnTipStart'
	pass

def OnTipEnd():
	print 'See OnTipEnd'
	pass

def OnUserListSelection(n,sFilename):
	print 'See OnUserListSelection'
	pass





