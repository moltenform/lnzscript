// see 

[Setup]
PrivilegesRequired=admin 


[Registry]
Root: HKCR; Subkey: ".jsz"; ValueType: string; ValueName: ""; ValueData: "LaunchorzLnzScript"; Flags: uninsdeletevalue 
Root: HKCR; Subkey: "LaunchorzLnzScript"; ValueType: string; ValueName: ""; ValueData: "Launchorz Js Script"; Flags: uninsdeletekey 
Root: HKCR; Subkey: "LaunchorzLnzScript\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{system32}\WScript.exe,3" 
Root: HKCR; Subkey: "LaunchorzLnzScript\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\testinterfaceconsole.exe"" /fconfirm ""%1""" 

