///Namespace:Window
///Section:Launchorz
///Doc:
There are ways to interact with a window. In the reference, many of these functions take a first parameter "string window". Here is what is meant by this. You just opened Calculator, maybe with Process.open('calc.exe'), and you want to close the window. Here are the possible ways to refer to the window:

- ``Window.close('')``		Close the currently active window (when given empty string '')
- ``Window.close('Calc')``			Close a window whose title starts with "Calc"
- ``Window.close('"Calculator"')``		Close a window whose title is exactly "Calculator"
- ``Window.close('%ulator%')``			Close any one window with title containing "ulator" 
- ``Window.close({'title':'Calculator', 'class':'SciCalc', 'instance':2})`` 	Close the 2nd instance of an open Calculator with the title "Calculator"

Note that in the last example an object (like a Python dict or Perl hash) was passed, not a string.
///Enddoc::



///Namespace:Control
///Section:Launchorz
///Doc:
Let's say you want a script to simulate clicking a button on a dialog. There are different ways one could approach this. One might measure the position of the button and use Mouse.move and Mouse.click to click at those coordinates, but this method is somewhat fragile - if the dialog is moved slightly, it could end up clicking somewhere unintended. A good choice is to find a keyboard shortcut for this, and simulate the keypress using Keyboard.send. If there is not a keyboard shortcut, though, or you want greater control you will have to use one of the Control methods.

Control methods can interact with a control (button, text field, and so on) on a form. One typically uses a tool to find the ID and/or class of the control. Two such tools are packaged with LnzScript - look in the "windowinfo" and "winexp" directories. An even better tool is distributed with AutoIt, if you happen to have that installed. These tools can give information about controls. 

Control methods generally take "string window" as a parameter - see above section for what this refers to. 
///Enddoc::

///Namespace:Clipboard
///Section:Launchorz
///Doc:
These methods can interact with the Windows clipboard.
///Enddoc::

///Namespace:Dialog
///Section:Launchorz
///Doc:
Dialogs for interacting with the user.
///Enddoc::

///Namespace:File
///Section:Launchorz
///Doc:
There are many functions in this namespace, but they should be self-explanatory. Note that File.readFile() and File.writeFile() are not intended for binary data, and the file cannot be larger than available memory.
///Enddoc::

///Namespace:Internet
///Section:Launchorz
///Doc:
More advanced methods, such as the ability to download a URL, will be added here soon. In the distant future, ftp support may be added.
///Enddoc::

///Namespace:Keyboard
///Section:Launchorz
///Doc:
The reference documentation for Keyboard.send sums up what key events can be simulated. For example, one can use Keyboard.send('<Control>s') to simulate Control-S in a program. This is one of the most useful functions in LnzScript.

One can often use {TAB} to walk through the options in a dialog and {ENTER}. <Alt> is also useful for running menu-items or setting focus. ``Keyboard.send('<Alt>f'); Keyboard.send('x');`` for example quits Notepad because Alt-F opens the File menu.
///Enddoc::

///Namespace:Mouse
///Section:Launchorz
///Doc:
It's pretty fun to be able to type ``Mouse.move(1,1)`` and watch the cursor move. LnzScript can also simulate mouse clicks, drags, and scroll-wheel.

However, the problem with using the mouse is that it recquires coordinates, and this can always be somewhat fragile. What if the window is in a different place from what you expected? It is recommended to use Keyboard or direct Control where possible.

Note that Keyboard.send('<Shift>{F10}') can be used to simulate right-clicking on something that has focus.
///Enddoc::


///Namespace:Process
///Section:Launchorz
///Doc:
One key part of automation is opening a program. This would seem to be simple, but there are actually choices involved. Do you want the script to wait until the program is closed? Do you want to read from the command-line? Here are some ways to start another program:

- Process.open	-opens the program and *doesn't* wait for it to close
- Process.runAndWait	-opens the program and waits for it to close
- Process.runAndRead	-opens the program, reads stdout, and waits for it to close
- Process.runCmdLine	-runs command line like copy, del, rm, and waits for it to close
- Process.openFile	-open a file or URL with default program, doesn't wait for close

For programs that are in the Windows directory, you won't need the entire path. In other words, you can just type Process.open('calc.exe') or Process.open('notepad').
///Enddoc::


///Namespace:Registry
///Section:Launchorz
///Doc:
Functions here should be self-explanatory.
///Enddoc::


///Namespace:Screen
///Section:Launchorz
///Doc:
Functions here should be self-explanatory.
///Enddoc::


///Namespace:System
///Section:Launchorz
///Doc:
Functions here should be self-explanatory.
///Enddoc::

///Namespace:Sound
///Section:Launchorz
///Doc:
Functions here should be self-explanatory.
///Enddoc::


///Namespace:Time
///Section:Launchorz
///Doc:
Time.sleep() is used very frequently in scripts. It is used to pause the script, usually to wait for something to happen. You cannot open a program and instantaneously interact with it - you must give the program time to load! Time.sleep(500) waits for half of a second and is typically a reasonable value.
///Enddoc::




//now for the builtin ones

///Namespace:(Global)
///Section:Language
///Doc:
LnzScript adds functions to the global namespace: alert, confirm, include, print.

Use include('<std.js>') to add: printarr, printobj.
///Enddoc::


///Namespace:Array
///Section:Language
///Doc:

///Enddoc::


///Namespace:String
///Section:Language
///Doc:

///Enddoc::


///Namespace:Number
///Section:Language
///Doc:

///Enddoc::

///Namespace:Math
///Section:Language
///Doc:

///Enddoc::

///Namespace:Date
///Section:Language
///Doc:

///Enddoc::

///Namespace:RegExp
///Section:Language
///Doc:

///Enddoc::

