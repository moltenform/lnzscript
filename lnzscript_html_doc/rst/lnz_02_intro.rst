=================
Introduction
=================


What is Launchorz?
================================

The goal of the Launchorz project is to provide powerful Win32 automation tools - automating repetitive tasks in any program you use.

LnzScript, the language used by Launchorz, can be thought of as JavaScript with new built-in functions. LnzScript differs from the traditional use of JavaScript - it does not run in a web browser and can interact with the filesystem. However, standard JavaScript code and idioms can still be used, including prototype-based classes.

Example of what Launchorz can do:
	In the editor, type

	::
	
		Process.open('notepad.exe')
		Time.sleep(500);
		Keyboard.send('hello!')
		Dialog.askYesNo('Question','Did you expect this to happen?');
		
	and choose Go from the Run menu. 
	
	(Alternatively, from the command line, you can run a script by typing``lnzscript.exe /f myscript.js``.)

LnzScript's dedicated code editor, with tooltips and autocomplete, makes it easy to write and run scripts.

Why is it useful?
==============================

Automation saves time by freeing you from repetitive tasks. The majority of programs do not have built-in ways to be customized or scripted. However, LnzScript will work with nearly any program - you just tell it which keystrokes to press. It can be used for testing GUI applications, automating a common task, or writing an administrative script.

One example scenario: you have a large Visual Studio solution and need to change the C++ projects from Multi-byte character set to Unicode. The examples page shows how you could write a script to automate this without going through every project manually. 

Why Launchorz?
==============================

There are existing tools for Windows automation. One popular choice is AutoIt, and another is AutoHotKey.  Launchorz has an overlap of functionality with these tools, and exists for a similar purpose.

The most important difference is that this project's LnzScript is based on Javascript: a true language comfortable for those familiar with programming. AutoIt and AutoHotKey use a minimal BASIC-like language which, although it may be easier for beginners, is not suitable for non-trivial scripts. The minimal languages with their lack of structures like objects or standard array syntax feel more like a list of instructions than a complete language. JavaScript's C-style syntax, on the other hand, is familiar to those who have worked languages such as  C++ or Java, and there is no need for distasteful labels, Goto, While, or Wend. The built-in array [] and object {} data types are very useful. Also, by being based on JavaScript, there can be re-use of algorithms. (For instance, many JavaScript code examples exist online).

I would also claim that Launchorz is more extensible than AutoIt or AutoHotKey. It is not simple to add new functions to these projects, but in LnzScript, one can use the "include" function to import a code module which can have its own private functions and variables. Modules can also expose prototype classes, for object-oriented programming. This allows for more structure, avoiding name conflicts, and maintainability of larger projects. 

Finally, much effort is put into designing the LnzScript API. The provided functions are organized, and aim to be self-explanatory rather than using cryptic abbreviations. LnzScript functions reside in namespaces and will not interfere with your code.

Also, there are further plans for Launchorz beyond LnzScript. Expect to see a documentation browser, quick access to Launchorz from the keyboard, and more.

.. (commented out) WSH is another option, provided by Microsoft. JavaScript as well as other active scripting languages are available. However, it is not very well documented, is not simple to use for automation, and some users disable it due to security concerns.

Current Implementation
====================================
Versions of Windows prior to XP are not officially supported.

LnzScript functions are currently implemented by a combination of code using win32 api, AutoItX dll, Qt Toolkit by Trolltech, and nircmd by nirsoft. The language is interpreted by Qt's QtScript module, an implementation of Ecma-262. The implementation may change in the future, but I am crediting what makes this project possible.




