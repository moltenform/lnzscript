if not exist ..\..\..\..\lnzscript_html_doc\documentation.xml goto notfound
copy ..\..\..\..\lnzscript_html_doc\documentation.xml .

cscript build_api_file.wsf

posttransform.py

::pause
goto end
:notfound
echo documentation.xml file not found. Run script_createxmldoc.py

:end
