//# runcmd

print('Running tests for namespace System.')

/*
registerTest('System.getenv');
var tempdir = System.getenv('TEMP');
assert(tempdir && tempdir.length > 2 );
assert(File.exists(tempdir));

alert('Note: the computer will appear to "freeze" for 4 seconds. This is expected. Use Ctrl+Alt+Delete if the system remains frozen.');
registerTest('System.disableInput');
registerTest('System.enableInput');
System.disableInput()
Time.sleep(4000)
System.enableInput()

registerTest('System.openEjectHardware');
System.openEjectHardware(); Time.sleep(800);
assert(Window.exists('Safely Remove'));
Window.close('Safely Remove');
*/


//~ registerTest('System.getenv');
//~ var strVersion = System.windowsVersion();
//~ var objVersion = {'5.0':'Windows2000', '5.1':'WindowsXP','6.0':'Vista','5.2':'Win server 2003','6.1':'Win7'};
//~ var isVista = (strVersion=='6.0')
//~ var strOs = objVersion[strVersion]===null ? 'Unknown' : objVersion[strVersion];
//~ assert(confirm('Your os is:'+strOs));

//~ registerTest('System.openControlPanel');
//~ System.openControlPanel( ControlPanel.ActionCenter)
//~ System.openControlPanel( ControlPanel.DateAndTime)
//~ System.openControlPanel( ControlPanel.ProgramsAndFeatures)
//~ System.openControlPanel( ControlPanel.UserAccounts)

//works.
//~ System.openControlPanel(ControlPanelXp.Keyboard)
//~ System.openControlPanel(ControlPanelXp.AddRemove)
//~ System.openControlPanel(ControlPanelXp.Accounts)
//~ System.openControlPanel(3) //Expected a ControlPanel.
//~ System.openControlPanel('3') //Unknown Ctrlpanel
//~ System.openControlPanel() //

//~ File.openExplorerWindowSpecial(SpecialFolder.MyDocuments)
//~ File.openExplorerWindowSpecial(SpecialFolder.ControlPanel)
print(File.getPathSpecial(SpecialFolder.MyDocuments))
print(File.getPathSpecial(SpecialFolder.Favorites))
print(File.getPathSpecial(SpecialFolder.MyPictures))
//~ print(File.getPathSpecial(SpecialFolder.MyMusic))
//~ print(File.getPathSpecial(SpecialFolder.MyVideo))
print(File.getPathSpecial(SpecialFolder.StartMenu))
//~ File.getPathSpecial(SpecialFolder.ControlPanel)

/*
registerTest('System.isAdmin');
assert(confirm(System.isAdmin() ? 'You are an admin.':'You are not an admin'));

registerTest('System.openControlPanel');
var arControlPanelTests=[
//~ // Input to fn,   Resulting window name. May need modification on Vista.
["Keyboard", "Keyboard Properties"],
["Mouse", "Mouse Properties"],
["Joystick", "Game Controllers"],
["Multimedia", (isVista?'Sound' : "Sounds and Audio")],
["Internet Options", "Internet Properties"],
["Add/Remove", (isVista?'Control Panel\\Programs' : "Add or Remove") ],
["Regional", "Regional"],
["Time", "Date and Time"],
["System", "System"],
["Display", "Display"],
["Accessibility", (isVista?'Control Panel\\Ease of Access' : "Accessibility") ],
["Network", (isVista?'Control Panel\\Network' : "Network") ],
["Power", (isVista?'Control Panel\\Power' : "Power") ],
["Accounts", (isVista?'Control Panel\\User' : "User Accounts") ],
["Security Center", "Windows Security Center"],
["Firewall", "Windows Firewall"],
["Wireless", "Wireless"],
["Taskbar", "Taskbar"],
["Folder Options", "Folder Options"],
["Device Manager", "Device Manager"],
["Updates", (isVista?'Control Panel\\Windows Update' : "Automatic Updates") ]]
for(var i=0; i<arControlPanelTests.length; i++) { testOpenWindow(System.openControlPanel, arControlPanelTests[i][0],arControlPanelTests[i][1]); }
*/

/*
var aropenUtilityTests= [ 
 ["Disk Cleanup", "Select Drive") ],
["Disk Management", "Disk Management"],
["Services", "Services"],
["Computer Management", "Computer Management"],
["Administrative Tools", "Administrative Tools"],
["Event Viewer", "Event Viewer"]]
for(var i=0; i<aropenUtilityTests.length; i++) { testOpenWindow(System.openUtility, aropenUtilityTests[i][0],aropenUtilityTests[i][1]); }
*/



//~ if (confirm('Install screensaver?'))
//~ {
//~ registerTest('System.installScreensaver');
//~ System.installScreensaver('..\\testfiles\\ssbeniercurves.scr');
//~ }

//~ methods_list_summary_namespace('System');