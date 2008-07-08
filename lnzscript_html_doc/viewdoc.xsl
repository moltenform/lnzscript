<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!-- ViewDoc, created for launchorz. Ben Fisher, 2008 -->
<xsl:template match="/">
  <html>
  <head><title>Launchorz Reference Documentation</title>
  <script language="JavaScript"><![CDATA[
 // The javascript here should not be essential.
 
 function changeOutput()
 {
 // change the output by adding line breaks.
 odivOutput = document.getElementById('divOutput');
var strOutput = odivOutput.innerHTML;
strOutput = strOutput.replace(/\[\[br\]\]/g,'<br/>');
 odivOutput.innerHTML = strOutput;
document.getElementById('txtTest').value = strOutput;
 }
 
  ]]></script>
  <style type="text/css"><![CDATA[
  .mleft {margin-left: 20px}
  .nottoowide {width: 80%}
  ]]></style>
  </head>
  <body onload="changeOutput()">
	<h2>Launchorz Reference Documentation</h2>
	<font size="-2">Version <xsl:value-of select="/launchorzdoc/@version"/></font>
	<!-- Draw the top links -->
	
<a name="anchor_top"></a>
<div id="divTopLinks" class="nottoowide">
<xsl:for-each select="launchorzdoc/section">
	<br/><b><xsl:value-of select="@name"/>:</b><br/><br/>

	<xsl:for-each select="namespace">
		<br/><i><xsl:value-of select="@name"/></i><br/>
		<xsl:for-each select="function">
			<span class="mleft">
			<!--<xsl:if test="../@name != '(Global)'"><xsl:value-of select="../@name"/>.</xsl:if> -->
			<xsl:value-of select="@name"/> 
			</span>
		</xsl:for-each>
	</xsl:for-each>
</xsl:for-each>
</div>
	
<div id="divOutput">
<xsl:for-each select="launchorzdoc/section">
<hr/>
<h4><xsl:value-of select="@name"/></h4>
	<xsl:for-each select="namespace">
		<b><xsl:value-of select="@name"/></b><span style="margin-left:100px;"><a href="#anchor_top">Top</a></span><br/>
		<xsl:for-each select="function">
		
		<!-- create the anchor-->
		<a>
		<xsl:attribute name="name">anchor_<xsl:value-of select="../@name" />_<xsl:value-of select="@name" /></xsl:attribute> 
		</a>
		
		
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
	 </xsl:for-each>
</xsl:for-each>
</div>

<textarea id="txtTest"></textarea>

</body>
</html>
</xsl:template>
</xsl:stylesheet>