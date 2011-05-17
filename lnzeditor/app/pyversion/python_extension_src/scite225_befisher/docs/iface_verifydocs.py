
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

def parseArgs(entry):
	out = []
	out.append('iface_'+entry.returntype)
	arg1, arg2 = entry.args.replace('(','').replace(')','').split(',')[0:2]
	arg1 = arg1.strip(); arg2 = arg2.strip()
	out.append('iface_void' if not arg1 else 'iface_'+arg1.split()[0])
	out.append('iface_void' if not arg2 else 'iface_'+arg2.split()[0])
	return out

def go(target, targettable,modifyEntries = False):
	
	out = iface_get(target, fSort=False)
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
			#correct it
			print 'INCORRECT (should be fn), ',entry.name,entry.type
			if modifyEntries: entry.type = 'fun'
		
		ifaceargs = parseArgs(entry)
		if spl[2].strip()=='iface_length': spl[2]='iface_int'
		if spl[3].strip()=='iface_length': spl[3]='iface_int'
		if spl[4].strip()=='iface_length': spl[4]='iface_int'
		expectEqual(ifaceargs[0], spl[2].strip(),spl)
		expectEqual(ifaceargs[1], spl[3].strip(),spl)
		expectEqual(ifaceargs[2], spl[4].strip(),spl)
		
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
				raise 'incorrect'
			if name!=entry.name:
				print 'INCORRECT: name %s should be %s'%(entry.name, name)
				if modifyEntries: entry.name = name
			#verify args
			ifaceargs = parseArgs(entry)
			
			expectEqual( ifaceargs[2], 'iface_void') #other param null
			expectEqual(ifaceargs[0], spl[3].strip(),spl) #value is value
			expectEqual(ifaceargs[1], spl[4].strip(),spl)
			
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
				raise 'incorrect (is set)'
			if name!=entry.name:
				print 'INCORRECT: name %s should be %s'%(entry.name, name)
				if modifyEntries: entry.name = name
			
			#verify args
			ifaceargs = parseArgs(entry)
			expectEqual(ifaceargs[0], 'iface_void',spl) #setters should return void
			if ifaceargs[2]=='iface_void':
				expectEqual(ifaceargs[1], spl[3].strip(),spl)
			else:
				expectEqual(ifaceargs[1], spl[4].strip(),spl)
				expectEqual(ifaceargs[2], spl[3].strip(),spl)

			entry.found = True
		
		
	#were all the entries found?
	for o in out:
		if o.found != True:
			print 'undocumented', o
	
	assert i== len(out)
	print 'done', len(out)
	
	return out #returns the modified entries. has corrections.

def expectEqual(v, vExpected, sContext=None):
	if v != vExpected:
		if sContext: print sContext
		print 'fail: Expected '+str(v) + ' but got '+str(vExpected)
		#~ raise 'stop'
	else:
		pass
		#~ print 'pass: '+str(v) + ' == '+str(vExpected)

def expectNotEqual(v, vExpected, sContext=None):
	if v == vExpected:
		if sContext: print sContext
		print 'fail: Expected '+str(v) + ' not to equal '+str(vExpected)
		#~ raise 'stop'
	else:
		pass
		#~ print 'pass: '+str(v) + ' != '+str(vExpected)


if __name__=='__main__':
	target = r'..\scintilla\include\Scintilla.iface'
	targettable = r'..\scite\src\ifacetable.cxx'
	go(target, targettable )


