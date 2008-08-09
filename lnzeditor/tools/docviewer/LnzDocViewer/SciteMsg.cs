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
            else return;
        }

        public bool insertText(string s)
        {
            return doAction("insert", s);   
        }

        private string escapeString(string s)
        {
            //escape spaces with \040 octal - not obvious. Hex \x20 didn't work.
            s = s.Replace("\\", "\\\\").Replace(" ", "\\040")
                .Replace("\n", "\\n").Replace("\r", "\\r").Replace("\t", "\\t");
                
            // add literal \0 to the end (not a zero byte, but literally \0)
            s = s+"\\0";

            // escape quotes because this is being passed as a command line parameter
            s = s.Replace("\"", "\\\"");

            return s;
        }

        private bool doAction(string verb, string argument)
        {
            if (this.hwnd == 0)
                return false;
            string strHwnd = this.hwnd.ToString();

            // remember to escape string.
            string strAction = "insert:" + escapeString(argument);
            
            string strArguments = " "+strHwnd+" \""+strAction+"\"";
            Process p = new Process();
            p.StartInfo.FileName = scitemsgpath;
            p.StartInfo.Arguments = strArguments;
            p.Start();
            p.WaitForExit();
            
            p.Close();
            int ret = p.ExitCode;
            return ret == 0 ? true : false;
        }
    }
}
