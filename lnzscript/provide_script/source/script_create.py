qtconversion = { 'int':'toInt32()', 'bool':'toBoolean()', 'string':'toString()'} #'double':'Number()', - need to find right method for this

qtconversiontypecheck = { 'int':'isNumber()', 'bool':'isBoolean()', 'string':'isString()'}
qtconversiontypeconstant = { 'int':'LNZTYPE_int', 'bool':'LNZTYPE_bool', 'string':'LNZTYPE_string'}
cpptypes = { 'int':'int', 'bool':'bool', 'string':'QString'}

class ExposedFunctionArg():
	def __init__(self, arg, n, bOptional=False):
		if not bOptional:
			self.type, self.name = arg.strip().split(' ')
			if self.type not in qtconversion: raise 'Unknown type,'+self.type
			self.n = n
		else:
			tmp, self.defaultValue = arg.strip().split('=')
			self.type, self.name = tmp.strip().split(' ')
			if self.type not in qtconversion: raise 'Unknown type,'+self.type
			self.n = n
	def isWindowArg(self):
		if self.type=='string' and self.name=='window': return True
		else: return False
	def renderCheckCorrectType(self, strFnName):
		if self.isWindowArg(): return ''
			
		method = qtconversiontypecheck[self.type] # isString()
		return 'if (!ctx->argument(%d).%s)'%(self.n,method) +' return g_ExceptionWrongTypeArg(ctx,FUNCTIONNAME,%d,%s);'%(self.n, qtconversiontypeconstant[self.type])

	def renderAssignVar(self, strFnName):
		if self.isWindowArg():  return 'QScriptValue sv_val_window(ctx->argument(%d)); QString window(util_Au3WindowParseAndSetMode(sv_val_window)); QString strText(util_Au3WindowGetTextParamFromObj(sv_val_window));'%self.n
		
		method = qtconversion[self.type] # toString()
		return '%s %s = ctx->argument(%d).%s;' % (cpptypes[self.type], self.name, self.n, method)
		
	def renderAssignVarOptional(self, strFnName):
		method = qtconversion[self.type] # toString()
		return 'if (ctx->argumentCount()>=%d)'%(self.n+1)  + ' {\n\t\t' + self.renderCheckCorrectType(strFnName) + '\n\t\t%s = ctx->argument(%d).%s;}' % (self.name, self.n, method)

class ExposedFunction():
	namespace = ''
	functionname = ''
	doc = ''
	example = ''
	args = ''
	returns = ''
	implementation = None
	instanceMethod = False
	def getImplName(self):
		return 'impl_' + self.namespace.lower() + '_' + self.functionname.lower()
	
	codeArray = None
	def __init__(self):
		self.codeArray = []
		

		
	def buildCheckArguments(self):
		astrResult = []
		largs = self.args.split(',')
		astrResult.append('const char* FUNCTIONNAME = "%s.%s";'%(self.namespace, self.functionname))
		if self.args=='':
			astrResult.append('\t' + 'if (ctx->argumentCount()!=%d) return g_ExceptionWrongNumberArgs(ctx,FUNCTIONNAME,%d);' % (0, 0));
		elif '=' not in self.args: #simple case, no optional arguments
			astrResult.append('\t' + 'if (ctx->argumentCount()!=%d) return g_ExceptionWrongNumberArgs(ctx,FUNCTIONNAME,%d);' % (len(largs), len(largs)));
			aArgs = [ExposedFunctionArg(largs[i], i) for i in range(len(largs))]
			#render type checks
			for arg in aArgs:
				astrResult.append('\t' + arg.renderCheckCorrectType(self.functionname))
			#render assignments
			for arg in aArgs:
				astrResult.append('\t' + arg.renderAssignVar(self.functionname))
			
		else:
			#note optional must come last. This should be checked.
			Aargs = []
			AoptionalArgs = []
			
			for i in range(len(largs)):
				if '=' in largs[i]:
					AoptionalArgs.append( ExposedFunctionArg(largs[i], i, True) )
				else:
					Aargs.append( ExposedFunctionArg(largs[i], i) )
			
			# just for conveniance, accept too many arguments. Maybe fix later.
			#so you should have at least len( Aargs)
			if len(Aargs)>0:
				astrResult.append('\t' + 'if (ctx->argumentCount()<%d) return g_ExceptionNotEnoughArgs(ctx,FUNCTIONNAME,%d);' % (len(Aargs), len(Aargs)));
			astrResult.append('\t' + 'if (ctx->argumentCount()>%d) return g_ExceptionTooManyArgs(ctx,FUNCTIONNAME,%d);' % (len(AoptionalArgs)+len(Aargs), len(AoptionalArgs)+len(Aargs)));
			
			# Do non-optional arguments
			#render type checks
			for arg in Aargs: astrResult.append('\t' + arg.renderCheckCorrectType(self.functionname))
			#render assignments
			for arg in Aargs: astrResult.append('\t' + arg.renderAssignVar(self.functionname))
			
			# Do optional arguments
			for arg in AoptionalArgs:
				astrResult.append('\t' + '%s %s = %s;'%(cpptypes[arg.type], arg.name, arg.defaultValue))
				astrResult.append('\t' + arg.renderAssignVarOptional(self.functionname))
			
		return '\n'.join(astrResult)
		
	def checkValidity(self):
		if self.implementation==None:
			raise Exception, 'no implementation found for function %s.'%self.functionname
		if self.args != '' and not self.implementation.startswith('Javascript'):
			#First check all args are used
			allcode = ' '.join(self.codeArray)
			for arg in self.args.split(','):
				arg = arg.strip()
				arg = arg.split('=')[0].strip()
				argtype, argname = arg.split(' ')
				if argname not in allcode:
					raise Exception, 'Error - Argument not used in function %s: type %s name %s' % (self.functionname, argtype, argname)
			#Now check that optional args can't be before required args.
			bprev = 'mandatory'
			for arg in self.args.split(','):
				bcurrent = 'opt' if ('=' in arg) else 'mandatory'
				if bcurrent=='mandatory' and bprev=='opt':
					raise Exception, 'Error - Optional arguments cannot be followed by mandatory args, in function %s , arg %s' %(self.functionname, arg)
				bprev = bcurrent
			
	def renderHeader(self):
		strImplName = self.getImplName()
		return ('QScriptValue %s(QScriptContext *ctx, QScriptEngine *eng);'%strImplName)
		
	def renderCode(self):
		astrResult = []
		astrResult.append(self.renderHeader().rstrip(';'))
		for line in self.codeArray:
			if line.strip() == 'CHECK_ARGS':
				astrResult.append(self.buildCheckArguments())
			else:
				astrResult.append(line)
		return '\n'.join(astrResult)
		

