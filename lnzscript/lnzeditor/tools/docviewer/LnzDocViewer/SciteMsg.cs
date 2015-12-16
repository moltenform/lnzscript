using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.IO;

namespace LnzDocViewer
{
    public class SciteMsg
    {
        long hwnd = 0;
        string scitemsgpath;
        public SciteMsg(long hwnd)
        {
            this.hwnd = hwnd;

            if (File.Exists("scite_msg.exe")) scitemsgpath = "scite_msg.exe";
            else if (File.Exists("..\\scite_msg.exe")) scitemsgpath = "..\\scite_msg.exe";
            else { this.hwnd = 0; return; }
        }

        public bool insertText(string s)
        {
            return doAction("insert", s);   
        }

        private static string escapeString(string s)
        {
            s = s.Replace("\n", "\\n").Replace("\r", "\\r").Replace("\\", "\\\\").Replace("\t","\\t");
            //other special chars should be replaced too, in theory, but I'm not really worried about that.

            // escape quotes because this is being passed as a command line parameter
            s = s.Replace("\"", "\\\"");

            return s;
        }

        private bool doAction(string verb, string argument)
        {
            if (this.hwnd == 0)
                return false;

            // remember to escape characters in string.
            string strHwnd = this.hwnd.ToString();
            string strAction = verb + ":" + escapeString(argument);

            // Scite_msg.exe 430245 "insert:hello scite"
            string strArguments = " "+strHwnd+" \""+strAction+"\"";

            ProcessStartInfo psinfo = new ProcessStartInfo(scitemsgpath, strArguments);
            psinfo.WindowStyle = ProcessWindowStyle.Hidden; // hide the flashing black box
            Process p = System.Diagnostics.Process.Start(psinfo);
            p.WaitForExit();

            return p.ExitCode == 0 ? true : false;
        }
    }
}
