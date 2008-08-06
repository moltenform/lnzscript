launchorz 0.2
http://jamon.ben.googlepages.com/lnz_02_intro.html
http://code.google.com/p/launchorz/
Powerful JavaScript libraries for Win32 automation
by Ben Fisher
=================

To Get Started:
Unzip the .zip file to someplace on your computer, possibly in Program Files. 
Open the "editor" folder and run lnzeditor.exe. This is a code editor specifically for the Launchorz project. 
Begin typing a script, such as Mouse.move(1,1); alert('hello');. 
Choose run script from the Run menu (or press F5) to run. 

(Alternatively, from the command line, you can run a script by typing lnzscript.exe /f myscript.js .)

=================
Documentation at http://jamon.ben.googlepages.com/lnz_02_intro.html
Check out the source at
http://launchorz.googlecode.com/svn/trunk
Contribute patches if you come up with something interesting.
Or, add an issue at http://code.google.com/p/launchorz/issues/list


Known Issues, as of version 0.2
- System.openUtility mostly does not work. Fixed in svn.
- File.iniDelete and related work, but sometimes return true even upon failure.
- There is a noticeable pause when closing Lnz Scite editor.
- File.dirListFiles() does not include hidden files.

=================
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
