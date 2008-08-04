=================
Overview
=================

Getting Started
============================

Download the latest version from `Google Code <http://code.google.com/p/launchorz/downloads/list>`_.

- Unzip the .zip file to someplace on your computer, possibly in Program Files.
- Open the ``editor`` folder and run ``lnzeditor.exe``. This is a code editor specifically for the Launchorz project.
- Begin typing a script, such as ``Mouse.move(1,1); alert('hello');``. 
- Choose run script from the Run menu (or press F5) to run.

A few things to note:

- The output pane to the right contains the results of the script. The output of the ``print`` function will go here.
- Notice the autocomplete and tooltip documentation (which can be disabled in Options->js options).
- A currently-running script can sometimes be stopped with Ctrl+. or Run->Stop Script.

After playing with "The Basics" below, I recommend watching the screencasts on the "examples" page `here <lnz_02_examples.html>`_ .

The Basics
==============================

Here are some sample scripts to play with:

Dialogs
::

	var res = Dialog.askYesNo('Question','Are you ready?');
	if (res==Dialog.YES) print("That's good.");

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
	var arFiles = File.dirListFiles('c:\\dir', 'name'); //array of files in the folder sorted by name

Controls - this type of thing is useful
::

	Process.open('calc.exe'); Time.sleep(500);
	Keyboard.send('1');
	Control.click('Calculator','Button60'); // click on the "+" button. Find control ids with a tool.
	Keyboard.send('1');
	Keyboard.send('{ENTER}');
	Time.sleep(1500);
	Control.setText('Calculator','403','1337'); //puts text into control id 403. 
	// watch the screencasts for more information.

Misc. self-explanatory stuff
::

	Sound.mute()
	Window.minimizeAll()
	Screen.saveScreenshot('c:/shot.png', false)
	Process.systemShutdown()

Demo
::
	
	// It's an actual programming language
	function moveCursor(x, y) { Mouse.move(x,y, true, 1); }
	for (var i=0; i<500; i++) 
		moveCursor(i*2, Math.sin((i/50.0)*6)*300);

From the Command Line
=============================

LnzScript can also be run from the command line using the program "lnzscript.exe". Running 	``lnzscript.exe /f "name of script.js"`` will execute a script. Also, running lnzscript.exe without arguments will start an interactive mode where commands can be typed one at a time.
