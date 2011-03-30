print 'Loading Pyscript'
import CScite
import exceptions

class ScintillaPaneBase():
	nPane = -1
	def __init__(self, nPane):
		self.nPane = nPane
	def __getattr__(self, sprop):
		if sprop.startswith('_'):
			#if it looking for a special method, don't try to do anything.
			raise exceptions.AttributeError
		elif sprop.startswith('fn'):
			sprop = sprop[2:]
			return (lambda *args: CScite.pane_ScintillaFn(self.nPane, sprop, args))
		elif sprop.startswith('Get'):
			sprop = sprop[3:]
			return (lambda param=None: CScite.pane_ScintillaGet(self.nPane, sprop, param))
		elif sprop.startswith('Set'):
			sprop = sprop[3:]
			return (lambda a1, a2=None: CScite.pane_ScintillaSet(self.nPane, sprop, a1, a2))
		
		raise exceptions.AttributeError
		
		
	def Append(self, txt): return CScite.pane_Append(self.nPane, txt)
	def Insert(self, npos, txt): return CScite.pane_Insert(self.nPane,npos, txt)
	def Textrange(self, n1, n2): return CScite.pane_Textrange(self.nPane, n1, n2)
	def FindText(self,s,nFlags=0,n1=0,n2=-1): return CScite.pane_FindText(self.nPane,s,nFlags,n1,n2)

class SciteAppWrapper():
	def __getattr__(self, sprop):
		if sprop.upper() == sprop and '_' in sprop:
			return CScite.GetConstant(sprop)
		else:
			raise exceptions.AttributeError


CScite.Editor = ScintillaPaneBase(0)
CScite.Output = ScintillaPaneBase(1)
CScite.App = SciteAppWrapper()

SCFIND_WHOLEWORD = 2
SCFIND_MATCHCASE = 4
SCFIND_WORDSTART = 0x00100000
SCFIND_REGEXP = 0x00200000
SCFIND_POSIX = 0x00400000

assert CScite.App.SCFIND_WHOLEWORD == SCFIND_WHOLEWORD
assert CScite.App.SCFIND_MATCHCASE == SCFIND_MATCHCASE
assert CScite.App.SCFIND_WORDSTART == SCFIND_WORDSTART
assert CScite.App.SCFIND_REGEXP == SCFIND_REGEXP
assert CScite.App.SCFIND_POSIX == SCFIND_POSIX



#put these into namespace: ScApp, ScEditor, ScOutput


