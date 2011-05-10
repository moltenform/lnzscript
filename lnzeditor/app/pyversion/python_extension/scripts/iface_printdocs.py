
from iface_get import iface_get

def go(starget, starget2):
	print '''
# Constants, from IFaceTable.cxx
ScApp.SCFIND_WHOLEWORD
ScApp.SCFIND_MATCHCASE 
ScApp.SCFIND_WORDSTART 
ScApp.SCFIND_REGEXP
ScApp.SCFIND_POSIX
...many others...

# ScApp methods
ScApp.Trace(s)
ScApp.MsgBox(s)
ScApp.OpenFile(s)
ScApp.GetProperty(s)
ScApp.SetProperty(s, v)
ScApp.UnsetProperty(s)
ScApp.UpdateStatusBar(bUpdateSlowData)

# Menu commands'''
	f=open(starget2,'r')
	isStart=False
	out = []
	for line in f:
		if not isStart:
			if 'rgFriendlyNamedIDMConstants[] =' in line:
				isStart = True
		else:
			if '};' in line:
				break
			else:
				out.append(line.split('",')[0].replace('{"',''))
	assert isStart
	for part in out:
		#~ print 'void\tScApp.fn'+part+'()'
		print 'ScApp.fn'+part+'()'
	f.close()
	
	print '''
# Pane methods (all apply to ScOutput as well)
ScEditor.Append(txt)
ScEditor.Insert(npos, txt)
ScEditor.Remove(npos1, npos2)
ScEditor.Textrange(npos1, npos2)
ScEditor.FindText(s,n1=0,n2=-1,wholeWord=False,matchCase=False,regExp=False, nFlags=0)

	'''
	
	out = iface_get(target)
	
	
	okPrefix = {'Annotation':1, 'AutoC':1, 'Indic':1, 'Margin':1, 'Style':1, 'CallTip':1}
	for o in out:
		if o.name=='AddRefDocument': continue
		sname = 'fn'+o.name if o.type=='fun' else o.name
		
		# I see what they mean by putting Annotation, AutoC together... though..
		
		if o.type == 'get':
			if not o.name.startswith('Get'):
				if o.name.split('Get')[0] in okPrefix:
					sname = 'Get' + o.name.replace('Get', '')
				elif o.name=='LinesOnScreen': sname = 'Get' + o.name
				elif o.name=='SelectionIsRectangle': sname = 'Get' + o.name
				else:
					print 'fail: '+o.name
					return
		if o.type == 'set':
			if not o.name.startswith('Set'):
				if o.name.split('Set')[0] in okPrefix:
					sname = 'Set' + o.name.replace('Set', '')
				elif o.name=='CallTipUseStyle': sname = 'Set' + o.name
				else:
					print 'fail: '+o.name
					return
		
		if 'stringresult' not in o.args:
			rettype=o.returntype.replace('position','pos')
			print rettype + '\tScEditor.'+sname + o.args.replace(',)',')')
		else:
			assert o.returntype=='int'
			sargs = o.args.split(',')[0] + ')'
			
			print 'string' + '\tScEditor.'+sname + sargs
		
		if o.docs: print o.docs.replace('#','')
	
	# now the scapp ones
	


#~ target = r'C:\pydev\hackscite\scintilla\include\Scintilla.iface'
#~ target2 = r'C:\pydev\hackscite\scite\src\pythonextension.cxx'
target = r'C:\Users\bfisher\Desktop\scite1\1newer1\scintilla_include\Scintilla.iface'
target2 = r'C:\Users\bfisher\Desktop\scite1\1newer1\src\pythonextension.cxx'
go(target, target2)


