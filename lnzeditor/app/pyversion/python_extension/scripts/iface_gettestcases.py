
import sys
import iface_verifydocs

from iface_get import iface_get

def go(starget, starget2, targettable):
	out = iface_verifydocs.go(target, targettable,modifyEntries = True)
	
	for o in out:
		o.sortkey = iface_verifydocs.parseArgs(o)
		o.sortkey.insert(0, o.type)
		
	
	# look for . also verify correct args in the 
	out.sort(key = lambda o: (tuple(o.sortkey)))
	
	for o in out:
		print o.sortkey, o.name
	
'''to test:
['fun', 'iface_bool', 'iface_void', 'iface_void'] AutoCActive
or ['fun', 'iface_bool', 'iface_void', 'iface_void'] CallTipActive
['fun', 'iface_colour', 'iface_void', 'iface_void'] GetHotspotActiveBack

'''
	
	


target = r'C:\Users\bfisher\Desktop\scite1\scitepy25\scintilla\include\Scintilla.iface'
target2 = r'C:\Users\bfisher\Desktop\scite1\scitepy25\scite\src\pythonextension.cxx'
targettable = r'C:\Users\bfisher\Desktop\scite1\scitepy25\scite\src\ifacetable.cxx'
go(target, target2,targettable)



