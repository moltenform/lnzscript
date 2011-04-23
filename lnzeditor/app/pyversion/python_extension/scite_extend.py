
# SciTE Python Extension
# Ben Fisher, 2011

from CScite import ScEditor, ScOutput, ScApp

echoEvents = False

def OnStart():
	if echoEvents: print 'See OnStart'

def OnOpen(sFilename):
	if echoEvents: print 'See OnOpen'

def OnClose(sFilename):
	if echoEvents: print 'See OnClose'

def OnMarginClick():
	ScEditor.Write('hi') # example of how to call a method on the ScEditor object
	if echoEvents: print 'See OnMarginClick'

def OnSwitchFile(sFilename):
	if echoEvents: print 'See OnSwitchFile'
	
def OnBeforeSave(sFilename):
	if echoEvents: print 'See OnBeforeSave'
	
def OnSave(sFilename):
	if echoEvents: print 'See OnSave'
	
def OnSavePointReached():
	if echoEvents: print 'See OnSavePointReached'
	
def OnSavePointLeft():
	if echoEvents: print 'See OnSavePointLeft'

def OnChar(nChar):
	# returning False here has no effect
	pass

def OnDoubleClick():
	if echoEvents: print 'See OnDoubleClick'
	
def OnDwellStart(nPos, sWord):
	if echoEvents: print 'See OnDwellStart'

def OnDwellEnd():
	if echoEvents: print 'See OnDwellEnd'

def OnUserListSelection(nType, sSelection):
	if echoEvents: print 'See OnUserListSelection', nType, sSelection

def OnKey(keycode, fShift, fCtrl, fAlt):
	import scite_extend_tests
	return scite_extend_tests.RunTestSet(keycode, fShift, fCtrl, fAlt)


