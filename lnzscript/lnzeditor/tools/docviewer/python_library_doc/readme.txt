The Python 2.6 documentation is stored in .rst, reStructuredText format.

I went through the library documentation quickly and copied some of the .rst into new files, filtering out some that were 2.6-specific, os-specific, obsolete, or uninteresting to me. I added ===Section:this=== divisions.

The most valuable part of this is the re-organization of the library into sections. In my opinion this is a better organization than given in the official docs.

Because the current amount of information seems to be "good enough" (and people who want more Python information can just look at the actual docs) I'm not planning on furthering this or adding more. 

So, don't expect this to be great, documented, or complete.








A planned better layout for Python docs:
============
(Names made-up for illustration)
+ Built-in
+ Math
- String
	toLower
	toUpper
	split
	join
	string.fromAscii
	string.static		(note static methods sorted below, this could be done ahead of time when generating xml)
- Os
	os.stat
	os.copy
- Web
	- Parsing			(note modules can expose their own classes whicch have children)
		- HTMLClass
			instanceMethod
			HTMLClass.staticmethod
		+ ParserClass
		+ XMLClass
	
, but, this would take some work to do and the existing design is not great but good enough