# intended to be run in its own directory
fout = open('methods_list.txt', 'w')

import sys, os

sys.path.append(r'..\..\provide_script\source')
os.chdir(r'..\..\provide_script\source')

import script_create

aFunctions = script_create.processAllSource()

for currentFn in aFunctions:
	if currentFn.implementation != 'Javascript' and not currentFn.functionname.startswith('_'):
		print(str(currentFn.namespace) + ' ' + str(currentFn.functionname))
		fout.write(currentFn.namespace + '.' + currentFn.functionname + '\n')

fout.close()
