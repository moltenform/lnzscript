using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace LnzDocViewer
{
    public class NodeDocBase : TreeNode
    {
        
    }
    public class NodeDocNamespace : NodeDocBase
    {
        public string strSection;
        public string strNamespacename;
        public string strDocumentation;
        public bool bHasExpanded;
        public NodeDocNamespace(string name, string section)
        {
            this.Name = name;
            this.Text = name;
            this.strNamespacename = name;
            this.strSection = section;
            bHasExpanded = false;
        }

    }

    public class NodeDocLnzFunction : NodeDocBase
    {
        public string strSection;
        public string strNamespacename;
        public string strFunctionname;
        public string strArguments = null;
        public string strReturns = null;
        public string strDocumentationAndExample = null;
        public bool bIsInstanceMethod;

        public NodeDocLnzFunction(string section, string strnamespace, string name)
        {
            this.Name = name;
            this.Text = name;
            this.strFunctionname = name;
            this.strSection = section;
            this.strNamespacename = strnamespace;
        }

        public string renderDocumentation()
        {
            string strDoc = "Syntax: " + commonRenderDocumentation();
            strDoc += "(" + ((strArguments==null) ? " ":strArguments) + ")\r\n";
            if (strReturns != null && strReturns != "")
                strDoc += "Returns: " + strReturns + "\r\n";
            //strDoc += "\r\n";
            strDoc += strDocumentationAndExample;
            return strDoc;
        }
        
        private string commonRenderDocumentation()
        {
            string strDoc = "";
            if (strNamespacename == "(Global)")
                strDoc += "";
            else if (bIsInstanceMethod)
                strDoc += "a."; //"<" + strNamespace + " object>.";
            else
                strDoc += strNamespacename + ".";
            strDoc += strFunctionname;
            return strDoc;
        }
        public string renderDocumentationInsertion()
        {
            string strDoc = commonRenderDocumentation() + "( ";
            //filter out the optional arguments
            if (strArguments != null && strArguments != "")
            {
                string[] astrArgs = strArguments.Split(',');
                for (int i = 0; i < astrArgs.Length; i++)
                {
                    string strArg = astrArgs[i].Trim();
                    if (strArg.Contains("=") || strArg.Contains("["))
                        continue; //this is some type of optional variable.

                    if (strArg.Contains(" "))
                        strDoc += strArg.Substring(strArg.IndexOf(' '));
                    else
                        strDoc += strArg;
                    if (i != astrArgs.Length - 1) strDoc += ", ";
                }
            }
            strDoc += " )";
            return strDoc;
        }

    }
    

}
