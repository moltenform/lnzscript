
# SciTE Python Extension
# Ben Fisher, 2011

from CScite import ScEditor, ScOutput, ScApp

def OnStart():
	print 'See OnStart'

def OnMarginClick():
	ScEditor.Insert( ScEditor.GetCurrentPos(), 'hi')
	print 'See OnMarginClick'
	pass

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

def OnKey( keycode, fShift, fCtrl, fAlt):
	pass

def OnChar(nChar):
	# returning False here does nothing
	pass

def OnDoubleClick():
	print 'See OnDoubleClick'
	pass

def OnDwellStart(nPos, sWord):
	print 'See OnDwellStart'
	pass

def OnDwellEnd():
	print 'See OnDwellEnd'
	pass

def OnUserListSelection(nType, sSelection):
	print 'See OnUserListSelection'
	pass




