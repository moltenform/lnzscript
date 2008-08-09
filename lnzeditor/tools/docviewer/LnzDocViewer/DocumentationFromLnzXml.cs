using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows.Forms;
using System.Xml;


namespace LnzDocViewer
{
    public class DocumentationFromLnzXml : DocumentationFromXmlBase
    {
        public DocumentationFromLnzXml(string strFilenameIn)
            : base(strFilenameIn)
        { }

        public override void ExpandNamespace(NodeDocNamespace node)
        {
            TreeNode instanceMethods = new TreeNode("(Instance Methods)"); //things may or may not be added to this.
            resetReader();
            expandNamespace_section(node.Nodes, instanceMethods, node.strSection, node.strNamespacename, mainReader);
            if (instanceMethods.Nodes.Count != 0)
                node.Nodes.Insert(0, instanceMethods); // add instance methods, if any were made
        }
        private void expandNamespace_section(TreeNodeCollection outNodes, TreeNode outInstanceMethods, string strSection, string strNamespace, XmlReader reader)
        {
            bool bContinue = reader.ReadToDescendant("section");
            while (bContinue)
            {
                if (mainReader.GetAttribute("name") == strSection)
                {
                    expandNamespace_namespace(outNodes, outInstanceMethods, strSection, strNamespace, reader.ReadSubtree());
                    mainReader.Close();
                    return;
                }
                bContinue = ReadToNextSibling(mainReader, "section");
            }
            mainReader.Close();
        }
        private void expandNamespace_namespace(TreeNodeCollection outNodes, TreeNode outInstanceMethods, string strSection, string strNamespace, XmlReader reader)
        {
            bool bContinue = reader.ReadToDescendant("namespace");
            while (bContinue)
            {
                if (reader.GetAttribute("name") == strNamespace)
                {
                    expandNamespace_function(outNodes, outInstanceMethods, strSection, strNamespace, reader.ReadSubtree());
                    reader.Close();
                    return;
                }
                bContinue = ReadToNextSibling(reader, "namespace");
            }
            reader.Close();
        }
        private void expandNamespace_function(TreeNodeCollection outNodes, TreeNode outInstanceMethods, string strSection, string strNamespace, XmlReader reader)
        {
            bool bContinue = reader.ReadToDescendant("function");
            while (bContinue)
            {
                
               // if (reader.GetAttribute("args") != null) MessageBox.Show("instance?");

                NodeDocLnzFunction node = new NodeDocLnzFunction(strSection, strNamespace, reader.GetAttribute("name"));

                bool bInstance = reader.GetAttribute("instance") == "true";
                node.bIsInstanceMethod = bInstance;
                string strArgs = reader.GetAttribute("args"); if (strArgs != null && strArgs != "") node.strArguments = strArgs;
                string strReturns = reader.GetAttribute("returns"); if (strReturns != null && strReturns != "") node.strReturns = strReturns;
                node.strDocumentationAndExample = getFunctionDocAndExample(reader.ReadSubtree()); //assumes doc before example

                if (bInstance)
                {
                    //MessageBox.Show("instance found");
                    outInstanceMethods.Nodes.Add(node);
                }
                else
                    outNodes.Add(node);

                bContinue = ReadToNextSibling(reader, "function");
            }
            reader.Close();
        }
    }
}
