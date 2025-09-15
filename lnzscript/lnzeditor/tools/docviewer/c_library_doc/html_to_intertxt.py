import re

# Reference: http://www.acm.uiuc.edu/webmonkeys/book/c_guide/

# html into intermediate

headername = 'time.h'

rename = re.compile(r'<a name="([^"]+)"></a>')
retag = re.compile(r'<.*?>')


def striptags(s):
    return retag.sub('', s)


def main():
    alltext = data.replace('\r\n', '\n').split('\n')

    lastName = None
    lastProto = None
    lastDoc = None
    lastProto = lastDoc = ''
    currentMode = 'Proto'

    for line in alltext:
        if line.startswith('<h2>'):
            continue
        m = rename.match(line)
        if m:
            strName = str(m.group(1))
            # print ('Found',strName)

            if lastName != None:
                process(lastName, lastProto, lastDoc)

            lastName = strName
            lastProto = lastDoc = ''
            currentMode = 'Proto'
            continue

        if line.strip() == 'Declaration:':
            # well, it's probably in the proto mode already, but whatver
            currentMode = 'Proto'
        elif line.strip() == 'Range:':
            currentMode = 'No-op' #we don't care about the range, don't include it
        elif currentMode == 'Proto' and line.strip() == '<p>':
            currentMode = 'Doc'
        elif currentMode == 'Proto' and line.strip() == '</b></code></blockquote>':
            currentMode = 'Doc'
        else:
            if currentMode == 'Proto':
                lastProto += line + '\n'
            elif currentMode == 'Doc':
                lastDoc += line + '\n'
            else:
                continue #evidently not in a mode

    process(lastName, lastProto, lastDoc)


def process(lastName, lastProto, lastDoc):
    #strip the "<blockquote>" and all other tags
    lastProto = striptags(lastProto).strip()
    lastDoc = striptags(lastDoc).strip()
    lastDoc = lastDoc.replace('\n     ', '\n')
    print('---' + lastName)
    print(lastProto)
    print('---!header')
    print(headername)
    print('---!doc')
    print(lastDoc)
    print('---!end')
    print()


# ([^ ]+) (.*)
# ---:\1\r\nint \1(int character); \r\n---!doc\r\n\2\r\n---!end\r\n

