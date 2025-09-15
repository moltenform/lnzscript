import sys
import os

# Syntax:
# script_create_std_js mypath outputpath

mypath = os.path.abspath(sys.argv[1])
outpath = os.path.abspath(sys.argv[2])

#start output file
os.chdir(outpath)
fout = open('std.js', 'w')
fout.write('//This is a generated file. When LnzScript is built, changes to it will be lost.\n')
fout.write('//These functions are documented in exposed-global.cpp.\n\n')

# Set the working directory to the first parameter passed to me
os.chdir(mypath)

#navigate to scripts directory
os.chdir('..\\..\\script\\provide')

#combine all of the js files into output
allfiles = os.listdir('.')
allfiles.sort() #the ones beginning with z depend on earlier ones.
nWritten = 0
for file in allfiles:
	if file.endswith('.js'):
		f = open(file, 'r')
		fout.write(f.read())
		fout.write('\n')
		f.close()
		nWritten += 1

fout.close()
if nWritten == 0:
	raise Exception('No js files were found.')
