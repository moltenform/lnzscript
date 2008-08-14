=================
Tutorial
=================

This section of the documentation contains more-detailed information about certain functions. (The Reference contains a complete list of what is available). Some screencasts can be found on the "examples" page `here <lnz_02_examples.html>`_ .

Scripts
=================

This is a full-fledged programming language, with loops, functions, and objects. The built in print() function can be used to print a value, sometimes useful for troubleshooting. The include() function will run the contents of another script file. See Scripts - Advanced for more information.

Time
=================

Time.sleep() is used very frequently in scripts. It is used to pause the script, usually to wait for something to happen. You cannot open a program and instantaneously interact with it - you must give the program time to load! Time.sleep(500) waits for half of a second and is typically a reasonable value.

Process
================

One key part of automation is opening a program. This would seem to be simple, but there are actually choices involved. Do you want the script to wait until the program is closed? Do you want to read from the command-line? Here are some ways to start another program:

- Process.open	- opens the program and *doesn't* wait for it to close
- Process.runAndWait	- opens the program and waits for it to close
- Process.runAndRead	- opens the program, reads stdout, and waits for it to close
- Process.runCmdLine	- runs command line like copy, del, rm, and waits for it to close
- Process.openFile	- open a file or URL with default program, doesn't wait for close

For programs that are in the Windows directory, you won't need the entire path. In other words, you can just type Process.open('calc.exe') or Process.open('notepad').

Mouse
===============

It's pretty fun to be able to type ``Mouse.move(1,1)`` and watch the cursor move. LnzScript can also simulate mouse clicks, drags, and scroll-wheel.

However, the problem with using the mouse is that it recquires coordinates, and this can always be somewhat fragile. What if the window is in a different place from what you expected? It is recommended to use Keyboard or direct Control where possible.

Note that Keyboard.send('<Shift>{F10}') can be used to simulate right-clicking on something that has focus.

Keyboard
================

The reference documentation for Keyboard.send sums up what key events can be simulated. For example, one can use Keyboard.send('<Control>s') to simulate Control-S in a program. This is one of the most useful functions in LnzScript.

One can often use {TAB} to walk through the options in a dialog and {ENTER}. <Alt> is also useful for running menu-items or setting focus. ``Keyboard.send('<Alt>f'); Keyboard.send('x');`` for example quits Notepad because Alt-F opens the File menu.


Window
==============

There are ways to interact with a window. In the reference, many of these functions take a first parameter "string window". Here is what is meant by this. You just opened Calculator, maybe with Process.open('calc.exe'), and you want to close the window. Here are the possible ways to refer to the window:

- ``Window.close('')``		Close the currently active window (when given empty string '')
- ``Window.close('Calc')``			Close a window whose title starts with "Calc"
- ``Window.close('"Calculator"')``		Close a window whose title is exactly "Calculator"
- ``Window.close('%ulator%')``			Close any one window with title containing "ulator" 
- ``Window.close({'title':'Calculator', 'class':'SciCalc', 'instance':2})`` 	Close the 2nd instance of an open Calculator with the title "Calculator"

Note that in the last example an object (like a Python dict or Perl hash) was passed, not a string.

Controls
================

Let's say you want a script to simulate clicking a button on a dialog. There are different ways one could approach this. One might measure the position of the button and use Mouse.move and Mouse.click to click at those coordinates, but this method is somewhat fragile - if the dialog is moved slightly, it could end up clicking somewhere unintended. A good choice is to find a keyboard shortcut for this, and simulate the keypress using Keyboard.send. If there is not a keyboard shortcut, though, or you want greater control you will have to use one of the Control methods.

Control methods can interact with a control (button, text field, and so on) on a form. One typically uses a tool to find the ID and/or class of the control. Two such tools are packaged with LnzScript - look in the "windowinfo" and "winexp" directories. An even better tool is distributed with AutoIt, if you happen to have that installed. These tools can give information about controls. 

Control methods generally take "string window" as a parameter - see above section for what this refers to. 

File
===============

There are many functions in this namespace, but they should be self-explanatory. Note that File.readFile() and File.writeFile() are not intended for binary data, and the file cannot be larger than available memory.

When referring to a file path, one should use special string literals beginning with the @ symbol, as in the example ``var s = File.readFile(@'c:\dir\myfile.txt')``. Otherwise, all backslashes in the string will have to be doubled.

Dialog
====================================

These can be used to interact with the user while running a script. ``Dialog.alert ('Paused','Click ok when ready to continue')`` can be used to create a pause. Ask questions with code like: ``var res = Dialog.askYesNo('Question','Are you ready?'); if (res==Dialog.YES) print("That's good.");``


Scripts - Advanced
===================================================

There are two special variables. The variable called ``argv`` is an array containing command-line parameters. The variable ``__name__`` contains either  "included" if the current script was included or "main" otherwise.

LnzScript code can include another file with the include() function. It is recommended to avoid name collisions by following these suggestions: To declare a variable private to a script file, use "var". To declare a function private, declare it with ``function foo(x,y) { return x+y }``. To expose a function as public, use the syntax ``foo = function(x,y) { return x+y }`` In this way functions from one file will not be accidently overwritten. Similar to Python, one can use the special variable called ``__name__`` to find out if the currently running script is "main" (i.e. was the one specified by lnzscript /f name_of_file.js). In this way, a module can contain test code that is not run when it is included.

For more advanced scripts, use the statement ``include('<std>')`` to import a code library. Currently, this library provides prototype methods such as .startsWith() / .endsWith() for strings, prototype methods such as .max() and .min() for arrays, and printarr(a) for printing arrays. These are documented in the Reference under String and Array.

You can associate the extension .js with lnzscript.exe, so that you can double-click a script to run it. It is recommended to associate with lnzscript.exe /fconfirm "%1". This will ask for confirmation before running the script.

Because LnzScript is JavaScript, in order to write an object-oriented program, one uses prototype-based inheritance. This is described online many places as seen by a Google search for object oriented JavaScript.








