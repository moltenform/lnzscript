
[Setup]
AppId={{E0D53206-14DE-4124-AA15-B7E4A1B82A68}
AppName=LnzScript
AppVersion=0.5
AppVerName=LnzScript 0.5
AppPublisher=Ben Fisher
AppPublisherURL=https://github.com/moltenform/lnzscript
AppSupportURL=https://github.com/moltenform/lnzscript
AppUpdatesURL=https://github.com/moltenform/lnzscript
DefaultDirName={pf}\LnzScript 0.5
DefaultGroupName=LnzScript
AllowNoIcons=yes
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes
PrivilegesRequired=admin
ChangesAssociations=yes

[Files]
Source: "x:\rc\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs

[Icons]
Name: "{group}\LnzScript Editor"; Filename: "{app}\editor\lnzeditor.exe"
Name: "{group}\LnzScript Documentation"; Filename: "https://github.com/moltenform/lnzscript"

[Run]
; run right after installing
Filename: "{app}\editor\lnzeditor.exe"; Parameters: """{app}\examples\firstrun.jsz"""; Description: "{cm:LaunchProgram,LnzScript}"; Flags: nowait postinstall skipifsilent

[Registry]
Root: HKCR; Subkey: ".jsz"; ValueType: string; ValueName: ""; ValueData: "LnzScriptJSFile"; Flags: uninsdeletevalue
Root: HKCR; Subkey: "LnzScriptJSFile"; ValueType: string; ValueName: ""; ValueData: "LNZ Script"; Flags: uninsdeletekey
Root: HKCR; Subkey: "LnzScriptJSFile\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "%SystemRoot%\System32\WScript.exe,3"; Flags: uninsdeletekey
Root: HKCR; Subkey: "LnzScriptJSFile\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\lnzscript.exe"" ""%1"" %*" ; Flags: uninsdeletekey
Root: HKCR; Subkey: "LnzScriptJSFile\shell\edit\command"; ValueType: string; ValueName: ""; ValueData: """{app}\editor\lnzeditor.exe"" ""%1""" ; Flags: uninsdeletekey
Root: HKCR; Subkey: "LnzScriptJSFile\ShellEx\DropHandler"; ValueType: string; ValueName: ""; ValueData: "{{60254CA5-953B-11CF-8C96-00AA00B8708C}" ; Flags: uninsdeletekey

;ideal behavior: two verbs, open and edit. double-click will edit. drag/drop into will run. right-click:run to run.

;can make it launchable! http://stackoverflow.com/questions/142844/drag-and-drop-onto-python-script-in-windows-explorer   (that's what python uses too)
;http://mindlesstechnology.wordpress.com/2008/03/29/make-python-scripts-droppable-in-windows/


;"DefaultIcon" is the registry key that specifies the filename containing the icon to associate with the file type. ",0" tells Explorer to use the first icon from MYPROG.EXE. (",1" would mean the second icon.)

;"shell\open\command" is the registry key that specifies the program to execute when a file of the type is double-clicked in Explorer. The surrounding quotes are in the command line so it handles long filenames correctly.

;Subkeys of the verb subkey include the command line and the drop target method: command and DropTarget.
;http://msdn.microsoft.com/en-us/library/ee872121%28VS.85%29.aspx
