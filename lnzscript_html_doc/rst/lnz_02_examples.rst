=================
Examples
=================

Here are screencasts showing how LnzScript works.


`Video 1, Basics <http://jamon.ben.googlepages.com/movlnz_02_screencast_basics.htm>`_

	Covers:

	- Writing simple scripts
	- Dialogs
	- Opening and sending keypresses to a process

	Summary:

	- When referring to a filepath, one must type 'c:\\\\myfile.txt' and not 'c:\\myfile.txt'
	- Keyboard.send can be used to simulate both typing and Control- keyboard shortcuts

`Video 2, Opening Firefox Tabs <http://jamon.ben.googlepages.com/movlnz_02_screencast_fftabs.htm>`_

	Covers:
	
	- Example of a useful script
	- Generating a shortcut to a script
	
	Summary:
	
	- Time.sleep is important to wait for the program to be ready.
	- Window.maximize, Window.move, and Window.resize can be used
	- File.getPathSpecial() can be used to get the Desktop folder among others.
	- File.writeFile can be used to create a text file.

`Video 3, Visual studio <http://jamon.ben.googlepages.com/movlnz_02_screencast_vstudio.htm>`_

	This is a real-life example. In Visual Studio, let's say you have a large C++ solution with many projects. You'd like to change all of the projects from Multi-byte character set to Unicode. Instead of clicking through all of the settings, you can write a script to loop through all projects and change the setting for you. The specific code will only work for vs 2003, but the process of writing the script is generalizable.


`Video 4, Controls <http://jamon.ben.googlepages.com/movlnz_02_screencast_controls.htm>`_

	Covers:
	
	- Direct interaction with controls on a form
	- Using a Window Info tool to find control ids
	- Getting / setting text of control, simulating clicking on a control

	Summary:
	
	- Open "Window Info" from the Tools menu to open the Window Info tool
	- When the tool is open, it will display information about the control currently under the cursor
	- The "ClassNN" or "id" of the control can both be used to refer to a control.


Video 5, Useful Clipboard Interaction

	(Coming soon)
	
	- Getting and setting clipboard text
	- More advanced Javascript, <std> library
	- Creating a code module.





