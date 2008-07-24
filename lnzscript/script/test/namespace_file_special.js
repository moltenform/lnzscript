
// File.emptyRecycleBin () works, at least on xp pro
// All of its arguments work

// File.tray('d','open') works
// File.driveMapAdd  works
// File.driveMapAddPersistant   works
// File.driveMapInformation    works

// File.ini*    works, except can return True when should return False

registerTest('File.getPathSpecial');
var arspecialtest=[
"Application Data",
"Application Data All Users",
"Cookies",
"Desktop",
"Favorites",
"Application Data Local Settings",
"My Documents",
"My Pictures",
"Program Files",
"Program Files Common",
"Recent Documents",
"Start Menu",
"Startup Items",
"System",
"Windows"];
function validate(strPath)
{
	if (!res || res.indexOf('\\')==-1 || !File.exists(res)) 
	{
		print('Failed:'+arspecialtest[i]); 
		assert(false);
	}
}for(var i=0; i<arspecialtest.length;i++) { validate(File.getPathSpecial(arspecialtest[i])); }
assertFails(function(){File.getPathSpecial('sdfsd')});

registerTest('File.getPathTemp');
validate(File.getPathTemp());
registerTest('File.getPathHome');
validate(File.getPathHome());

registerTest('File.openExplorerWindowSpecial');
var arspecialopentest=[["Control Panel","Control Panel"],
["Fonts","Fonts"],
//~ ["Printers","Printers"],
["My Computer","My Computer"],
["My Documents","My Documents"],
["My Network Places","My Network Places"],
["Network Computers","Search Results"], //Note, strange name,not really expected. Search Results-Computers ?
["Network Connections","Network Connections"],
["Printers and Faxes","Printers and Faxes"],
["Recycle Bin","Recycle Bin"],
["Scheduled Tasks","Scheduled Tasks"]];
for(var i=0; i<arspecialopentest.length; i++) { testOpenWindow(File.openExplorerWindowSpecial, arspecialopentest[i][0],arspecialopentest[i][1]); }
assertFails(function(){File.openExplorerWindowSpecial('sdfsd')});


registerTest('File.driveMapDialog');
File.driveMapDialog(); Time.sleep(800);
assert(Window.exists('Map Network'));
Window.close('Map Network');

