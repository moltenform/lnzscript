# SciTE Python Extension
# Ben Fisher, 2011

import CScite
from CScite import ScEditor, ScOutput, ScApp
import exceptions
import sys


CurrentPane = ScEditor # press Ctrl+; to switch
winNewLines = True

def test_0_0():
	ScApp.MsgBox('Test:MessageBox')
	ScApp.Trace('Test:')
	ScApp.Trace('Tracing')

def test_0_1():
	ScOutput.ClearAll()
	ScApp.Trace('abc')
	expectEqual(ScOutput.GetAllText(), 'abc')
	ScOutput.ClearAll()
	expectEqual(ScOutput.GetAllText(), '')
	ScOutput.ClearAll()
	ScApp.Trace('AA'); ScApp.Trace('BB'); ScApp.Trace('CC')
	expectEqual(ScOutput.GetAllText(), 'AABBCC')
	
	expectEqual(ScApp.GetProperty('tabbar.visible') , '1')
	expectEqual(ScApp.GetProperty('margin.width') , '16')
	expectEqual(ScApp.GetProperty('a.new.prop') , '')
	for prop in ('tabbar.visible', 'margin.width', 'a.new.prop'):
		print '%s=%s'%(prop, ScApp.GetProperty(prop))
	ScApp.SetProperty('a.new.prop', 'abc')
	expectEqual(ScApp.GetProperty('a.new.prop') , 'abc')
	ScApp.SetProperty('a.new.prop', 'def')
	expectEqual(ScApp.GetProperty('a.new.prop') , 'def')
	ScApp.UnsetProperty('a.new.prop')
	expectEqual(ScApp.GetProperty('a.new.prop') , '')
	
	expectThrow( (lambda: ScApp._specialatt), '', exceptions.AttributeError)
	expectThrow( (lambda: ScApp.nonExist()), 'Could not find command')
	expectThrow( (lambda: ScApp.nonExist(1)), 'takes no arguments', exceptions.TypeError )
	expectThrow( (lambda: ScApp.NON_EXIST), 'Could not find constant')
	expectThrow( (lambda: ScApp.NON_EXIST(1)), 'Could not find constant')
	expectThrow( (lambda: ScApp.Close(1)), 'takes no arguments', exceptions.TypeError )
	
	# test commands that can be verified by script
	ScApp.Trace('abc')
	ScApp.ClearOutput()
	expectEqual(ScOutput.GetAllText(), '')
	
	ScEditor.ClearAll()
	ScEditor.Write('h')
	ScApp.Duplicate()
	expectEqual(ScEditor.GetAllText(), 'h\r\nh' if winNewLines else 'h\nh')
	
	ScEditor.ClearAll()
	ScEditor.Write('ABCabcABC')
	ScApp.SelectAll()
	ScApp.Lwrcase()
	expectEqual(ScEditor.GetAllText(), 'abcabcabc')
	
	ScEditor.ClearAll()
	ScEditor.Write('qq')
	ScApp.SelectAll()
	ScApp.Cut()
	ScApp.Paste()
	ScApp.Paste()
	ScApp.Paste()
	expectEqual(ScEditor.GetAllText(), 'qqqqqq')
	
	ScEditor.ClearAll()
	ScEditor.Write('g')
	ScApp.SelectAll()
	ScApp.Uprcase()
	ScApp.Copy()
	ScApp.Paste() #replaces selection
	ScApp.Paste()
	expectEqual(ScEditor.GetAllText(), 'GG')
	
	

def test_0_3():
	ScApp.OpenFile('pythonsetup.py')
	ScApp.MsgBox( 'Opened.')
	ScApp.Close()
	ScApp.MsgBox( 'Closed.')



def test_1_1():
	expectThrow( (lambda:CurrentPane.MarkerAdd(1,1,1)), 'wrong#args')
	expectThrow( (lambda:CurrentPane.CanRedo(None)), 'wrong#args')
	expectThrow( (lambda:CurrentPane.CanRedo(0)), 'expected int')
	

##################################

testLevel = 0
def RunTestSet( keycode, fShift, fCtrl, fAlt):
	global testLevel
	if keycode==ord("'") and fCtrl and not fShift and not fAlt:
		SwitchOutput()
		return False
	
	if not (keycode>=ord('0') and keycode<=ord('9')):
		return True
	
	if fCtrl and not fShift and not fAlt:
		ScOutput.ClearAll()
		print 'setting testlevel to '+str(keycode-ord('0'))
		testLevel = keycode-ord('0')
		return False
	elif not fCtrl and not fShift and not fAlt:
		s = 'test_' + str(testLevel) + '_' + str(keycode-ord('0')) + '()'
		print s
		exec s
		return False


##################################

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
		raise exceptions.RuntimeError, 'stop'
	else:
		print 'pass: '+str(vExpected) + ' == '+str(v)

def expectNotEqual(v, vExpected):
	if v == vExpected:
		print 'fail: Expected '+str(vExpected) + ' not to equal '+str(v)
		raise exceptions.RuntimeError, 'stop'
	else:
		print 'pass: '+str(vExpected) + ' != '+str(v)


class PrintToEditor():
	def __init__(self): pass
	def write(self, s): ScEditor.Write(s)
	def close(self): pass

sys.stdoutOut = sys.stdout
sys.stdoutEdit = PrintToEditor()

def SwitchOutput():
	if CurrentPane==ScEditor:
		sys.stdout = sys.stdoutEdit
		CurrentPane = ScOutput
	else:
		sys.stdout = sys.stdoutOut
		CurrentPane = ScEditor

def printclear():
	if CurrentPane == ScOutput:
		ScEditor.ClearAll()
	else:
		ScOutput.ClearAll()
	
	
