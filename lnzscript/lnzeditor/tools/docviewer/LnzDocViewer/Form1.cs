//Ben Fisher, 2008
//Launchorz, GPL

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace LnzDocViewer
{
    public partial class Form1 : Form
    {
        public enum LanguageMode { Python, Lnz, C };
        private SciteMsg scitemsg;
        private DocumentationFromXmlBase docObject;
        private bool bSciteEditorConnection = false;
        private string docurl = "";

        private LanguageMode currentMode;
        public void setLanguage(LanguageMode mode)
        {
            switch (mode)
            {
                case LanguageMode.Python:
                    docurl = "http://docs.python.org/lib/lib.html";
                    docObject = new DocumentationFromPythonXml("pythondoc.xml");
                    this.Text = "Python";
                    break;
                case LanguageMode.Lnz:
                    docurl = "https://moltenform.com/page/lnzscript/doc/api/#version_v0_50";
                    docObject = new DocumentationFromLnzXml("lnzdoc.xml");
                    this.Text = "LnzScript";
                    break;
                case LanguageMode.C:
                    docurl = "http://www.acm.uiuc.edu/webmonkeys/book/c_guide/";
                    docObject = new DocumentationFromCXml("cdoc.xml");
                    this.Text = "C";
                    break;
                default:
                    break;
            }
            this.lblLanguage.Text = this.Text + " (switch)";
            this.treeView.Nodes.Clear();
            docObject.InitialGetSections(this.treeView.Nodes);
            currentMode = mode;
        }

        // Command-line syntax: docviewer.exe python 410243
        // Another feature could be to look up based on selected word, but that will have to wait
        public Form1()
        {
            InitializeComponent();
            this.txtOutput.MouseWheel += new MouseEventHandler(txtOutput_MouseWheel);
            // In Program.cs, ShowInTaskbar is set to false if command-line arguments are given

            LanguageMode mode = LanguageMode.Lnz;

            // callers can pass in a directory (the location of the xml files)
            string[] args = Environment.GetCommandLineArgs();
            if (args.Length > 3)
            {
                System.IO.Directory.SetCurrentDirectory(args[3]);
            }

            // get language
            if (args.Length > 1)
            {
                if (args[1].StartsWith("py")) mode = LanguageMode.Python;
                else if (args[1].StartsWith("lnz")) mode = LanguageMode.Lnz;
                else if (args[1] == ("c")) mode = LanguageMode.C;
            }
            // set up treeview
            this.setLanguage(mode);

            // Scite Communication
            long hwnd = 0;
            if (args.Length > 2)
            {
                bool bParsed = long.TryParse(args[2], out hwnd);
                if (bParsed)
                {
                    bSciteEditorConnection = true;
                    // loses the ability to switch languages, because with a connection to editor uses context of the current doc type
                    this.lblLanguage.Text = "Double-click on a function to insert it into a script.";
                }
            }
            this.scitemsg = new SciteMsg(hwnd);

            
        }

        

        
        private void treeView_AfterSelect(object sender, TreeViewEventArgs e)
        {
            // first, see if it is a namespace
            NodeDocNamespace node = e.Node as NodeDocNamespace;
            if (node != null)
            {
                this.txtOutput.Text = node.strDocumentation;
                return;
            }
            // next, see if it is a function
            NodeDocFunctionBase nodefn = e.Node as NodeDocFunctionBase;
            if (nodefn != null)
            {
                this.txtOutput.Text = nodefn.renderDocumentation();
                return;
            }

            // clear "doc not available" regardless
            if (this.txtOutput.Text == DocumentationFromXmlBase.NodocsIncluded)
                this.txtOutput.Text = "";

            
        }

        private void treeView_AfterExpand(object sender, TreeViewEventArgs e)
        {
            // if it is a namespace then populate it with children
            NodeDocNamespace node = e.Node as NodeDocNamespace;
            if (node == null || node.bHasExpanded) return;

            node.Nodes.Clear();
            string strSection = node.Parent.Text;
            string strNamespace = node.Text;
            docObject.ExpandNamespace(node);

            node.bHasExpanded = true;
        }

        private void treeView_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            NodeDocFunctionBase nodefn = treeView.SelectedNode as NodeDocFunctionBase;
            if (nodefn == null) return;
            if (!bSciteEditorConnection)
                MessageBox.Show(nodefn.renderDocumentationInsertion());
            else
                scitemsg.insertText(nodefn.renderDocumentationInsertion());
        }

        private void btnOpenWebDoc_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(docurl);
        }
        private void btnSearch_Click(object sender, EventArgs e)
        {
            // Feature not implemented yet. 
            this.txtOutput.Text = "You can search by opening the online docs, clicking (All), and using Ctrl+F.";
            this.treeView.Focus();
        }
        private void lblLanguage_Click(object sender, EventArgs e)
        {
            if (!bSciteEditorConnection)
            {
                if (currentMode == LanguageMode.C) this.setLanguage(LanguageMode.Lnz);
                else if (currentMode == LanguageMode.Lnz) this.setLanguage(LanguageMode.Python);
                else if (currentMode == LanguageMode.Python) this.setLanguage(LanguageMode.C);
            }
        }


        void txtOutput_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0) SendKeys.Send("{UP}{UP}");
            else SendKeys.Send("{DOWN}{DOWN}");
        }

        
        private void treeView_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char) Keys.Escape)
                Environment.Exit(0);
            else if (e.KeyChar == (char) Keys.Enter)
                treeView_MouseDoubleClick(null, null);
            return;
        }

        

    }
}