
# SciTE Python Extension
# Ben Fisher, 2011

import CScite
from CScite import ScEditor, ScOutput, ScApp
import exceptions
import sys

echoAll = False
CurrentPane = None

def testFailOnIncorrectArgs():
	expectThrow( (lambda: ScApp._specialatt), '', exceptions.AttributeError)
	expectThrow( (lambda: ScApp.nonExist()), 'Could not find command')
	expectThrow( (lambda: ScApp.nonExist(1)), 'takes no arguments', exceptions.TypeError )
	expectThrow( (lambda: ScApp.NON_EXIST), 'Could not find constant')
	expectThrow( (lambda: ScApp.NON_EXIST(1)), 'Could not find constant')
	
	
	expectThrow( (lambda:CurrentPane.MarkerAdd(1,1,1)), 'wrong#args')
	expectThrow( (lambda:CurrentPane.CanRedo(None)), 'wrong#args')
	expectThrow( (lambda:CurrentPane.CanRedo(0)), 'expected int')
	


#things that basically have to be manual
def basicTests():
	ScEditor.ClearAll(); ScOutput.ClearAll()
	ScEditor.Write('a');ScEditor.Write('bc')
	ScApp.Trace('d');ScApp.Trace('ef')
	ScApp.MsgBox( 'Not an error.\nManual sanity check:\n editor="abc"\n output="def"\n\nThanks')
	
	
	ScEditor.ClearAll(); ScOutput.ClearAll()
	SetStdout(ScEditor)
	expectEqual(ScOutput.GetAllText(), '')
	ScApp.Trace("a")
	ScApp.Trace("b")
	ScApp.Trace("c")
	expectEqual(ScOutput.GetAllText(), 'abc')
	
	ScEditor.ClearAll(); ScOutput.ClearAll()
	SetStdout(ScOutput)
	ScApp.OpenFile('pythonsetup.py')
	ScApp.MsgBox( 'Opened.')
	ScApp.Close()
	ScApp.MsgBox( 'Closed.')
	
	
	

def autoTestApp():
	testFailOnIncorrectArgs()
	#~ basicTests()
	#~ ScOutput.ClearAll()
	#~ expectEqual(getAllText(ScOutput), ''); ScOutput.ClearAll()
	#~ ScApp.Trace("trace")
	#~ ScApp.Trace("trace")
	#~ expectEqual(getAllText(ScEditor), 'tracetrace'); ScOutput.ClearAll()
	
	

def manualTestApp():
	ScApp.MsgBox( 'Message box')
	pass


def manualTestPane(pane):
	expectThrow( (lambda:objPane.MarkerAdd(1,1,1)), 'wrong#args')
	expectThrow( (lambda:objPane.CanRedo(None)), 'wrong#args')
	expectThrow( (lambda:objPane.CanRedo(0)), 'expected int')
	
	pane.MarkerAdd(2,2)



def testSciteCallsApp(nTest):
	if nTest==1:
		autoTestApp()
		
		#~ ScApp.Trace( 'trace')
		#~ ScApp.Trace( 'trace')
		#~ # result should be tracetrace with no whitespace between
		#~ ScApp.MsgBox( 'mbox')
		
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
		objPane.Insert('aaa',2)
		
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
		expectThrow( (lambda:objPane.ClearAll(1)), 'wrong#args')
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
		expectThrow( (lambda:objPane.GetLineCount('a')), 'prop does not take params')
		expectThrow( (lambda:objPane.GetLineCount(1)), 'prop does not take params')
		expectThrow( (lambda:objPane.GetCharAt()), 'prop needs param')
		expectThrow( (lambda:objPane.GetCharAt('a')), 'Int expected')
		expectThrow( (lambda:objPane.SetStyleBold('a')), 'Bool expected')
		expectThrow( (lambda:objPane.SetStyleBold(True)), 'prop needs param')
		expectThrow( (lambda:objPane.SetViewEOL(1)), 'Bool expected')
		expectThrow( (lambda:objPane.SetViewEOL(True, 45)), 'prop does not take params')
		
		n = objPane.GetCharAt(1); print 'GetCharAt(1)', n, chr(n)
		n = objPane.GetCaretWidth(); print 'GetCaretWidth', n
		n = objPane.GetCurrentPos(); print 'GetCurrentPos', n
		nStyle = objPane.GetStyleAt(1); print 'GetStyleAt 1', nStyle
		n = objPane.GetStyleBold(1); print 'GetStyleBold 1', n
		n = objPane.GetViewEOL(); print 'GetViewEOL 1', n
		
		nBefore = objPane.GetUseTabs();
		objPane.SetUseTabs(not nBefore)
		n = objPane.GetUseTabs(); print 'GetUseTabs was',nBefore, 'is now', n
		
		objPane.SetCaretWidth(3); assert(objPane.GetCaretWidth() == 3)
		
		
		nBefore = objPane.GetViewEOL();
		objPane.SetViewEOL(not nBefore)
		n = objPane.GetViewEOL(); print 'GetViewEOL was',nBefore, 'is now', n
		nBefore = objPane.GetStyleBold(nStyle);
		objPane.SetStyleBold(nStyle, not nBefore)
		n = objPane.GetStyleBold(nStyle); print 'GetStyleBold was',nBefore, 'is now', n
		
		objPane.SetStyleSize(nStyle, objPane.GetStyleSize(nStyle)+1)
		#~ objPane.SetStyleFore(11, 0x00ff0000)
		objPane.SetStyleBold(11, True)
		
		
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
		objPane.ClearAll # iface_void, {iface_void, iface_void}}
		
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
		
	if nTest == 4:
		#moved to its own test. if you call this and then throw an exception,
		#the key event still sent to Scite, and it ends up clearing much of your text.
		objPane.SetCurrentPos(1); assert(objPane.GetCurrentPos() == 1)
	
	
	
	
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
	if echoAll: print 'See OnStart'

