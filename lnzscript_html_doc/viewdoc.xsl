<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!-- ViewDoc, created for launchorz. Ben Fisher, 2008 -->
<xsl:template match="/">
<html>
<head><title>Launchorz Reference Documentation</title>
<script language="JavaScript"><![CDATA[

function changeOutput()
{
// change the output by adding line breaks.
odivOutput = document.getElementById('divOutput');
var strOutput = odivOutput.innerHTML;
strOutput = strOutput.replace(/\[\[br\]\]/g,'<br/>');
odivOutput.innerHTML = strOutput;

//document.getElementById('txtTest').value = strOutput;
}

]]></script>
<style type="text/css"><![CDATA[
.mleft {margin-left: 20px}
.nottoowide {width: 80%}
]]></style>
</head>
<body onload="changeOutput();">
<h2>Launchorz Reference Documentation <font size="-2">Version <xsl:value-of select="/launchorzdoc/@version"/></font></h2>

	<!-- Draw the top links -->
	
<a name="anchor_top"></a>
<div id="divTopLinks" class="nottoowide">
<xsl:for-each select="launchorzdoc/section">
	<br/><xsl:value-of select="@name"/><br/>

	<table border="1"><tr>
	<xsl:for-each select="namespace">
		<td><xsl:value-of select="@name"/></td>
		
	</xsl:for-each>
	</tr></table>
</xsl:for-each>
</div>

<hr/>	
<xsl:variable name="firstNamespace" select="/launchorzdoc/section/namespace/@name" />

<div id="divOutput">
<xsl:for-each select="launchorzdoc/section">
	<xsl:for-each select="namespace">
		<!-- create the named div-->
		<div>
		<xsl:attribute name="id">div_<xsl:value-of select="../@name" />_<xsl:value-of select="@name" /></xsl:attribute> 
		
		<xsl:if test="@name != $firstNamespace"><xsl:attribute name="style">display:none</xsl:attribute></xsl:if>
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


<textarea id="txtTest"></textarea> <!--print transformed html here for debugging-->
</body>
</html>
</xsl:template>
</xsl:stylesheet>