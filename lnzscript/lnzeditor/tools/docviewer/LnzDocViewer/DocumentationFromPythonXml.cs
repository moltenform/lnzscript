//Ben Fisher, 2008
//Launchorz, GPL

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows.Forms;
using System.Xml;


namespace LnzDocViewer
{
    public class DocumentationFromPythonXml : DocumentationFromXmlBase
    {
        public DocumentationFromPythonXml(string strFilenameIn)
            : base(strFilenameIn)
        { }

        protected virtual bool emphasizeStaticness() {return true;}

        public override void ExpandNamespace(NodeDocNamespace node)
        {
            resetReader();
            expandNamespace_section(node.Nodes, node.strSection, node.strNamespacename, mainReader);
        }
        private void expandNamespace_section(TreeNodeCollection outNodes, string strSection, string strNamespace, XmlReader reader)
        {
            bool bContinue = reader.ReadToDescendant("section");
            while (bContinue)
            {
                if (mainReader.GetAttribute("name") == strSection)
                {
                    expandNamespace_namespace(outNodes, strSection, strNamespace, reader.ReadSubtree());
                    mainReader.Close();
                    return;
                }
                bContinue = ReadToNextSibling(mainReader, "section");
            }
            mainReader.Close();
        }
        private void expandNamespace_namespace(TreeNodeCollection outNodes,  string strSection, string strNamespace, XmlReader reader)
        {
            bool bContinue = reader.ReadToDescendant("namespace");
            while (bContinue)
            {
                if (reader.GetAttribute("name") == strNamespace)
                {
                    expandNamespace_function(outNodes, strSection, strNamespace, reader.ReadSubtree());
                    reader.Close();
                    return;
                }
                bContinue = ReadToNextSibling(reader, "namespace");
            }
            reader.Close();
        }

        //this exists only so that subclass can override it 
        protected virtual NodeDocPythonFunction newnode(string strSection, string strNamespace, string strFnname)
        {
            return new NodeDocPythonFunction(strSection, strNamespace, strFnname);
        }
        private void expandNamespace_function(TreeNodeCollection outNodes, string strSection, string strNamespace, XmlReader reader)
        {
            bool bContinue = reader.ReadToDescendant("function");
            while (bContinue)
            {
                NodeDocPythonFunction node = newnode(strSection, strNamespace, reader.GetAttribute("name"));
                outNodes.Add(node);

                bool bInstance = reader.GetAttribute("instance") == "true";
                node.bIsInstanceMethod = bInstance;
                string strSyntax = reader.GetAttribute("fullsyntax"); if (strSyntax != null && strSyntax != "") node.strFullSyntax = strSyntax;
                node.strDocumentation = getFunctionDocAndExample(reader.ReadSubtree()); //assumes doc before example

                if (this.emphasizeStaticness())
                {
                    if (!bInstance)
                    {
                        //change visible node text to emphasize static-ness
                        node.Text = node.strNamespacename + "." + node.strFunctionname;
                    }
                }
                bContinue = ReadToNextSibling(reader, "function");
            }
            
            reader.Close();
        }


    }
}