def OnOpen(sFilename):
	if echoAll: print 'See OnOpen'
	pass

def OnClose(sFilename):
	if echoAll: print 'See OnClose'
	pass
	
def OnSwitchFile(sFilename):
	if echoAll: print 'See OnSwitchFile'
	pass
	
def OnBeforeSave(sFilename):
	if echoAll: print 'See OnBeforeSave'
	pass
	
def OnSave(sFilename):
	if echoAll: print 'See OnSave'
	pass
	
def OnSavePointReached():
	if echoAll: print 'See OnSavePointReached'
	pass
	
def OnSavePointLeft():
	if echoAll: print 'See OnSavePointLeft'
	pass

testLevel = 1
def OnKey( keycode, fShift, fCtrl, fAlt):
	global testLevel	
	if not (keycode>=ord('0') and keycode<=ord('9')):
		return True
	
	if fCtrl and not fShift and not fAlt:
		ScOutput.ClearAll()
		print 'setting testlevel to '+str(keycode-ord('0'))
		testLevel = keycode-ord('0')
		return False
	elif not fCtrl and not fShift and not fAlt:
		#~ ScOutput.ClearAll()
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
	if echoAll: print 'See OnDoubleClick'
	pass
	
def OnMarginClick():
	ScEditor.Write( 'hi')
	if echoAll: print 'See OnMarginClick'
	pass

def OnDwellStart(nPos, sWord):
	if echoAll: print 'See OnDwellStart'
	pass

def OnDwellEnd():
	if echoAll: print 'See OnDwellEnd'
	pass

def OnUserListSelection(nType, sSelection):
	if echoAll: print 'See OnUserListSelection'
	pass

def expectThrow(fn, sExpectedError, TypeException=exceptions.RuntimeError):
	try:
		fn()
	except TypeException,e:
		sError = str(e).split('\n')[-1]
		if sExpectedError.lower() in sError.lower():
			print 'Pass:',sExpectedError, ' == ', sError
		elif TypeException==True:
			print 'Pass:',' ', sError
		else:
			print 'Fail: expected msg',sExpectedError,'got',sError
	else:
		print 'Fail: expected to throw! '+sExpectedError

def expectEqual(v, vExpected):
	if v != vExpected:
		print 'fail: Expected '+str(vExpected) + ' but got '+str(v)
		raise 'stop'
	else:
		print 'pass: '+str(vExpected) + ' == '+str(v)

def expectNotEqual(v, vExpected):
	if v == vExpected:
		print 'fail: Expected '+str(vExpected) + ' not to equal '+str(v)
		raise 'stop'
	else:
		print 'pass: '+str(vExpected) + ' != '+str(v)


class PrintToEditor():
	def __init__(self): pass
	def write(self, s): ScEditor.Write(s)
	def close(self): pass
def SetStdout(paneObject):
	if paneObject==ScEditor:
		sys.stdout = sys.stdoutEdit
	else:
		sys.stdout = sys.stdoutOut
sys.stdoutOut = sys.stdout
sys.stdoutEdit = PrintToEditor()
def printclear():
	if sys.stdout == sys.stdoutEdit:
		ScEditor.ClearAll()
	else:
		ScOutput.ClearAll()
	
	
	

