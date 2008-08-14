// Note the syntax for functions in included files:
// function fn(a,b) { } // will be private
// fn = function(a,b) { } // will be exported
// var x=4; // will be private
// x=4; // will be exported
// Because these often rely on Window names, these tests will probably only pass on ENGLISH systems.
// Tests were developed on Windows xp professional. 

include('<std>');
include('framework.js');
include('methods_list.js');


// clear temporary files:
File.cd('temp');
var astrFiles = File.dirListFiles('.');
for (var i=0; i<astrFiles.length; i++)
	if (!File.removeFile(astrFiles[i]))
		print('Warning: could not remove file '+astrFiles[i]);
if (File.dirListFiles('.').length!=0) print('Warning: could not remove temporary files.');
	
print('Beginning main tests\n\n');

// uncomment the tests you wish to run.
//~ include('..\\namespace_clipboard.js');
//~ include('..\\namespace_dialog.js');
//~ include('..\\namespace_file.js');

//~ include('..\\namespace_system.js');
//~ include('..\\namespace_sound.js');
//~ include('..\\namespace_file_special.js');


methods_list_summary();
print('');