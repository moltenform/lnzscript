using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace LnzDocViewer
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Form1 fm = new Form1();
            if (Environment.GetCommandLineArgs().Length > 1)
                fm.ShowInTaskbar = false;
            Application.Run(fm);
        }
    }
}