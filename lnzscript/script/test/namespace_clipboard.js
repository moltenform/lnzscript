

registerTest('Clipboard.getText');
print('Current contents of the clipboard are: '+Clipboard.getText());

registerTest('Clipboard.setText');
Clipboard.setText('ThisIsATest');
assertEq(Clipboard.getText(), 'ThisIsATest')

registerTest('Clipboard.clear');
Clipboard.clear();
assertNotEq(Clipboard.getText(), 'ThisIsATest')

// get a screenshot from calc
Process.open('calc'); Time.sleep(500);
Screen.copyScreenshot(false); Time.sleep(100);

// save the screenshot
registerTest('Clipboard.saveImage');
Clipboard.saveImage('calc_screenshot_clipboard.png')
Clipboard.saveImage('calc_screenshot_clipboard.bmp')
Process.close('calc.exe');

Process.openFile('calc_screenshot_clipboard.png');
Dialog.alert('Test','You should see a screenshot of a calculator.');

methods_list_summary_namespace('Clipboard');