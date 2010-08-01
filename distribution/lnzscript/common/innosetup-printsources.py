
import os

#I didn't see a way to recursively add the entire directory, including subdirs, so I wrote this.

def visit(arg,dirname, names):
	#~ print dirname
	s= 'Source: "C:\qt\launchorz\ltrunk\distribution\lnzscript\%s\*"; DestDir: "{app}\%s"; Flags: ignoreversion'
	print s%(dirname,dirname.replace('release-candidate\\',''))

os.path.walk(  'release-candidate', visit, None)

