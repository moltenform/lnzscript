if not exist ..\..\..\..\lnzscript\builddoc\documentation.xml goto notfound
copy ..\..\..\..\lnzscript\builddoc\documentation.xml .

cscript build_api_file.wsf

posttransform.py

::pause
goto end
:notfound
echo documentation.xml file not found. Run /lnzscript/builddoc/buildxmldoc.bat

:end
