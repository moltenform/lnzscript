
#parses object_properties, and
# prints out the following
# 1) list of members seperated by [[br]], to be copied into exposed-file.cpp 's inline documentation
# 2) list of members separated by newline, for the editor .api autocomplete.

# as of 0.50, see compile.txt instead for instructions on how to generate the .api file

arWind=[]
arCpanel=[]
arCpanelXp=[]
arjSpecfolder=[]
f=open('object_properties.cpp')
for line in f:
	if line.startswith('objWindowStyle.setProperty('):
		arWind.append(line.split('"')[1])
	elif line.startswith('objCpanel.setProperty('):
		arCpanel.append(line.split('"')[1])
	elif line.startswith('objCpanelXp.setProperty('):
		arCpanelXp.append(line.split('"')[1])	
	elif line.startswith('objSpecfolder.setProperty('):
		arjSpecfolder.append(line.split('"')[1])
	
f.close()

if not arWind or not arCpanel or not arCpanelXp or not arjSpecfolder:
	raise "couldn't find one of the sections"

#1)
for ar in arWind,arCpanel,arCpanelXp, arjSpecfolder:
	print '[[br]]'.join(ar)

#2)
print '--------';
arWind.insert(0, 'WindowStyle')
arCpanel.insert(0, 'ControlPanel')
arCpanelXp.insert(0, 'ControlPanelXp')
arjSpecfolder.insert(0, 'SpecialFolder')
for ar in arWind,arCpanel,arCpanelXp, arjSpecfolder:
	for item in ar[1:]:
		print ar[0] + '.'+item
	
	