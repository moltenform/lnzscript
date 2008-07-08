
// test File.cd and File.getPathTemp
registerTest('File.cd');
var strPreviousPath = File.cd();
assert(strPreviousPath);

registerTest('File.getPathTemp');
var strTempPath = File.getPathTemp();
assert(strTempPath && File.isDirectory(strTempPath));

if (File.exists('namespace_file_test.txt')) File.removeFile('namespace_file_test.txt');
File.writeFile('namespace_file_test.txt','Creating file here');
if (!File.exists('namespace_file_test.txt'))
	abort('We should have created this file in system temp.');

// the file we created shouldn't be here
File.cd(strPreviousPath);
if (File.exists('namespace_file_test.txt'))
	abort('File should have been created in system temp directory, not here.');
	
if (File.isDirectory('namespace_file_testdir'))
	abort('Remnants of test. Please delete namespace_file_testdir folder.');

// test getting paths
registerTest('File.getPathHome');
var strHomePath = File.getPathTemp();
assert(strTempPath && File.isDirectory(strTempPath));

// now do basic file tests


methods_list_summary_namespace('File');