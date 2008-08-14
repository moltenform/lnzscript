
registerTest('Dialog.input');
{
	var s = Dialog.input('Title "hey"','Prompt "hey"')
	alert('You entered: '+s)
	s = prompt('Prompt "hey"')
	alert('You entered: '+s)
}

registerTest('Dialog.alert');
registerTest('Dialog.error');
registerTest('Dialog.warning');
{
	Dialog.alert('Alert Title "title"', 'Text "text"');
	Dialog.error('Error Title "title"', 'Text "text"');
	Dialog.warning('Warning Title "title"', 'Text "text"');
}

registerTest('Dialog.askOkCancel');
registerTest('Dialog.askYesNo');
registerTest('Dialog.askYesNoCancel');
{
	assertEq( Dialog.askOkCancel("DialogOKCancel",'Please press ok'), Dialog.OK) 
	assertEq( Dialog.askOkCancel("DialogOKCancel",'Please press cancel'), Dialog.CANCEL) 
	assertEq( Dialog.askYesNo("Dialogyesno",'Please press yes'), Dialog.YES) 
	assertEq( Dialog.askYesNo("Dialogyesno",'Please press no'), Dialog.NO) 
	assertEq( Dialog.askYesNoCancel("Dialogyesnocan",'Please press yes'), Dialog.YES) 
	assertEq( Dialog.askYesNoCancel("Dialogyesnocan",'Please press no'), Dialog.NO) 
	assertEq( Dialog.askYesNoCancel("Dialogyesnocan",'Please press cancel'), Dialog.CANCEL) 
}


registerTest('Dialog.askColor');
{
	alert('Please pick pure red.'); assertArrEq( Dialog.askColor(), [255,0,0])
	alert('Please pick pure green.'); assertArrEq( Dialog.askColor(), [0,255,0])
	alert('Please pick pure blue.'); assertArrEq( Dialog.askColor(), [0,0,255])
}

registerTest('Dialog.openFile');
{
	alert('Open: Any type, single'); var s=Dialog.openFile()
	alert('You chose \r\n'+s)
	alert('txt files, single'); s=Dialog.openFile('txt')
	alert('txt files, multiple'); s=Dialog.openFile('txt', true)
	alert('txt files, single, c drive initial'); s=Dialog.openFile('txt', false, 'c:\\')
	alert('any files, multiple'); s=Dialog.openFile('*', true)
	alert('You chose:\r\n'+s)
	
	
}
registerTest('Dialog.saveFile');
{
	alert('Save: Any type'); var s = Dialog.saveFile()
	alert('You chose \r\n'+s)
	alert('txt files'); s = Dialog.saveFile('txt')
	alert('any files, c drive'); s = Dialog.saveFile('*', 'c:\\')
}

registerTest('Dialog.toolTip');
{
	Dialog.toolTip('Here is a tooltip .')
	Time.sleep(500)
}