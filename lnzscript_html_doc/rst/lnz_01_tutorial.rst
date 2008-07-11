
Dialog
============
These functions are mainly straight-forward. 

Window
==============

Controls
================
Let's say you want a script to simulate clicking a button on a dialog. There are different ways one could approach this. One might measure the position of the button and use Mouse.move and Mouse.click to click at those coordinates, but this method is somewhat fragile - if the dialog is moved slightly, it could end up clicking somewhere unintended. A good choice is to find a keyboard shortcut for this, and simulate the keypress using Keyboard.send. If there is not a keyboard shortcut, though, or you want greater control you will have to use one of the Control methods.

Scripts
================
How to include other scripts/modules. __name__. include() print() , printar()
How to use prototype-based inheritance.
Use JavaScript prototypes like those in




