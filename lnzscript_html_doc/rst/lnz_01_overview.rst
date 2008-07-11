=================
Overview
=================

Getting Started
============================

Download from `Google Code <http://code.google.com/p/launchorz/downloads/list>`_.

There are currently two distributions: "command line" and "form". The command-line is recommended, but if you have never used a command-line interface (cmd.exe), the "form" interface is provided. There is not yet an installer, and so the .zip file must be uncompressed to a folder of your choice.

If you choose the command-line interface:

- Unzip the .zip file to a folder, possibly in Program Files.
- Open cmd.exe (the command prompt) and cd into the directory.
- Run lnzscript.exe.
- You should see a LnzScript prompt. Type print('hello') and see if it works.
- Open notepad or a code editor and create a file called 'test.js', containing print('hello')
- Save this file into the directory.
- From cmd.exe, inside the directory, run lnzscript.exe /f test.js
- From now on, you can use both of these ways (interactive or script-based) to run LnzScript code.

If you choose the form interface:

- Unzip the .zip file to a folder, possibly in Program Files.
- Run lnzscriptform.exe and you should see a window with two text boxes.
- Type "print('hello')" into the upper box and click Go. 
- The lower box should respond with the text hello.
- You can run scripts by typing text into the top box, and running it by pressing Go.


The Basics
==============================

Here are some sample scripts to play with:

Dialogs
::

	var res = Dialog.askYesNo('Question','Are you ready?');
	if (res==Dialog.OK) print("That's good.");

Mouse
::

	Mouse.move(1,1); 
	// or, to get really crazy,
	for (var i=0; i<15; i++) Mouse.move(Math.round(Math.random()*800), Math.round(Math.random()*800));
	
Keyboard
::

	Process.open('notepad.exe')
	Time.sleep(500); //wait for the program to open
	Keyboard.send('hello!'); Time.sleep(100);
	Keyboard.send('<Control>s'); //simulates the keystroke,opening Save dialog

Files
::

	// note that you can use / in paths. If you use \, it must be escaped.
	// these are equivalent:
	var s = File.readFile('c:\\dir\\myfile.txt')
	var s = File.readFile('c:/dir/myfile.txt')
	var arFiles = File.dirListFiles('c:/dir', 'name'); //array of files in the folder sorted by name

Controls - this type of thing is useful
::

	Process.open('calc.exe'); Time.sleep(500);
	Keyboard.send('1');
	Control.click('Calculator','Button60'); // click on the "+" button. Find control ids with a tool.
	Keyboard.send('1');
	Keyboard.send('{ENTER}');
	Time.sleep(1500);
	Control.setText('Calculator','403','1337'); //puts text into control id 403. 

Misc. self-explanatory stuff
::

	Screen.saveScreenshot('c:/shot.png', false)
	Sound.mute()
	Window.minimizeAll()
	Process.systemShutdown()