def parseParamEntry(s):
	param, data = s.split(':',1)
	return param.replace('///','').strip(), data.strip()


def processAllSource():
	# return array of all results 
	import os
	aresults = []
	files = os.listdir('.')
	for file in files:
		if file.startswith('exposed') and file.endswith('.cpp'):
			s = readfile(file)
			parse(s, aresults)
			
	return aresults

def parse(s, AllExposed = None):
	
	
	if AllExposed==None: AllExposed = []
	
	currentFn = None
	lines = s.replace('\r\n','\n').split('\n')
	for line in lines:
		if line.strip()=='' and currentFn==None:
			continue
		if line.strip().startswith('//') and not line.startswith('///') and currentFn==None:
			continue
		if line.startswith('///'):
			param, data = parseParamEntry(line)
			if param=='Function':
				print '... '+data
				currentFn = ExposedFunction()
				currentFn.namespace, currentFn.functionname = data.split('.')
			elif param=='Arguments':
				currentFn.args = data #don't parse yet
			elif param=='Doc':
				currentFn.doc = data #don't parse yet
			elif param=='Example':
				currentFn.example = data
			elif param=='Returns':
				currentFn.returns = data #don't parse yet
			elif param=='Implementation':
				currentFn.implementation = data
			elif param=='InstanceMethod':
				if data=='true': currentFn.instanceMethod=True
				elif data=='false': currentFn.instanceMethod=False
				else: raise Exception, 'Function %s, instanceMethod parameter should be true or false, not %s' %(currentFn.functionname, data)
			else:
				raise 'Param not recognized: '+param
			
		#deal with this later
		#elif line.strip()=='CHECK_ARGS':
			#
			
		elif line.rstrip()=='}' or line.strip()=='{}': #note, don't cut at the close of a loop, only when there is no whitespace before it
			currentFn.codeArray.append(line)
			AllExposed.append(currentFn)
			currentFn.checkValidity()
			currentFn = None
		else:
			currentFn.codeArray.append(line)
			
	return AllExposed

def readfile(filename):
	f = open(filename)
	s = f.read()
	f.close()
	return s


if __name__=='__main__':
	testin = '''
///Function:Process.setCredentials
///Arguments:string strUser, string strDomain, string strPassword
///Doc: Allows subsequent Process functions to run as a different user
///Implementation:c++_au3
{
	CHECK_ARGS
	
	long res;
	res = AU3_Shutdown(strUser, strDomain, strPassword);
	return (res) ? QScriptValue(eng, true) : QScriptValue(eng, false);	
}

///Function:Process.sysLogoff
///Arguments:bool bForce=false
///Returns:bool bSuccess
///Doc:Windows logoff, pass a value of true to be more forceful. Returns true if successful and false otherwise.
///Implementation:c++_au3
{
	CHECK_ARGS
	res = AU3_Shutdown(bForce);
}

///Function:Process.waitClose
///Arguments:string processName, int timeout=0
///Returns:bool bTimedout
///Doc:Windows logoff, pass a value of true to be more forceful. Returns true if successful and false otherwise.
///Implementation:c++_au3
{
	CHECK_ARGS
	res = AU3_ProcessWaitClose(processName, timeout);
}

///Function:Test.noArgs
///Arguments:
///Returns:int nTemp
///Doc:No return val
///Implementation:c++_au3
{
	CHECK_ARGS
	res = AU3_DoSomething(strTmp, nTemp);
}
'''
	r = parse(testin)
	for fn in r:
		print fn.renderCode()

