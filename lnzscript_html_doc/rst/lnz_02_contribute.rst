=================
Contribute
=================

Launchorz is an open source project licensed under the GPL. If you have a good idea, post it as an enhancement on the project page, optionally with a diff. If you notice a bug, please file a report. It is a new project, and help is appreciated. To become a member of the project, e-mail (Ben) or leave a comment on the `blog <http://halfhourhacks.blogspot.com>`_.

Try it!
-----------------
You can help by simply using the software. If you notice that something does not work as expected, or documentation is incorrect, you can use the project page to post an issue. `Issues list <http://code.google.com/p/launchorz/issues/list>`_. Or give feedback via e-mail, blog, or anything.


Writing test cases
---------------------------------------
If you decide to join development, this is a great way to help the project and to play with things. Unit tests reside in /lnzscript/script/test/. A small test framework keeps track of which methods have no tests; the eventual goal being to have tests for the entire api.

Technical details
======================

Building
---------------------------

- Install Python 2.5 or greater.
- Install Mingw/GCC. (This combination also comes packaged with Bloodshed Dev/Cpp which has an installer).
- Install Qt 4.4 "Open Source Edition"
- Use svn to checkout the latest version of the code. 

	- svn checkout http://launchorz.googlecode.com/svn/trunk/
	
- Read the file /lnzscript/building.txt. Basically you will need to run some Python scripts to generate files.


How it works
-----------------------

The project relies on QtScript. QtScript is a new class in the Qt toolkit that provides an Ecma-262 interpreter, and one can expose C++ functions to it. 

The functions are implemented with a mixture of the Windows api, Qt, AutoItX, and Nirsoft's Nircmd. At a future date, code from the AutoHotKey project may be incorporated. 

Internal Structure
-----------------------

If you downloaded the Launchorz source, this explanation may help.

The implementations of functions are in /lnzscript/provide_script/source, but note that the .cpp files are not compiled directly. The .cpp files here contain significant metadata in the comments (any line beginning with /// is considered a directive), and are processed by a Python script to create the real .cpp file. This is done for several reasons:

- Inline documentation
- Argument checking. QtScript function calls are not type-checked, but by providing metadata about the types expected, the Python script will automatically generate checks that the incoming arguments are valid.
- Flexibility. To change the way in which something is done, one just changes the .cpp.template file or the Python script instead of all of the C++ functions.
- Documentation generation. A Python script creates a .xml file from the source.

In more detail, every "exposed-\*.cpp" file in source is processed, and cpp code is generated. This code is placed into one of the .cpp.template files to create the final .cpp output.

On a smaller scale, a similar step occurs for the JavaScript library. The JavaScript files are in /lnzscript/script/provide , and a Python script at build time consolidates them to a single std.js file in the output directory.

