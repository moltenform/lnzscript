launchorz
http://jamon.ben.googlepages.com/lnz_01_intro.html
http://code.google.com/p/launchorz/
Powerful JavaScript libraries for Win32 automation
by Ben Fisher
=================

Write short JavaScript scripts to do nearly anything on a Windows machine: 
open programs, simulate keystrokes, simulate mouse movements and clicks, and work with files. 
Current implementation uses a combination of Qt toolkit, an AutoIt dll, and Nircmd.

test.js: 
Process.open('notepad.exe')
Time.sleep(500);
Keyboard.send('hello!')

from a command line: 
lnzscript /f test.js

=================
Documentation at http://jamon.ben.googlepages.com/lnz_01_intro.html
Check out the source at
http://launchorz.googlecode.com/svn/trunk
Contribute patches if you come up with something interesting.
Or, add an issue at http://code.google.com/p/launchorz/issues/list
The file TodoList.txt contains planned features and developments.

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
