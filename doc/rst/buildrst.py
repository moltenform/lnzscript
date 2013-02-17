#uses http://rst2a.com/api/
#which isn't that great, but I wanted something quickly.
#mostly using it for the themes.

#style of 'lsr'
import urllib
import os

# Get the common header
f = open('header.html','r')
g_strHtmlHeader = f.read()
f.close()

def convertRstToHtml(strFileIn, strFileOut):
	f=open(strFileIn,'r')
	alltxt = f.read()
	f.close()
	
	url = 'http://api.rst2a.com/1.0/rst2/html'
	args = {'rst':alltxt, 'style':'lsr'}
	postdata = urllib.urlencode(args)
	
	#POST it to the site and get the results
	u = urllib.urlopen(url, data=postdata)
	html = u.read()
	
	# add custom things to the html
	index = html.index('<div class="document"')
	html = html[0:index] + g_strHtmlHeader + html[index:]
	#i.e. html.insert(index, g_strHtmlHeader)
	
	f = open(strFileOut, 'w'); f.write(html); f.close()
	

def generateDocumentation():
	files = os.listdir('.')
	nFiles = 0
	for file in files:
		if file.endswith('.rst'):
			nFiles+=1
			strOutFilename = file.replace('.rst','.html')
			convertRstToHtml(file, '..\\html\\'+strOutFilename)
			print strOutFilename
			
	if nFiles==0:
		raise Exception, 'no documentation found.'
			

if __name__=='__main__':
	def test(): convertRstToHtml('test.rst','..\\html\\test.html')
	generateDocumentation()
	
		
	