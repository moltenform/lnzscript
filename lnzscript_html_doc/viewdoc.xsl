<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!-- ViewDoc, created for launchorz. Ben Fisher, 2008 -->
<xsl:template match="/">
<html>
<head><title>Launchorz Reference Documentation</title>
<script language="JavaScript"><![CDATA[
function $(s) {return document.getElementById(s); }

function getElementsByClass(node,searchClass,tag) {
// to be better, would use a regexp ("\b"+searchClass+"\b")
  var classElements = new Array();
  var els = node.getElementsByTagName(tag);
  var elsLen = els.length;
  for (i = 0, j = 0; i < elsLen; i++) {
    if ( els[i].className.indexOf(searchClass)!= -1 ) {
      classElements[j] = els[i];
      j++;
    }
  }
return classElements;
}
function setVisibleAll(bShow) { 
var aObjNs = getElementsByClass($('divOutput'),'classNamespace','div' );
for (var i=0; i<aObjNs.length;i++)
	aObjNs[i].style.display = bShow ? '' : 'none';
if (bShow) g_prevShown='(All)';
}

g_prevShown = null;
function showDiv(strId)
{
if (g_prevShown=='(All)') setVisibleAll(false);
else if (g_prevShown) $(g_prevShown).style.display = 'none';

oDiv = $(strId);
oDiv.style.display = ''; //show it
g_prevShown = strId;
}

function changeOutput()
{
// change the output by adding line breaks.
var odivOutput = $('divOutput');
var strOutput = odivOutput.innerHTML;
strOutput = strOutput.replace(/\[\[br\]\]/g,'<br/>');
strOutput = strOutput.replace(/AU3_INTDEFAULT/g,'(default)');
odivOutput.innerHTML = strOutput;

// Show the first one
var aObjNs = getElementsByClass($('divOutput'),'classNamespace','div' );
showDiv( aObjNs[0].id );

//$('txtTest').value = strOutput;
}

]]></script>
<style type="text/css"><![CDATA[
.mleft {margin-left: 20px}
.nottoowide {width: 80%}
body {
  font: 100% sans-serif;
  background: #ffffff;
  color: black;
  margin: 2em;
  padding: 0em 2em;
}

]]></style>
</head>
<body onload="changeOutput();">
<h2>Launchorz Reference Documentation <font size="-2">Version <xsl:value-of select="/launchorzdoc/@version"/></font></h2>

	<!-- Draw the top links -->
	
<a name="anchor_top"></a>
<div id="divTopLinks" class="nottoowide">
<xsl:for-each select="launchorzdoc/section">
	<br/><xsl:value-of select="@name"/><br/><!-- Section name-->

	<table border="1"><tr>
	<xsl:for-each select="namespace">
		<td>
		<a>
		<xsl:attribute name="href">javascript:showDiv('div_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>');</xsl:attribute>
		<xsl:value-of select="@name"/>
		</a></td><!-- Namespace name-->
		
	</xsl:for-each>
	<td><a href="javascript:setVisibleAll(true);">(All)</a></td>
	</tr></table>
</xsl:for-each>
</div>

<hr/>	
<xsl:variable name="firstNamespace" select="/launchorzdoc/section/namespace/@name" />

<div id="divOutput">
<xsl:for-each select="launchorzdoc/section">
	<xsl:for-each select="namespace">
		<!-- create the named div-->
		<div class="classNamespace" style="display:none"> <!-- it will be shown later, with JavaScript-->
		<xsl:attribute name="id">div_<xsl:value-of select="../@name" />_<xsl:value-of select="@name" /></xsl:attribute> 
		
		<b><xsl:value-of select="@name"/></b><br/>
		
		
		<xsl:for-each select="function">
			<xsl:if test="../@name != '(Global)'"><xsl:value-of select="../@name"/>.</xsl:if>
			<xsl:value-of select="@name"/>
			<blockquote>
			<i>Syntax : </i> <xsl:if test="../@name != '(Global)'"><xsl:value-of select="../@name"/>.</xsl:if><xsl:value-of select="@name"/>
			( <xsl:value-of select="@args"/> )<br/>
			<xsl:if test="@returns != ''"><i>Returns : </i> <xsl:value-of select="@returns"/><br/></xsl:if>
			<br/>
			<xsl:value-of select="doc"/>
			</blockquote>
			<br/>
			
		</xsl:for-each>
		</div>
	 </xsl:for-each>
</xsl:for-each>
</div>

<br/>
<a href="#anchor_top">Top</a>

<!--<textarea id="txtTest"></textarea> --><!--print transformed html here for debugging-->
</body>
</html>
</xsl:template>
</xsl:stylesheet>