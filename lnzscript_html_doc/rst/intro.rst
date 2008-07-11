=================
Introduction
=================


What is Launchorz?
================================

The goal of the Launchorz project is to provide powerful Win32 automation tools - automating repetitive tasks. 

LnzScript is the language used by Launchorz. It is a version of JavaScript with many additional libraries. LnzScript differs from the traditional use of JavaScript - it won't be run in a web browser,  and can interact with the filesystem. However, standard JavaScript code and idioms can still be used, including prototype-based classes.

Example of what Launchorz can do:
	In a file called ``test.js``,

	::
	
		Process.open('notepad.exe')
		Time.sleep(500);
		Keyboard.send('hello!')
		Dialog.askYesNo('Question','Did you expect this to happen?');

Now run ``lnzscript test.js``, and watch what happens!

Why Launchorz?
==============================

There are existing tools for Windows automation. One popular choice is AutoIt, and another strong project is AutoHotKey.  LnzScript has an overlap of functionality with these tools, and exists for a very similar purpose.

The most important difference is that LnzScript is a true, comfortable language for those familiar with programming. AutoIt and AutoHotKey use a minimal BASIC-like language, which although may be easier for beginners, is not suitable for non-trivial functions. LnzScript has the feel of a more complete language rather than a list of instructions for a one-time use script. The C-style syntax is familiar to those who have worked languages such as  C++ or Java, and there is no need for labels and GOTO statements. The built-in array [] and object {} data types are very useful. Also, by being based on JavaScript (Ecma-262), there can be greater code re-use of algorithms. (For example, many JavaScript code examples exist online).

I would also claim that Launchorz is more extensible than AutoIt or AutoHotKey. It is not simple for a developer to add new functionality to these projects. In LnzScript, one can use the "include" function to import a code module. These modules can have private variables (declared with var) and prototype-based classes. This prevents name collisions and allows for information hiding. 

Finally, much effort is put into designing the LnzScript API. The provided functions are organized, and aim to be self-explanatory without using any cryptic abbreviations. LnzScript functions reside in static classes, and will not interfere with your code.

Also, there are further plans for Launchorz beyond LnzScript. Expect to see a dedicated script editor, quick access to Launchorz from the keyboard, and more.

.. (commented out) WSH is another option, provided by Microsoft. JavaScript as well as other active scripting languages are available. However, it is not very well documented, is not simple to use for automation, and some users disable it due to security concerns.

Current Implementation
====================================
Versions of Windows prior to XP are not officially supported.

The details here may change, and are not necessarily important to users, but I am crediting what makes this project possible. LnzScript functions are currently provided by a combination of the Qt Toolkit by Trolltech, nircmd by nirsoft, the AutoItX dll, and the Windows api. The language is interpreted by Qt's QtScript module, an implementation of Ecma-262. 




