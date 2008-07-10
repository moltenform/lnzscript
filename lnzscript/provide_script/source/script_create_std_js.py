import sys
import os

# Syntax:
# script_create_std_js mypath outputpath

mypath = os.path.abspath(sys.argv[1])
outpath = os.path.abspath(sys.argv[2])

#start output file
os.chdir(outpath)
fout = open('std.js','w')

# Set the working directory to the first parameter passed to me
os.chdir(mypath)

#navigate to scripts directory
os.chdir('..\\..\\script\\provide')

#combine all of the js files into output
allfiles = os.listdir('.')
nWritten = 0
for file in allfiles:
	if file.endswith('.js'):
		f=open(file,'r')
		fout.write(f.read())
		f.close()
		nWritten += 1

fout.close()
if nWritten==0:
	raise Exception, 'No js files were found.'
	