


class IFaceFn():
	docs = ''
	type = None #fun,set,get. no vals.
	returntype = None
	name = None
	args = None
	num = None


def iface_get(starget, fSort=False):
	f = open(starget,'r').read()
	lines = f.replace('\r\n','\n').split('\n')
	i = 0
	out = []
	for line in lines:
		if line.startswith('fun') or line.startswith('set') or line.startswith('get'):
			o = IFaceFn()
			line = line.strip()
			if lines[i-1].startswith('#'): 
				o.docs += lines[i-1]
				if lines[i-2].startswith('#'): o.docs = lines[i-2] + o.docs
			spl = line.split()
			o.type = spl[0]
			o.returntype = spl[1]
			o.name = spl[2].split('=')[0]
			args = line.split('=')[1]
			o.args = '('+args.split('(')[1]
			o.num =  args.split('(')[0]
			out.append(o)
				
		i+=1
	
	if fSort:
		out.sort(key=lambda f: f.type + f.name)
	return out
	
	