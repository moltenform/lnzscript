qtconversion = { 'int':'Int32()', 'bool':'Boolean()', 'string':'String()'} #'double':'Number()', - need to find right method for this
qtconversioncheck = { 'int':'Number()', 'bool':'Boolean()', 'string':'String()'}
def jsToQtType(s): return 'QString' if s=='string' else s 

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
	def renderCheckType(self, strFnName):
		#~ print 'Type:', self.type
		method = 'is' + qtconversioncheck[self.type] # .isString() .isNumber(), etc
		if self.isWindowArg(): return ''
		else: return 'if (!ctx->argument(%d).%s)'%(self.n,method) +' return ctx->throwError(QScriptContext::TypeError,"%s: argument %d is not a %s");'%(strFnName,self.n,self.type)
	def renderAssignVar(self, strFnName):
		method = 'to' + qtconversion[self.type] # .tosString() .toNumber(), etc
		if self.isWindowArg(): return 'QScriptValue sv_val_window=(ctx->argument(%d)); QString window = util_Au3WindowParseAndSetMode(sv_val_window), strText = util_Au3WindowGetTextParamFromObj(sv_val_window);'%self.n
		else: return '%s %s = ctx->argument(%d).%s;' % (jsToQtType(self.type), self.name, self.n, method)
	def renderAssignVarOptional(self, strFnName):
		method = 'to' + qtconversion[self.type] # .tosString() .toNumber(), etc
		return 'if (ctx->argumentCount()>=%d)'%(self.n+1)  + ' {\n\t\t' + self.renderCheckType(strFnName) + '\n\t\t%s = ctx->argument(%d).%s;}' % (self.name, self.n, method)

class ExposedFunction():
	namespace = ''
	functionname = ''
	doc = ''
	example = ''
	args = ''
	returns = ''
	implementation = 'c++_au3' #default implementation
	def getImplName(self): 
		return 'impl_' + self.namespace.lower() + '_' + self.functionname.lower()
	
	codeArray = None
	def __init__(self):
		self.codeArray = []
		

		
	def buildCheckArguments(self):
		astrResult = []
		largs = self.args.split(',')
		if self.args=='':
			astrResult.append('\t' + 'if (ctx->argumentCount()!=%d) return ctx->throwError("%s takes exactly %d argument(s).");' % (0, self.functionname, 0));
		elif '=' not in self.args: #simple case, no optional arguments
			astrResult.append('\t' + 'if (ctx->argumentCount()!=%d) return ctx->throwError("%s takes exactly %d argument(s).");' % (len(largs), self.functionname, len(largs)));
			aArgs = [ExposedFunctionArg(largs[i], i) for i in range(len(largs))]
			#render type checks
			for arg in aArgs:
				astrResult.append('\t' + arg.renderCheckType(self.functionname))
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
				astrResult.append('\t' + 'if (ctx->argumentCount()<%d) return ctx->throwError("%s takes at least %d argument(s).");' % (len(Aargs), self.functionname, len(Aargs)));
			
			# Do non-optional arguments
			#render type checks
			for arg in Aargs: astrResult.append('\t' + arg.renderCheckType(self.functionname))
			#render assignments
			for arg in Aargs: astrResult.append('\t' + arg.renderAssignVar(self.functionname))
			
			# Do optional arguments
			for arg in AoptionalArgs:
				astrResult.append('\t' + '%s %s = %s;'%(jsToQtType(arg.type), arg.name, arg.defaultValue))
				astrResult.append('\t' + arg.renderAssignVarOptional(self.functionname))
			
		return '\n'.join(astrResult)
		
	def checkValidity(self):
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
			elif param=='Example': #is this defined in C++, or C++Qt, or JavaScript?
				currentFn.example = data
			elif param=='Returns':
				currentFn.returns = data #don't parse yet
			elif param=='Implementation': #is this defined in C++, or C++Qt, or JavaScript?
				currentFn.implementation = data
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

testin = '''
///Function:Process.setCredentials
///Arguments:string strUser, string strDomain, string strPassword
///Doc: Allows subsequent Process functions to run as a different user
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
{
	CHECK_ARGS
	res = AU3_Shutdown(bForce);
}

///Function:Process.waitClose
///Arguments:string processName, int timeout=0
///Returns:bool bTimedout
///Doc:Windows logoff, pass a value of true to be more forceful. Returns true if successful and false otherwise.
{
	CHECK_ARGS
	res = AU3_ProcessWaitClose(processName, timeout);
}

///Function:Test.noArgs
///Arguments:
///Returns:int nTemp
///Doc:No return val
{
	CHECK_ARGS
	res = AU3_DoSomething(strTmp, nTemp);
}
'''
if __name__=='__main__':
	r = parse(testin)
	for fn in r:
		print fn.renderCode()

