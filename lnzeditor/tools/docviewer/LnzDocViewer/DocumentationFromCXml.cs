using System;
using System.Collections.Generic;
using System.Text;

namespace LnzDocViewer
{
    public class DocumentationFromCXml : DocumentationFromPythonXml
    {
        public DocumentationFromCXml(string strFilenameIn)
            : base(strFilenameIn)
        { }
        protected override bool emphasizeStaticness() { return false; }

        protected override NodeDocPythonFunction newnode(string strSection, string strNamespace, string strFnname)
        {
            return new NodeDocCFunction(strSection, strNamespace, strFnname);
        }
    }
}
