using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Lnzlaunch
{
    static class Program
    {

        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            FormLnzLaunch fm = new FormLnzLaunch();
            bool bSuccess = fm.registerHotKey();
            if (bSuccess)
                Application.Run(fm);

        }     

    }
}