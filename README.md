lnzscript
==========

LnzScript lets you easily automate Win32 with JavaScript.

An example:

<pre>
Process.open('notepad.exe')
Time.sleep(500);
Keyboard.send('typing some text into the program...')
if (Dialog.askYesNo('Question','Do you wish to continue?')==Dialog.YES)
    Keyboard.send('Ctrl+s') // bring up Save dialog
</pre>

You can script macros for frequently performed actions, write quick one-off scripts in the editor,
and write tests for your software's UI.

[Download LnzScript 0.4](http://launchorz.googlecode.com/files/lnz_script_0.4.exe) , 2.4Mb

*the features:*

* 180+ available functions, documented and separated into namespaces
* comes with a full editor + optional autocompletion
* reads/writes/renames files, edits the registry, starts processes and reads their stdout 
* simulates mouse+keyboard actions, and can send input to specific controls by id for better robustness.
* access the clipboard, resize windows, and retrieve text from dialogs.
* and, it's all of this from ECMAScript (JavaScript)!

*how is this different than AutoIt?*

* the editor has interesting shortcuts, like executing unsaved scripts
* the provided functions are organized into namespaces
* syntax where it is natural to organize code into functions, and not deal with Goto/While/Wend keywords. 
* you can include shared modules with the built-in include() function.

The implementation uses win32 api, AutoItX dll, Qt Toolkit, and nircmd. The language is interpreted by Qt's QtScript module. (ed. note: when I wrote this in 2008, I mentioned how different it was to use JavaScript out of a browser context... times have changed).

To run scripts from hotkeys, just install [Clavier+](http://utilfr42.free.fr/util/Clavier.php?sLang=en) (a useful open source tool) and
point it at your script.


