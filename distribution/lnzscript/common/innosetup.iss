
[Setup]
AppId={{C0D53206-64DE-4124-AA15-A7E4A1B82A68}
AppName=LnzScript
AppVersion=0.4
;AppVerName=LnzScript 0.4
AppPublisher=Ben Fisher
AppPublisherURL=http://b3nf.com/codepages/lnz/
AppSupportURL=http://b3nf.com/codepages/lnz/
AppUpdatesURL=http://b3nf.com/codepages/lnz/
DefaultDirName={pf}\LnzScript
DefaultGroupName=LnzScript
AllowNoIcons=yes
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes
PrivilegesRequired=admin

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\Program Files (x86)\Inno Setup 5\Examples\MyProg.exe"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\LnzScript"; Filename: "{app}\MyProg.exe"
Name: "{commondesktop}\LnzScript"; Filename: "{app}\MyProg.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\MyProg.exe"; Description: "{cm:LaunchProgram,LnzScript}"; Flags: nowait postinstall skipifsilent

[Registry]
Root: HKCR; Subkey: ".jsz"; ValueType: string; ValueName: ""; ValueData: "LnzScriptJSFile"; Flags: uninsdeletevalue
Root: HKCR; Subkey: "LnzScriptJSFile"; ValueType: string; ValueName: ""; ValueData: "LNZ Script"; Flags: uninsdeletekey
Root: HKCR; Subkey: "LnzScriptJSFile\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "%SystemRoot%\System32\WScript.exe,1"
Root: HKCR; Subkey: "LnzScriptJSFile\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\MYPROG.EXE"" ""%1"""
Root: HKCR; Subkey: "LnzScriptJSFile\ShellEx\DropHandler"; ValueType: string; ValueName: ""; ValueData: "{60254CA5-953B-11CF-8C96-00AA00B8708C}"

;can make it launchable! http://stackoverflow.com/questions/142844/drag-and-drop-onto-python-script-in-windows-explorer
;http://mindlesstechnology.wordpress.com/2008/03/29/make-python-scripts-droppable-in-windows/


;"DefaultIcon" is the registry key that specifies the filename containing the icon to associate with the file type. ",0" tells Explorer to use the first icon from MYPROG.EXE. (",1" would mean the second icon.)

;"shell\open\command" is the registry key that specifies the program to execute when a file of the type is double-clicked in Explorer. The surrounding quotes are in the command line so it handles long filenames correctly.


;Subkeys of the verb subkey include the command line and the drop target method: command and DropTarget.
;http://msdn.microsoft.com/en-us/library/ee872121%28VS.85%29.aspx
  ;  HKEY_CLASSES_ROOT
;  MyProgram.exe
 ;     shell
  ;       open
  ;          command
  ;             (Default) = C:\MyDir\MyProgram.exe /a "%1"
  ;       print
   ;         command
 ;              (Default) = C:\MyDir\MyProgram.exe /a /p "%1"
  ;       printto
  ;          command
 ;              (Default) = C:\MyDir\MyProgram.exe /a /p "%1" "%2"
