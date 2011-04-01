
import CScite
from CScite import ScEditor, ScOutput, ScApp
import exceptions


def testSciteCallsApp(nTest):
	if nTest==1:
		ScApp.Trace( 'trace')
		ScApp.Trace( 'trace')
		# result should be tracetrace with no whitespace between
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
		assert ScApp.SCFIND_WHOLEWORD == 2
		assert ScApp.SCFIND_MATCHCASE == 4
		assert ScApp.SCFIND_WORDSTART == 0x00100000
		assert ScApp.SCFIND_REGEXP == 0x00200000
		assert ScApp.SCFIND_POSIX == 0x00400000
		expectThrow( lambda: ScApp.NON_PROPERTY, 'could not find constant')
		expectThrow( lambda: ScApp.GetProperty(1), 'arg 1 must be string', exceptions.TypeError)
		ScApp.UpdateStatusBar()
		
	if nTest==5:
		ScApp.UpdateStatusBar(True)
	
def testSciteCallsAppFn(nTest):
	if nTest==0:
		expectThrow( lambda: ScApp.fnNonExist(), 'could not find constant')
		expectThrow( lambda: ScApp.fn(), 'could not find constant')
	if nTest==1:
		ScApp.fnSelectAll()
		ScApp.fnViewEol()
		ScApp.fnWrap()
		ScApp.fnAbout()
	if nTest==2:
		ScApp.fnBookmarkToggle()
		ScApp.fnPaste()
		ScApp.fnFind()
		
	
def testSciteCallsPane(nTest, objPane):
	from exceptions import AttributeError, TypeError
	if nTest==1:
		objPane.Append('_appendtext')
		objPane.Append('_appendtext')
		objPane.Append('_appendtext')
		
	if nTest==2:
		objPane.Append('0123456789')
		objPane.Remove(6,8)
		objPane.Insert(2, 'aaa')
		
	if nTest==3:
		s = objPane.Textrange(2,4)
		print 'chars 2-4 are:'+s
		print 'findtext:', objPane.FindText('lookit')
		print 'findwhole:', objPane.FindText('lookit', wholeWord=True)
		print 'findcase:', objPane.FindText('lookit', matchCase=True)
		print 'findinrange:', objPane.FindText('lookit', 2,50)


def testSciteCallsPaneFn(nTest, objPane):
	if nTest==0:
		expectThrow( (lambda:CScite.pane_Append(1, 'a', 'b')), 'wrong # args', TypeError)
		expectThrow( (lambda:objPane.XXX()), 'noattribute', AttributeError)
		expectThrow( (lambda:objPane.fnNothing()), 'not find fn')
		expectThrow( (lambda:objPane.fn()), 'not find fn')
		expectThrow( (lambda:objPane.fnClearAll(1)), 'wrong#args')
		expectThrow( (lambda:objPane.fnSetWhitespaceBack(1,1,1)), 'wrong#args')
		expectThrow( (lambda:objPane.fnAppendText('a','b','c','d')), 'wrong#args')
		expectThrow( (lambda:objPane.fnAppendText('a','a')), 'int expected')
		expectThrow( (lambda:objPane.fnAppendText(False,False)), 'string expected')
		
	if nTest==1:
		objPane.GetCharAt #{"CharAt", 2007, 0, iface_int, iface_position},
		objPane.GetCaretWidth #{"CaretWidth", 2189, 2188, iface_int, iface_void},
		objPane.GetCurrentPos #{"CurrentPos", 2008, 2141, iface_position, iface_void},
		objPane.GetUseTabs #{"UseTabs", 2125, 2124, iface_bool, iface_void},
		objPane.GetStyleAt #{"StyleAt", 2010, 0, iface_int, iface_position},
		objPane.GetStyleBold #{"StyleBold", 2483, 2053, iface_bool, iface_int},
		objPane.GetViewEOL #{"ViewEOL", 2355, 2356, iface_bool, iface_void},
		
		n = objPane.GetTextLength(); print 'GetTextLength', n
		n = objPane.GetUseTabs(); print 'GetUseTabs', n
		n = objPane.GetLexer(); print 'GetLexer', n
		n = objPane.GetLineCount(); print 'GetLinecount', n
		expectThrow( (lambda:objPane.SetLineCount(4)), 'prop can\'t be set')
		expectThrow( (lambda:objPane.GetWhitespaceChars()), 'prop can\'t be get')
		print objPane.GetLineCount(55) #errror - succeeds
		#~ expectThrow( (lambda:objPane.GetLineCount('a')), 'prop can\'t be set')
		
		
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
		
		objPane.fnCopyText(len('foo'), 'foods')
		s = objPane.fnGetLine(2); print 'fnGetLine(2)', s
		s = objPane.fnGetSelText(); print 'fnGetSelText', s
		s = objPane.fnGetLexerLanguage(); print 'fnGetLexerLanguage', s
		n = objPane.fnPositionFromLine(2); print 'PositionFromLine(2)', n
		ret = objPane.fnGotoLine( 3 ); assert ret == None
		
		# does not yet work
		objPane.fnAssignCmdKey(ScEditor.MakeKeymod(ord('u'), fCtrl=True), 2004 )
		
	if nTest==3:
		objPane.fnSetWhitespaceBack(True, 0x00ff0000) #first turn on view whitespace
		objPane.fnAppendText(len('_append_'), '_append_')
		

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
		return True
	
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
		if testLevel == 3: testSciteCallsPane(nTest, ScEditor)
		if testLevel == 4: testSciteCallsPaneFn(nTest, ScEditor)
		
		if testLevel == 6: testSciteCallsPane(nTest, ScOutput)
		if testLevel == 7: testSciteCallsPaneFn(nTest, ScOutput)
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

def expectThrow(fn, sExpectedError, TypeException=exceptions.RuntimeError):
	try:
		fn()
	except TypeException,e:
		print 'Pass:',sExpectedError, ':', str(e).split('\n')[-1]
	else:
		print 'Fail: expected to throw '+sExpectedError




