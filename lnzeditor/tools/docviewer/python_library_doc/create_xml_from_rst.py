#Ben Fisher, 2008
#Launchorz, GPL

#Creates xml from a psuedo-restructured text format
#This code isn't pretty or documented, see readme.txt for rationale

import os
import re

os.chdir('source')

class Section_repr():
    name = ''
    doc = ''
    namespaces = None
    def __init__(self, strName):
        self.namespaces = []
        self.name = strName

class Namespace_repr():
    name = ''
    doc = ''
    docArray = None
    functions = None
    def __init__(self, strName):
        self.functions = []
        self.docArray = []
        self.name = strName
    def consolidateDoc(self):
        self.doc = ''.join(self.docArray).replace('    ','\t').replace('  ',' ').strip()
        del self.docArray

class Function_repr():
    name = ''
    doc = ''
    syntax = ''
    static = True
    docArray = None
    def __init__(self, strName):
        self.functions = []
        self.docArray = []
        self.name = strName
    def consolidateDoc(self):
        self.doc = ''.join(self.docArray).replace('    ','\t').replace('  ',' ').strip()
        del self.docArray



def xmlescape(s):
    return s.replace('&','&amp;').replace('<','&lt;').replace('>','&gt;').replace('"','&quot;').replace("'",'&apos;')
    
reRstDirective = re.compile(r':[^ \r\n\t]+:')
reIndex = re.compile(r'\.\. index::.*?\n\s*\n',re.DOTALL)
reComment = re.compile(r'\.\. XXX.*?\n',re.DOTALL)

#If it was added in 2.6, that's important-keep it. Otherwise, strip it.
reVersion = re.compile(r'\.\. version((added)|(changed))::(?! 2\.6).*?\n',re.DOTALL)

def unstructuretext(s):
    s = reIndex.sub('\n',s)
    s = reComment.sub('\n',s)
    s = reVersion.sub('',s)
    return reRstDirective.sub('', s).replace('``','').replace('   .. note::','Note:') #remove :func: and so on. Remove ``literal`` marks


