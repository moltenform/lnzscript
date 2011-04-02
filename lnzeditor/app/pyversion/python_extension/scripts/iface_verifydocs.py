
from iface_get import iface_get

def getIfacetablecxx(targettable, prefix):
	f=open(targettable,'r')
	isStart=False
	out = []
	for line in f:
		if not isStart:
			if prefix in line:
				isStart = True
		else:
			if '};' in line:
				break
			else:
				line = line.strip()
				assert line.startswith('{"')
				line=line.replace('"','').replace('{','').replace('}','')
				out.append(line)
	assert isStart
	f.close()
	return out

def go(target, targettable ):
	
	out = iface_get(target)
	#make dictionary of iface
	dictiface = {}
	for o in out:
		o.found = False
		dictiface[o.name] = o
	
	misleadingNames = []
	i=0
	listSciFns = getIfacetablecxx(targettable, 'static IFaceFunction ifaceFunctions[] =')
	for ln in listSciFns:
		i+=1
		spl = ln.split(',')
		name = spl[0].strip()
		if name.startswith('Get') or name.startswith('Set'):
			misleadingNames.append(name)
		entry = dictiface[name]
		if entry.type!='fun':
			print 'incorrect, ',entry.name,entry.type
		entry.found = True
	
	print 'dictIsScintillaFnNotProperty = {'
	for nm in misleadingNames: print '"%s":True,'%nm,
	print '}'
	print '-'
	hackPrefix = ('Annotation', 'AutoC', 'Indic', 'Margin', 'CallTip','Style') #should try Annotation before trying Style
	listSciProps = getIfacetablecxx(targettable, 'static IFaceProperty ifaceProperties[] =')
	for ln in listSciProps:
		spl = ln.split(',')
		pname = spl[0].strip()
		hasGet = spl[1].strip() != '0'
		hasSet = spl[2].strip() != '0'
		if hasGet:
			i+=1
			name = 'Get'+pname
			entry = None
			if name not in dictiface:
				if pname in ('LinesOnScreen','SelectionIsRectangle') :
					entry = dictiface[pname]
				else:
					for k in hackPrefix:
						if k in name:
							tname = k+name.replace(k,'')
							if tname not in dictiface:
								print k, ln
							entry = dictiface[tname]
							break
				if not entry:
					print ln; 
					raise 'not found'
			else:
				entry = dictiface[name]
			if entry.type!='get':
				print 'incorrect (is get), ',entry.name,entry.type
			entry.found = True
			
		if hasSet:
			i+=1
			name = 'Set'+pname
			entry = None
			if name not in dictiface:
				if pname in ('CallTipUseStyle') :
					entry = dictiface[pname]
				else:
					for k in hackPrefix:
						if k in name:
							tname = k+name.replace(k,'')
							if tname not in dictiface:
								print k, ln
							entry = dictiface[tname]
							break
				if not entry:
					print ln
					raise 'not found'
			else:
				entry = dictiface[name]
			
			if entry.type!='set':
				print 'incorrect (is set), ',entry.name,entry.type
			entry.found = True
		
		
	#were all the entries found?
	for o in out:
		if o.found != True:
			print 'undocumented', o
	
	assert i== len(out)
	print 'done', len(out)
	
	
	
target = r'C:\Users\bfisher\Desktop\scite1\1newer1\scintilla_include\Scintilla.iface'
targettable = r'C:\Users\bfisher\Desktop\scite1\1newer1\src\ifacetable.cxx'
go(target, targettable )

