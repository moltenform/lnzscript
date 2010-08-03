
[Setup]
AppId={{C0D53206-64DE-4124-AA15-A7E4A1B82A68}
AppName=LnzScript
AppVersion=0.4
AppVerName=LnzScript 0.4
AppPublisher=GPL, http://b3nf.com, Ben Fisher
AppPublisherURL=http://b3nf.com/codepages/lnz/
AppSupportURL=http://b3nf.com/codepages/lnz/
AppUpdatesURL=http://b3nf.com/codepages/lnz/
DefaultDirName={pf}\LnzScript 0.4
DefaultGroupName=LnzScript
AllowNoIcons=yes
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes
PrivilegesRequired=admin
ChangesAssociations=yes

[Files]
Source: "C:\qt\launchorz\ltrunk\distribution\lnzscript\release-candidate\*"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\qt\launchorz\ltrunk\distribution\lnzscript\release-candidate\editor\*"; DestDir: "{app}\editor"; Flags: ignoreversion
Source: "C:\qt\launchorz\ltrunk\distribution\lnzscript\release-candidate\editor\license\*"; DestDir: "{app}\editor\license"; Flags: ignoreversion
Source: "C:\qt\launchorz\ltrunk\distribution\lnzscript\release-candidate\editor\properties\*"; DestDir: "{app}\editor\properties"; Flags: ignoreversion
Source: "C:\qt\launchorz\ltrunk\distribution\lnzscript\release-candidate\editor\tools\*"; DestDir: "{app}\editor\tools"; Flags: ignoreversion
Source: "C:\qt\launchorz\ltrunk\distribution\lnzscript\release-candidate\editor\tools\docviewer\*"; DestDir: "{app}\editor\tools\docviewer"; Flags: ignoreversion
Source: "C:\qt\launchorz\ltrunk\distribution\lnzscript\release-candidate\examples\*"; DestDir: "{app}\examples"; Flags: ignoreversion
Source: "C:\qt\launchorz\ltrunk\distribution\lnzscript\release-candidate\licenses\*"; DestDir: "{app}\licenses"; Flags: ignoreversion
;Source: "C:\qt\launchorz\ltrunk\distribution\lnzscript\release-candidate\tools\*"; DestDir: "{app}\tools"; Flags: ignoreversion
Source: "C:\qt\launchorz\ltrunk\distribution\lnzscript\release-candidate\tools\ahk_wininfo\*"; DestDir: "{app}\tools\ahk_wininfo"; Flags: ignoreversion
Source: "C:\qt\launchorz\ltrunk\distribution\lnzscript\release-candidate\tools\nir_winexp\*"; DestDir: "{app}\tools\nir_winexp"; Flags: ignoreversion


[Icons]
Name: "{group}\LnzScript Editor"; Filename: "{app}\editor\lnzeditor.exe"
Name: "{group}\LnzScript Documentation"; Filename: "http://b3nf.com/codepages/lnz/"

[Run]
;apparently this is to run right after installing
Filename: "{app}\editor\lnzeditor.exe"; Description: "{cm:LaunchProgram,LnzScript}"; Flags: nowait postinstall skipifsilent

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
