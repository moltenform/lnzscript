<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!-- ViewDoc, created for launchy. Ben Fisher, 2008 -->
<xsl:template match="/">
  <html>
  <body>
    <h2>Launchorz Documentation</h2>
    
    <xsl:for-each select="launchorzdoc/section">
    <hr/>
    <h4><xsl:value-of select="@name"/></h4>
	    <xsl:for-each select="namespace">
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
			<br/><br/>
		    </xsl:for-each>
	     </xsl:for-each>
    </xsl:for-each>
    
    
  </body>
  </html>
</xsl:template>
</xsl:stylesheet>