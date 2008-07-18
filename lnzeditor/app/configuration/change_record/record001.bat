
echo this file is just a representation of changes made to Scite configuation
echo in case of a new release of scite, I can see what was changed.
goto END

mkdir htmldoc
mkdir license
mkdir properties

move *.properties properties
move *.html htmldoc
move *.png htmldoc
move *.jpg htmldoc

move *.txt license
move luaCOPYRIGHT license
move scite.1 license

:END