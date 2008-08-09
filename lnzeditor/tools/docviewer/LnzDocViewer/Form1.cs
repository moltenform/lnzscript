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
        private SciteMsg scitemsg;
        private DocumentationFromXmlBase docObject;
        private bool bStartedWithArgs = false;
        public Form1()
        {
            InitializeComponent();
            // note that ShowInTaskbar is set to false if command-line arguments are given

            // Scite Communication
            string[] args = Environment.GetCommandLineArgs();
            long hwnd = 0;
            this.lblVersion.Text = "Can't see editor.";
            if (args.Length > 1)
            {
                bStartedWithArgs = true;
                bool bParsed; 
                bParsed = long.TryParse(args[1], out hwnd);
                if (bParsed)
                    this.lblVersion.Text = "Double-click on a function to insert it into a script.";                    
            }
            this.scitemsg = new SciteMsg(hwnd);

            // set up TreeView

            docObject = new DocumentationFromLnzXml("lnzdoc.xml");
            docObject.InitialGetSections(this.treeView.Nodes);
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
            NodeDocLnzFunction nodefn = e.Node as NodeDocLnzFunction;
            if (nodefn != null)
            {
                this.txtOutput.Text = nodefn.renderDocumentation();
                return;
            }
            
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
            NodeDocLnzFunction nodefn = treeView.SelectedNode as NodeDocLnzFunction;
            if (nodefn == null) return;
            if (!bStartedWithArgs)
                MessageBox.Show(nodefn.renderDocumentationInsertion());
            else
                scitemsg.insertText(nodefn.renderDocumentationInsertion());
        }

        private void btnOpenWebDoc_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("http://students.olin.edu/2010/bfisher/lnz_script/lnz_02_documentation.xml");
        }

        private void btnSearch_Click(object sender, EventArgs e)
        {
            // Feature not implemented yet. 
            this.txtOutput.Text = "You can search by opening the online docs, clicking (All), and using Ctrl+F.";

        }



    }
}