data = '''

<a name="asctime"></a>
<h2> 2.15.2    asctime</h2>
<p>

Declaration:
<blockquote><code><b>
     char *asctime(const struct tm *</b></code><i>timeptr</i><code><b>);
</b></code></blockquote>
     Returns a pointer to a string which represents the day and time of the structure <i>timeptr</i>. 
The string is in the following format:
<blockquote><code><b>
DDD MMM dd hh:mm:ss YYYY
</b></code></blockquote>
<table border=0>
<tr><td><code><b>DDD</b></code></td><td>  Day of the week (Sun, Mon, Tue, Wed, Thu, Fri, Sat)</td></tr>
<tr><td><code><b>MMM</b></code></td><td>  Month of the year (Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec)</td></tr>
<tr><td><code><b>dd</b></code></td><td>   Day of the month (1,...,31)</td></tr>
<tr><td><code><b>hh</b></code></td><td>   Hour (0,...,23)</td></tr>
<tr><td><code><b>mm </b></code></td><td>  Minute (0,...,59)</td></tr>
<tr><td><code><b>ss</b></code></td><td>   Second (0,...,59)</td></tr>
<tr><td><code><b>YYYY</b></code></td><td> Year</td></tr>
</table>
     The string is terminated with a newline character and a null character.  The string is
always 26 characters long (including the terminating newline and null characters).
<p>
     A pointer to the string is returned.
<p>

Example:

  time_t timer;
  timer=time(NULL);
  printf("The current time is %s.\n",asctime(localtime(&timer)));

<a name="clock"></a>
<h2>2.15.3    clock</h2>
<p>

Declaration:
<blockquote><code><b>
     clock_t clock(void);
</b></code></blockquote>

     Returns the processor clock time used since the beginning of an implementation-defined
era (normally the beginning of the program).  The returned value divided by
<code><b>CLOCKS_PER_SEC</b></code> results in the number of seconds.  If the value is unavailable, then -1 is
returned.
<p>

</pre></b></code></blockquote>
<a name="ctime"></a>
<h2>2.15.4    ctime</h2>
<p>

Declaration:
<blockquote><code><b>
     char *ctime(const time_t *</b></code><i>timer</i><code><b>);
</b></code></blockquote>

     Returns a string representing the localtime based on the argument <i>timer</i>.  This is
equivalent to:
<blockquote><code><b>
     asctime(locatime(timer));
</b></code></blockquote>
     The returned string is in the following format:
<blockquote><code><b>
DDD MMM dd hh:mm:ss YYYY
</b></code></blockquote>
<table border=0>
<tr><td><code><b>DDD</b></code></td><td>  Day of the week (Sun, Mon, Tue, Wed, Thu, Fri, Sat)</td></tr>
<tr><td><code><b>MMM</b></code></td><td>  Month of the year (Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec)</td></tr>
<tr><td><code><b>dd</b></code></td><td>   Day of the month (1,...,31)</td></tr>
<tr><td><code><b>hh</b></code></td><td>   Hour (0,...,23)</td></tr>
<tr><td><code><b>mm</b></code></td><td>   Minute (0,...,59)</td></tr>
<tr><td><code><b>ss</b></code></td><td>   Second (0,...,59)</td></tr>
<tr><td><code><b>YYYY</b></code></td><td> Year</td></tr>
</table>
     The string is terminated with a newline character and a null character.  The string is
always 26 characters long (including the terminating newline and null characters).
<p>
     A pointer to the string is returned.

<a name="difftime"></a>
<h2>2.15.5    difftime</h2>
<p>

Declaration:
<blockquote><code><b>
     double difftime(time_t </b></code><i>time1</i><code><b>, time_t </b></code><i>time2</i><code><b>);
</b></code></blockquote>

     Calculates the difference of seconds between <i>time1</i> and <i>time2</i> (time1-time2).
<p>
     Returns the number of seconds.

<a name="gmtime"></a>
<h2>2.15.6    gmtime</h2>
<p>

Declaration:
<blockquote><code><b>
     struct tm *gmtime(const time_t *</b></code><i>timer);
</b></code></blockquote>

     The value of timer is broken up into the structure <code><b>tm</b></code> and expressed in Coordinated
Universal Time (UTC) also known as Greenwich Mean Time (GMT).
<p>
     A pointer to the structure is returned.  A null pointer is returned if UTC is not available.

<a name="localtime"></a>
<h2>2.15.7    localtime</h2>
<p>

Declaration:
<blockquote><code><b>
     struct tm *localtime(const time_t *</b></code><i>timer</i><code><b>);
</b></code></blockquote>

     The value of timer is broken up into the structure <code><b>tm</b></code> and expressed in the local time
zone.
<p>
     A pointer to the structure is returned.
<p>

</pre></b></code></blockquote>
<a name="mktime"></a>
<h2>2.15.8    mktime</h2>
<p>

Declaration:
<blockquote><code><b>
     time_t mktime(struct tm *</b></code><i>timeptr</i><code><b>);
</b></code></blockquote>

     Converts the structure pointed to by <i>timeptr</i> into a <code><b>time_t</b></code> value according to the local
time zone.  The values in the structure are not limited to their constraints.  If they exceed their
bounds, then they are adjusted accordingly so that they fit within their bounds.  The original
values of <code><b>tm_wday</b></code> (day of the week) and <code><b>tm_yday</b></code> (day of the year) are ignored, but are set
correctly after the other values have been constrained.  <code><b>tm_mday</b></code> (day of the month) is not
corrected until after <code><b>tm_mon</b></code> and <code><b>tm_year</b></code> are corrected.
<p>
     After adjustment the structure still represents the same time.
<p>
     The encoded <code><b>time_t</b></code> value is returned.  If the calendar time cannot be represented, then -1
is returned.
<p>


</pre></b></code></blockquote>
<a name="strftime"></a>
<h2>2.15.9    strftime</h2>
<p>

Declaration:
<blockquote><code><b>
     size_t strftime(char *</b></code><i>str</i><code><b>, size_t </b></code><i>maxsize</i><code><b>, const char *</b></code><i>format</i><code><b>, const struct tm *</b></code><i>timeptr</i><code><b>);
</b></code></blockquote>

     Formats the time represented in the structure <i>timeptr</i> according to the formatting rules
defined in <i>format</i> and stored into <i>str</i>.  No more than <i>maxsize</i> characters are stored into <i>str</i>
(including the terminating null character).
<p>
     All characters in the <i>format</i> string are copied to the <i>str</i> string, including the terminating
null character, except for conversion characters.  A conversion character begins with the <code><b>%</b></code> sign
and is followed by another character which defines a special value that it is to be replaced by.
<table border=0>
<tr><td><b>Conversion<br>Character</b></td><td><b>     What it is replaced by</b></td></tr>
<tr><td><code><b>%a</b></code></td><td>             abbreviated weekday name</td></tr>
<tr><td><code><b>%A</b></code></td><td>             full weekday name</td></tr>
<tr><td><code><b>%b</b></code></td><td>             abbreviated month name</td></tr>
<tr><td><code><b>%B</b></code></td><td>             full month name</td></tr>
<tr><td><code><b>%c</b></code></td><td>             appropriate date and time representation</td></tr>
<tr><td><code><b>%d</b></code></td><td>             day of the month (01-31)</td></tr>
<tr><td><code><b>%H</b></code></td><td>             hour of the day (00-23)</td></tr>
<tr><td><code><b>%I</b></code></td><td>             hour of the day (01-12)</td></tr>
<tr><td><code><b>%j</b></code></td><td>             day of the year (001-366)</td></tr>
<tr><td><code><b>%m</b></code></td><td>             month of the year (01-12)</td></tr>
<tr><td><code><b>%M</b></code></td><td>             minute of the hour (00-59)</td></tr>
<tr><td><code><b>%p</b></code></td><td>             AM/PM designator</td></tr>
<tr><td><code><b>%S</b></code></td><td>             second of the minute (00-61)</td></tr>
<tr><td><code><b>%U</b></code></td><td>             week number of the year where Sunday is the first day of week 1 (00-53)</td></tr>
<tr><td><code><b>%w</b></code></td><td>             weekday where Sunday is day 0 (0-6)</td></tr>
<tr><td><code><b>%W</b></code></td><td>             week number of the year where Monday is the first day of week 1 (00-53)</td></tr>
<tr><td><code><b>%x</b></code></td><td>             appropriate date representation</td></tr>
<tr><td><code><b>%X</b></code></td><td>             appropriate time representation</td></tr>
<tr><td><code><b>%y</b></code></td><td>             year without century (00-99)</td></tr>
<tr><td><code><b>%Y</b></code></td><td>             year with century</td></tr>
<tr><td><code><b>%Z</b></code></td><td>             time zone (possibly abbreviated) or no characters if time zone isunavailable</td></tr>
<tr><td><code><b>%%</b></code></td><td>             %</td></tr>
</table>
     Returns the number of characters stored into str not including the terminating null
character.  On error zero is returned.

<a name="time"></a>
<h2>2.15.10   time</h2>
<p>

Declaration:
<blockquote><code><b>
     time_t time(time_t *</b></code><i>timer</i><code><b>);
</b></code></blockquote>

     Calculates the current calender time and encodes it into <code><b>time_t</b></code> format.
<p>
     The <code><b>time_t</b></code> value is returned.  If <i>timer</i> is not a null pointer, then the value is also stored
into the object it points to.  If the time is unavailable, then -1 is returned.





'''

#~ print striptags('ello<b>dfgdf</b>that is')
main()