def makeKeyMod(keycode, fShift=False, fCtrl=False, fAlt=False):
	keycode = keycode&0xffff
	modifiers = 0
	if fShift: modifiers |= CScite.App.SCMOD_SHIFT
	if fCtrl: modifiers |= CScite.App.SCMOD_CTRL
	if fAlt: modifiers |= CScite.App.SCMOD_ALT
	return keycode | (modifiers << 16)

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
whichPaneTest = CScite.Editor
def OnKey( keycode, fShift, fCtrl, fAlt):
	global testLevel, whichPaneTest
	#~ print 'See OnChar %d %d %d %d'%(keycode, fShift, fCtrl, fAlt)
	if fCtrl:
		if keycode>=ord('0') and keycode<=ord('9'):
			print 'setting testlevel to '+str(keycode-ord('0'))
			testLevel = keycode-ord('0')
			return False
		return
	
	if testLevel == 1:
		# disable a key by returning false
		if keycode==ord('`'):
			return False
		elif keycode==ord('0'):
			print ''
			CScite.trace( 'trace')
			CScite.trace( 'trace')
			#output should be 'tracetrace' on one line
			print ''
			return False
		elif keycode==ord('1'):
			CScite.OpenFile('c:\\nps.txt')
			return False
		elif keycode==ord('2'):
			assert CScite.GetProperty('tabbar.visible') == '1'
			assert CScite.GetProperty('margin.width') == '16'
			for prop in ('tabbar.visible', 'margin.width', 'a.new.prop'):
				print '%s=%s'%(prop, CScite.GetProperty(prop))
			return False
		elif keycode==ord('3'):
			CScite.SetProperty('a.new.prop','|a value here|')
			return False
		elif keycode==ord('4'):
			CScite.MsgBox('Hi')
			return False
	elif testLevel == 2:
		if keycode==ord('0'):
			if whichPaneTest==CScite.Editor:
				whichPaneTest = CScite.Output
				print 'output to Output'
			else:
				whichPaneTest = CScite.Editor
				print 'output to Editor'
			return False
		elif keycode==ord('1'):
			whichPaneTest.Append('_appendedtext_')
			return False
		elif keycode==ord('2'):
			whichPaneTest.Insert(2, '_insertedtext_')
			return False
		elif keycode==ord('3'):
			s = whichPaneTest.Textrange(2,4)
			print 'chars 2-4 are:'+s
			return False
		elif keycode==ord('4'):
			print 'rdef:', whichPaneTest.FindText('lookit')
			print 'rwhole:', whichPaneTest.FindText('lookit', SCFIND_WHOLEWORD)
			print 'rcase:', whichPaneTest.FindText('lookit', SCFIND_MATCHCASE)
			print 'rrange:', whichPaneTest.FindText('lookit', 0, 2,50)
			return False
		elif keycode==ord('5'):
			CScite.pane_Append(1, '\na\n')
			try: CScite.pane_Append(23, 'a')
			except exceptions.RuntimeError,e: print 'Pass: invalid pane: ', str(e).split('\n')[-1]
			else: print "Fail!(should throw invalid pane)"
			try: CScite.pane_Append(1, 'a', 'b')
			except exceptions.TypeError,e: print 'Pass: wrong # args: ', str(e).split('\n')[-1]
			else: print "Fail!(should throw too many args)"
			
			return False
		elif keycode==ord('6'):
			
			return False
	elif testLevel == 3:
		if keycode==ord('0'):
			try: whichPaneTest.XXX()
			except exceptions.AttributeError,e: print 'Pass: noattribute: ', str(e).split('\n')[-1]
			else: print "Fail!(should throw noattribute)"
			try: whichPaneTest.fnNothing()
			except exceptions.RuntimeError,e: print 'Pass: not find fn: ', str(e).split('\n')[-1]
			else: print "Fail!(should throw not find fn)"
			try: whichPaneTest.fn()
			except exceptions.RuntimeError,e: print 'Pass: not find fn: ', str(e).split('\n')[-1]
			else: print "Fail!(should throw not find fn)"
			try: whichPaneTest.fnClearAll(1)
			except exceptions.RuntimeError,e: print 'Pass: wrong#args: ', str(e).split('\n')[-1]
			else: print "Fail!(should throw wrong#args)"
			try: whichPaneTest.fnSetWhitespaceBack(1,1,1)
			except exceptions.RuntimeError,e: print 'Pass: wrong#args: ', str(e).split('\n')[-1]
			else: print "Fail!(should throw wrong#args)"
			try: whichPaneTest.fnAppendText('a','a')
			except exceptions.RuntimeError,e: print 'Pass: int expected: ', str(e).split('\n')[-1]
			else: print "Fail!(should throw wrongargtype)"
			try: whichPaneTest.fnAppendText(False, False)
			except exceptions.RuntimeError,e: print 'Pass: string expected: ', str(e).split('\n')[-1]
			else: print "Fail!(should throw wrongargtype)"
			
			return False
		elif keycode==ord('1'):
			whichPaneTest.fnAssignCmdKey #iface_void, {iface_keymod, iface_int}},
			whichPaneTest.fnCopyText # iface_void, {iface_length, iface_string}},
			whichPaneTest.fnGetLine #iface_int, {iface_int, iface_stringresult}},
			whichPaneTest.fnGetSelText # iface_int, {iface_void, iface_stringresult}},
			whichPaneTest.fnGetLexerLanguage # iface_int, {iface_void, iface_stringresult}},
			whichPaneTest.fnPositionFromLine #  iface_position, {iface_int, iface_void}},
			whichPaneTest.fnGotoLine #void,  {iface_int, iface_void}},
			whichPaneTest.fnSetWhitespaceBack # iface_void, {iface_bool, iface_colour}},
			whichPaneTest.fnAppendText #iface_void, {iface_length, iface_string}},
			whichPaneTest.fnClearAll # iface_void, {iface_void, iface_void}}
			
			CScite.Output.fnClearAll()
			#~ whichPaneTest.fnAssignCmdKey(makeKeyMod(ord('p')), 2180 )
			whichPaneTest.fnCopyText(len('foo'), 'foods')
			s = whichPaneTest.fnGetLine(2); print 'fnGetLine(2)', s
			s = whichPaneTest.fnGetSelText(); print 'fnGetSelText', s
			s = whichPaneTest.fnGetLexerLanguage(); print 'fnGetLexerLanguage', s
			n = whichPaneTest.fnPositionFromLine(2); print 'PositionFromLine(2)', n
			ret = whichPaneTest.fnGotoLine( 3 ); assert ret == None
			return False
			
		elif keycode==ord('2'):
			whichPaneTest.fnSetWhitespaceBack(True, 0x00ff0000) #first turn on view whitespace
			whichPaneTest.fnAppendText(len('_append_'), '_append_')
			return False
		elif keycode==ord('3'):
			
			return False
		elif keycode==ord('4'):
			
			return False
		elif keycode==ord('5'):
			
			return False
		elif keycode==ord('9'):
			
			return False
	elif testLevel == 4:
		if keycode==ord('0'):
			n = whichPaneTest.GetTextLength(); print 'GetTextLength', n
			n = whichPaneTest.GetUseTabs(); print 'GetUseTabs', n
			n = whichPaneTest.GetLexer(); print 'GetLexer', n
			n = whichPaneTest.GetCursor(); print 'GetCursor', n
			s = whichPaneTest.GetWhitespaceChars(); print 'GetWhitespaceChars', s
			#this is bad - ir should throw, is set only
			s = whichPaneTest.GetWhitespaceChars(); print 'GetWhitespaceChars', s
						
			return False
		elif keycode==ord('1'):
			
		
			return False
		elif keycode==ord('2'):
			
			return False
		elif keycode==ord('3'):
			
			return False
	
	elif testLevel == 9:
		if keycode==ord('0'):
			
			return False
		elif keycode==ord('1'):
			
		
			return False
		elif keycode==ord('2'):
			
			return False
		elif keycode==ord('3'):
			
			return False
		elif keycode==ord('4'):
			
			return False
		elif keycode==ord('5'):
			
			return False
		elif keycode==ord('6'):
			
			return False
		
	pass

# returning False here does nothing
def OnChar(nChar):
	#~ print 'See OnChar'
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




