=================
Contribute
=================

Launchorz is an open source project licensed under the GPL. (That means that if you have a good idea, post it as an enhancement on the project page, optionally including a diff). It is a new project, and help is appreciated. To become a member of the project, e-mail me (Ben) or leave a comment on my `blog <http://halfhourhacks.blogspot.com>`_.

Try it!
-----------------
You can help by simply using the software. If you notice that something does not work as expected, or documentation is incorrect, you can use the project page to post an issue. `Issues list <http://code.google.com/p/launchorz/issues/list>`_. Or give feedback via e-mail, blog, or anything.


Writing test cases
---------------------------------------
If you decide to join development, this is a great way to help the project and to play with things. Unit tests reside in /lnzscript/script/test/, but there are currently only a few written. A small test framework keeps track of which methods have no tests, and the eventual goal is to have tests for the entire api.

Writing documentation
--------------------------------------------
At this point in time, some details are not set in stone, and so I am holding off on a full-fledged documentation effort. I still feel that documentation is important.

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

Structure
-----------------------

The structure of the code is somewhat unique, but is convenient. The implementations are in /lnzscript/provide_script/source, but note that the .cpp files are not compiled directly. The .cpp files here contain significant metadata in the comments (any line beginning with /// should be considered a directive), and are processed by a Python script to create the real .cpp file. This is done for several reasons:

- Inline documentation
- Argument checking. QtScript function calls are not "type-checked", but by providing metadata about the types expected, the Python script will automatically generate checks that the incoming arguments are valid.
- Flexibility. To change the way in which something is done, one just changes the Python script or the .cpp.template file instead of countless C++ functions.

In more detail, every "exposed-\*.cpp" file in source is processed, and cpp code is generated. This code is placed into one of the .cpp.template files to create the final .cpp output.

On a much smaller scale, a similar step occurs for JavaScript. The JavaScript libraries are in /lnzscript/script/provide , and a Python script at build time consolidates them to a single std.js file in the output directory.