def process(fout, s):
    #Turn pseudo-restructured text into an xml file. Creates in memory, then writes to fout.
    #first, create memory representation
    arSections = []
    lines = unstructuretext(s.replace('\r\n','\n')).split('\n')
    currentSection = None
    currentNamespace = None
    currentFunction = None
    bInModDocumentation = bInFnDocumentation = False
    for line in lines:
        if not bInModDocumentation and not bInFnDocumentation and line.strip()=='':
            continue
        if not bInModDocumentation and not bInFnDocumentation and line.startswith('//'):
            continue
        if line.startswith('==='):
            param, data = splitheader(line)
            if param=='Section':
                
                currentSection = Section_repr(data)
                arSections.append(currentSection)
            elif param=='Mod':
                bInFnDocumentation = False
                #consolidate previous module's doc
                if currentNamespace: currentNamespace.consolidateDoc()
                
                currentNamespace = Namespace_repr(data)
                currentSection.namespaces.append(currentNamespace)
            elif param=='ModDoc':
                bInModDocumentation = True
            elif param=='EndDoc':
                bInModDocumentation = False
        elif line.startswith('// '):
            continue # a comment
        elif line.lstrip().startswith('.. function::') or line.lstrip().startswith('.. method::'):
            if bInModDocumentation: raise Exception, 'not allowed- function inside module docs ' + line
            bInFnDocumentation = True
            header, syntax = line.split('::')
            syntax = syntax.strip()
            if '.' in syntax and syntax.index('.')<(syntax.index('(') if '(' in syntax else 9999): syntax = syntax[syntax.index('.')+1:]
            
            fnname = syntax.split('(')[0] if not syntax.startswith('(') else syntax
            #~ if '.' in fnname: fnname = fnname.split('.')[-1] #if input is str.split , name is split
            #consolidate previous function's doc
            if currentFunction: currentFunction.consolidateDoc()
            
            currentFunction = Function_repr(fnname)
            currentNamespace.functions.append(currentFunction)
            currentFunction.syntax = syntax
            if line.lstrip().startswith('.. function::'): currentFunction.static=True
            elif line.lstrip().startswith('.. method::'): currentFunction.static=False
        elif line.lstrip().startswith('.. class::') or line.lstrip().startswith('.. attribute::') or line.lstrip().startswith('.. data::'):
            raise Exception, 'You probably missed something here: '+line
            
        else:
            # keep the line break ??
            if line.endswith('.') or len(line) < 60 or (line.startswith('*') or line.startswith('-') or line.startswith('+')):
                line += '\n'
            
            
            if bInModDocumentation:
                currentNamespace.docArray.append(line)
            elif bInFnDocumentation:
                currentFunction.docArray.append(line)
            
    
    #then, write out to disk
    i=0
    for section in arSections:
        fout.write('<section name="%s">'%xmlescape(section.name))
        if section.doc: fout.write('<section_doc>%s</section_doc>'%xmlescape(section.doc))
        for namespace in section.namespaces:
            
            isempty = '' if len(namespace.functions) > 0 else ' empty="true" '
            #~ if len(namespace.functions) == 0: namespace.doc+='\n(documentation not included)'
            fout.write('<namespace name="%s"%s>'%(xmlescape(namespace.name), isempty))
            if namespace.doc: fout.write('<namespace_doc>%s</namespace_doc>'%xmlescape(namespace.doc))
            
            for function in namespace.functions:
                global g_count; g_count+=1
                
                fout.write('<function name="%s" fullsyntax="%s"  '%(xmlescape(function.name),xmlescape(function.syntax)))
                print function.name
                if  function.static: fout.write(' >')
                else: fout.write('instance="true">')
                if function.doc: fout.write('<doc>%s</doc>'%xmlescape(function.doc))
                #if function.example: fout.write('<example>%s</example>'%xmlescape(function.example)) - included within doc
                fout.write('</function>')
            fout.write('</namespace>')
        
        fout.write('</section>')
        
g_count = 0
def go():
    fordering = open('..\\include_files_ordering.txt','r').read().replace('\r\n','\n').split('\n')
    
    # check that all files are included
    files = os.listdir('.')
    for file in files:
        if file.startswith('pythondoc_') and file.endswith('.txt'):
            if file not in fordering:
                raise Exception, "Warning Index in python_index.txt does not include file %s"%file
    
    #now write the output
    fout = open('..\\pythondoc.xml','w')
    writeheader(fout)
    for file in fordering:
        if file.strip() != '':
            f=open(file,'r')
            process(fout, f.read())
            f.close()
        
    writefooter(fout)
    fout.close()
    print g_count

def writeheader(fout):
    fout.write('<?xml version="1.0" encoding="UTF-8"?>')
    fout.write('<?xml-stylesheet type="text/xsl" href="viewdoc.xsl"?>')
    fout.write('<launchorzdoc library="python" version="2.5">')
def writefooter(fout):
    fout.write('</launchorzdoc>')

def splitheader(s): #takes ===Section:Text====== and returns 'Section','Text'
    s = s.strip('=')
    if ':' in s:   return s.split(':')
    else:  return s, ''

if __name__=='__main__':
    def test():
        assert unstructuretext('a :joe :: and :bob: how are: you ::') == 'a :joe :: and  how are: you ::'
        print unstructuretext('''
        This is some text
        
        .. index::
        don't show this
        single: what ever
        
        keep this though!


        and this
        '''.replace('\r\n','\n'))
        
        print unstructuretext('''
        test
        
           .. versionchanged:: 2.1 this should be gone
           
           .. versionchanged:: 2.6
           this should stay
           
           .. versionadded:: 1.5 this should be gone
           
           .. versionadded:: 2.6
           this should stay
           
              .. XXX this comment should go
              but not this I guess
        
        end
        ''')
        
        
    def main():
        go()
        
    main()


