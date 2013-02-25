<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!-- ViewDoc, created for launchorz. Ben Fisher, 2008 -->
<xsl:template match="/">
<html><head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>LnzScript Reference</title>
<link type="text/css" rel="stylesheet" href="viewdoc.css" />
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

function shex(s) { $(s).style.display = ($(s).style.display!='none') ? 'none' : ''; }

function onFirstLoad()
{
// change the output by adding line breaks.
var odivOutput = $('divOutput');
var strOutput = odivOutput.innerHTML;
strOutput = strOutput.replace(/\[\[br\]\]/g,'<br/>');
strOutput = strOutput.replace(/string str([A-Z])/g,'s$1');
strOutput = strOutput.replace(/bool (b[A-Z])/g,'$1');
strOutput = strOutput.replace(/int (x|y|w|h|n[A-Z])/g,'$1');
odivOutput.innerHTML = strOutput;

// Show the first one
var aObjNs = getElementsByClass($('divOutput'),'classNamespace','div' );
showDiv( aObjNs[0].id );

}

]]></script>
</head>
<body onload="onFirstLoad();">

<div id="topbar" class="wide"><div class="container"></div></div>

<div tabindex="-1" style="outline: 0px none;" id="page" class="wide">
<div class="container">

<h1>LnzScript Reference</h1>
<p>This is documentation for LnzScript 0.4. See the <a href="..\lnz\index.html">latest version</a> of LnzScript.</p>
<div class="maintoplinks">
<!-- Draw the top links -->
<a name="anchor_top"></a>
<xsl:for-each select="launchorzdoc/section">
	<xsl:for-each select="namespace">
		<a>
		<xsl:attribute name="href">javascript:showDiv('div_<xsl:value-of select="../@name"/>_<xsl:value-of select="@name"/>');</xsl:attribute>
		<xsl:choose>
		<xsl:when test="@name = '(Global)'">Global</xsl:when>
		<xsl:otherwise><xsl:value-of select="@name"/></xsl:otherwise>
		</xsl:choose>
		</a> |
	</xsl:for-each>
</xsl:for-each>
<a href="javascript:setVisibleAll(true);">(All)</a>
</div>

<div style="margin:3em"></div>

<div id="divOutput" class="maindoc">
<xsl:for-each select="launchorzdoc/section">
	<xsl:for-each select="namespace">
		<!-- create the named div-->
		<div class="classNamespace" style="display:none"> <!-- it will be shown later, with JavaScript-->
		<xsl:attribute name="id">div_<xsl:value-of select="../@name" />_<xsl:value-of select="@name" /></xsl:attribute> 
		
		<xsl:for-each select="function">			
			<!-- If an instance method, a.foo(). If a global method, foo(). If a static method, Class.foo() -->
			<pre><xsl:choose>
				<xsl:when test="@instance='true'">
					<xsl:choose>
					<xsl:when test="../@name = 'Array'">arr.</xsl:when>
					<xsl:when test="../@name = 'String'">s.</xsl:when>
					<xsl:when test="../@name = 'RegExp'">re.</xsl:when>
					<xsl:when test="../@name = 'Number'">x.</xsl:when>
					<xsl:when test="../@name = 'Date'">dt.</xsl:when>
					</xsl:choose>
				</xsl:when>
				<xsl:when test="(../@name != '(Global)') and not(starts-with(@name, ' new '))"><xsl:value-of select="../@name"/>.</xsl:when>
			</xsl:choose>
			<xsl:value-of select="@name"/>(<xsl:value-of select="@args"/>)<xsl:if test="@returns != ''"><i> => </i> <xsl:value-of select="@returns"/></xsl:if></pre>
			<p>
			<xsl:value-of select="doc"/>
			<xsl:if test="example != ''">
				<span><xsl:attribute name="onclick">shex('ex_<xsl:value-of select="../@name" />_<xsl:value-of select="@name" />');</xsl:attribute> Example. </span>
				<span class="spanexample">
					<xsl:if test="not(starts-with(example,'Note:'))"><xsl:attribute name="style">display:none</xsl:attribute></xsl:if>
					<xsl:attribute name="id">ex_<xsl:value-of select="../@name" />_<xsl:value-of select="@name" /></xsl:attribute>
					<br/><br/>
				<xsl:value-of select="example"/></span> 
			</xsl:if>
			</p>
			
		</xsl:for-each>
		</div>
	 </xsl:for-each>
</xsl:for-each>
</div>

<!--
	XSL code: 
	Ben Fisher, 2008. Released under Gnu Public License v3.
	CSS styles:
	Copyright 2009 The Go Authors. All rights reserved.
	Use of this source code is governed by a BSD-style
	license that can be found in the LICENSE file.
-->
<div id="footer">
Styling from golang package documentation; <a href="http://golang.org/LICENSE">license</a>.
</div>

</div></div>

</body>
</html>
</xsl:template>
</xsl:stylesheet>