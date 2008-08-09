using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows.Forms;
using System.Xml;

namespace LnzDocViewer
{
    //Section - TreeNode
    //Namespace - NodeDocNamespace
        //Instance Methods - TreeNode
        //Function - NodeDocLnzFunction

    public abstract class DocumentationFromXmlBase
    {
        protected StreamReader sr;
        protected XmlTextReader mainReader;
        protected string filename;

        public DocumentationFromXmlBase(string strFilenameIn)
		{
            if (File.Exists(strFilenameIn)) this.filename = strFilenameIn;
            else if (File.Exists("..\\" + strFilenameIn)) this.filename = "..\\" + strFilenameIn;
            else if (File.Exists("..\\..\\" + strFilenameIn)) this.filename = "..\\..\\" + strFilenameIn;
            else throw new Exception("Could not find file "+strFilenameIn);

            resetReader();
		}
        protected void resetReader()
        {
            sr = new StreamReader(this.filename);
            mainReader = new XmlTextReader(sr);

            mainReader.MoveToContent();
            if (mainReader.Name != "launchorzdoc")
                throw new Exception("Invalid document file, xml root should be launchorzdoc");
        }

        public void InitialGetSections(TreeNodeCollection root)
        {
            resetReader();
            bool bContinue = mainReader.ReadToDescendant("section");
            while (bContinue)
            {
                TreeNode currentSection = new TreeNode(mainReader.GetAttribute("name"));
                root.Add(currentSection);
                initialGetNamespaces(currentSection, mainReader.ReadSubtree());
                bContinue = ReadToNextSibling(mainReader, "section");
            }
            mainReader.Close();
        }

        public static string NodocsIncluded = "(Documentation not included. See official library reference.)";
        protected void initialGetNamespaces(TreeNode outCurrentSection, XmlReader reader)
        {
            bool bContinue = reader.ReadToDescendant("namespace");
            while (bContinue)
            {
                NodeDocNamespace currentNamespace = new NodeDocNamespace(reader.GetAttribute("name"), outCurrentSection.Text);
                bool bIsEmpty = (reader.GetAttribute("empty") != "true"); //Python might specify some to be empty
                
                currentNamespace.strDocumentation = initialGetNamespaceDoc(reader.ReadSubtree());
                outCurrentSection.Nodes.Add(currentNamespace);

                if (bIsEmpty)
                    currentNamespace.Nodes.Add(new TreeNode("")); // add dummy element, so can be expanded
                else
                    if (currentNamespace.strDocumentation == "")
                        currentNamespace.strDocumentation = NodocsIncluded;


                bContinue = ReadToNextSibling(reader, "namespace");
            }
            reader.Close();
        }
        protected string initialGetNamespaceDoc(XmlReader reader)
        {
            bool bFound = reader.ReadToDescendant("namespace_doc");
            string strRes = (bFound) ? unencodeXml(reader.ReadString()) : "";
            reader.Close();
            return strRes;
        }
        public abstract void ExpandNamespace(NodeDocNamespace node);
        protected string getFunctionDocAndExample(XmlReader reader)
        {
            //assumes doc is before example. Otherwise, could miss an example.
            string strRes = "";
            bool bFound = reader.ReadToDescendant("doc");
            if (bFound) strRes += (unencodeXml(reader.ReadString()));
            bFound = reader.ReadToNextSibling("example");
            if (bFound) strRes += ("\r\n\r\nExample:\r\n" + unencodeXml(reader.ReadString()));

            reader.Close();
            return strRes;
        }
        protected static string unencodeXml(string strInput)
        {
            return strInput.Replace("[[br]]", "\r\n");
        }
        protected static bool ReadToNextSibling(XmlReader r, string name) // workaround for possible xml reader bug. See http://support.microsoft.com/kb/906724
        {
            if (r.ReadState == ReadState.Initial)
            {
                r.Read();
                if (r.IsStartElement(name))
                    return true;
            }
            return r.ReadToNextSibling(name);
        }
        
    }



}
