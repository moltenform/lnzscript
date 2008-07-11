
// Note the syntax for functions:
// function my_private_fn(a,b) { } // will be private
// my_public_fn = function(a,b) { } // will be exported

include('framework.js');
include('methods_list.js');

print('Beginning main tests\n\n');
File.cd('temp'); // to make temporary files and so on

// uncomment the tests you wish to run.
//include('..\\namespace_clipboard.js');
//include('..\\namespace_file.js');




methods_list_summary();
print('');