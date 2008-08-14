print('Running tests for namespace Clipboard.')

registerTest('Clipboard.getText');
registerTest('Clipboard.setText');
registerTest('Clipboard.clear');
{
	print('Current contents of the clipboard are: '+Clipboard.getText());

	Clipboard.setText('ThisIsATest');
	assertEq(Clipboard.getText(), 'ThisIsATest')
	
	Clipboard.clear();
	assertNotEq(Clipboard.getText(), 'ThisIsATest')
}


registerTest('Clipboard.saveImage');
{
	// get a screenshot from calc
	Process.open('calc'); Time.sleep(500);
	Screen.copyScreenshot(false); Time.sleep(100);

	// save the screenshot
	Clipboard.saveImage('calc_screenshot_clipboard.png')
	Clipboard.saveImage('calc_screenshot_clipboard.bmp')
	Process.close('calc.exe');

	Process.openFile('calc_screenshot_clipboard.png');
	if(!confirm('You should see a screenshot of a calculator.')) assert(false);
}

methods_list_summary_namespace('Clipboard');	