
print 'Loading Python extension.'
import CScite
import exceptions

class CScintillaPane():
	def Append(self, txt): return CScite.pane_Append(self.nPane, txt)
	def Insert(self, npos, txt): return CScite.pane_Insert(self.nPane,npos, txt)
	def Remove(self, npos1, npos2): return CScite.pane_Remove(self.nPane, npos1, npos2)
	def Textrange(self, n1, n2): return CScite.pane_Textrange(self.nPane, n1, n2)
	# CScite.pane_ScintillaFn(self.nPane, s, *args)  (see __getattr__)
	# CScite.pane_ScintillaGet(self.nPane, s, *args)  (see __getattr__)
	# CScite.pane_ScintillaSet(self.nPane, s, *args)  (see __getattr__)
	def FindText(self,s,n1=0,n2=-1,wholeWord=False,matchCase=False,regExp=False, nFlags=0): 
		if wholeWord: nFlags |= CScite.ScApp.SCFIND_WHOLEWORD
		if matchCase: nFlags |= CScite.ScApp.SCFIND_MATCHCASE
		if regExp: nFlags |= CScite.ScApp.SCFIND_REGEXP
		return CScite.pane_FindText(self.nPane,s,nFlags,n1,n2)
	
	nPane = -1
	def __init__(self, nPane): 
		self.nPane = nPane
	
	def __getattr__(self, sprop):
		if sprop.startswith('_'):
			#if looking for a special method, don't try to do anything.
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
	
	def MakeKeymod(self, keycode, fShift=False, fCtrl=False, fAlt=False):
		keycode = keycode&0xffff
		modifiers = 0
		if fShift: modifiers |= ScApp.SCMOD_SHIFT
		if fCtrl: modifiers |= ScApp.SCMOD_CTRL
		if fAlt: modifiers |= ScApp.SCMOD_ALT
		return keycode | (modifiers << 16)
	

class CSciteApp():
	def Trace(self, s): return CScite.app_Trace(s)
	def MsgBox(self, s): return CScite.app_MsgBox(s)
	def OpenFile(self, s): return CScite.app_OpenFile(s)
	def GetProperty(self, s): return CScite.app_GetProperty(s)
	def SetProperty(self, s, v): return CScite.app_SetProperty(s, v)
	def UnsetProperty(self, s): return CScite.app_UnsetProperty(s)
	def UpdateStatusBar(self, v=None): return CScite.app_UpdateStatusBar(v)
	# CScite.app_SciteCommand(self.nPane, s, *args)  (see __getattr__)
	# CScite.app_GetConstant(self.nPane, s, *args)  (see __getattr__)
	
	def __getattr__(self, sprop):
		if sprop.startswith('_'):
			#if looking for a special method, don't try to do anything.
			raise exceptions.AttributeError
		elif sprop.startswith('fn'):
			sprop = sprop[2:]
			return (lambda *args: CScite.app_SciteCommand(self.nPane, sprop, args))
		elif sprop.upper() == sprop and '_' in sprop:
			return CScite.app_GetConstant(sprop)
		else:
			raise exceptions.AttributeError

CScite.ScEditor = CScintillaPane(0)
CScite.ScOutput = CScintillaPane(1)
CScite.ScApp = CSciteApp()


	

