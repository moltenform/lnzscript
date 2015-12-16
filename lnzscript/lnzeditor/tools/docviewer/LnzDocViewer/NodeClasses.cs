//Ben Fisher, 2008
//Launchorz, GPL

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace LnzDocViewer
{
    // TreeNode classes. They store documentation information associated with a node.

    public abstract class NodeDocBase : TreeNode
    { }

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
    public abstract class NodeDocFunctionBase : NodeDocBase
    {
        public string strSection;
        public string strNamespacename;
        public string strFunctionname;
        public bool bIsInstanceMethod;

        public NodeDocFunctionBase(string section, string strnamespace, string name)
        {
            this.Name = name;
            this.Text = name;
            this.strFunctionname = name;
            this.strSection = section;
            this.strNamespacename = strnamespace;
        }
        protected virtual string commonRenderDocumentation()
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
        public abstract string renderDocumentation();
        public abstract string renderDocumentationInsertion();

    }

    public class NodeDocLnzFunction : NodeDocFunctionBase
    {
        public string strArguments = null;
        public string strReturns = null;
        public string strDocumentationAndExample = null;

        public NodeDocLnzFunction(string section, string strnamespace, string name)
            : base(section, strnamespace, name) { }

        public override string renderDocumentation()
        {
            string strDoc = "Syntax: " + commonRenderDocumentation();
            strDoc += "(" + ((strArguments==null) ? " ":strArguments) + ")\r\n";
            if (strReturns != null && strReturns != "")
                strDoc += "Returns: " + strReturns + "\r\n";
            //strDoc += "\r\n";
            if (strDocumentationAndExample != null)
                strDoc += strDocumentationAndExample;
            return strDoc;
        }


        public override string renderDocumentationInsertion()
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

    public class NodeDocPythonFunction : NodeDocFunctionBase
    {
        public string strFullSyntax = null;
        public string strDocumentation = null;

        public NodeDocPythonFunction(string section, string strnamespace, string name)
            : base(section, strnamespace, name) { }

        public override string renderDocumentation()
        {
            string strDoc = "Syntax: " + commonRenderDocumentation();
            if (strFullSyntax == null || strFullSyntax == "")
                strDoc += "( )";
            else
            {
                //problem: duplication of names because name=dostuff and syntax=dostuff(a1, a2)
                // this workaround seems to solve it
                if (strFullSyntax.StartsWith(strFunctionname))
                    strDoc += strFullSyntax.Substring(strFunctionname.Length);
                else
                    strDoc += strFullSyntax;
            }
            // return information isn't explicitly given.

            if (strDocumentation != null && strDocumentation != "")
                strDoc += "\r\n\r\n" + strDocumentation;
            return strDoc;
        }
        public override string renderDocumentationInsertion()
        {
            // don't try to remove optional arguments and so on.
            // just insert the function name only
            return commonRenderDocumentation() + "( "; // "os.rename( "
        }

    }

    public class NodeDocCFunction : NodeDocPythonFunction
    {

        public NodeDocCFunction(string section, string strnamespace, string name)
            : base(section, strnamespace, name) { }

        public override string renderDocumentation()
        {
            // the strFullSyntax will include the fn. name
            string strDoc = "Syntax: " + ((strFullSyntax == null) ? "" : strFullSyntax);
            if (strDocumentation != null && strDocumentation != "")
                strDoc += "\r\n\r\n" + strDocumentation;
            return strDoc;
        }
        public override string renderDocumentationInsertion()
        {
            // don't try to remove argument types and so on.
            // insert the function name only
            return strFunctionname + "( ";
        }

    }

}
