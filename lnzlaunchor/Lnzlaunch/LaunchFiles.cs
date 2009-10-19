using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Diagnostics;
using System.Windows.Forms;
using System.ComponentModel;

namespace Lnzlaunch
{
    public class LaunchFiles
    {
        public static void editFileWithNotepad(string filePath)
        {

        }

        public static void showFileInExplorer(string filePath)
        {
            if (!File.Exists(filePath))
                throw new FileNotFoundException("File not found", filePath);
            ProcessStartInfo processStartInfo = new ProcessStartInfo();
            processStartInfo.FileName = "explorer";
            processStartInfo.UseShellExecute = true;
            processStartInfo.WindowStyle = ProcessWindowStyle.Normal;
            //processStartInfo.Arguments = string.Format("/e,/select,\"{0}\"", filePath);
            processStartInfo.Arguments = string.Format("/select,\"{0}\"", filePath);
            Process.Start(processStartInfo);
        }

        public static bool openCommandContainingFolder(LnzLaunchCommand cmd)
        {
            //shouldn't throw an exception, just return false upon error
            string sTarget = getBaseFileFromCommand(cmd);
            if (sTarget==null) return false;
            showFileInExplorer(sTarget);
            return true;
        }

        //returns null if file doesn't exist
        public static string getBaseFileFromCommand(LnzLaunchCommand cmd)
        {
            //use heuristics to see if we can find containing the file of the command
            //we won't be able to replace %clip% or %1%
            string sTarget = cmd.sCmdTarget;
            sTarget = sTarget.Split('\t')[0];
            if (!File.Exists(sTarget)) return null;
            return sTarget;
        }

        //TODO: catch exceptions. try giving this really bad data/nonexistent files, see where breaks
        public static string runCommand(string textInBox, LnzLaunchCommand cmd)
        {
            //be sure to escape " with \" . don't need to escape \ with \\.

            string sTarget = cmd.sCmdTarget;
            Debug.Assert(!textInBox.Contains("\t")); //that'd mess things up since we split on tab.
            if (sTarget.Contains("%clip%"))
            {
                string strClip = "";
                IDataObject data = Clipboard.GetDataObject();
                if (data!=null && data.GetDataPresent(DataFormats.Text))
                    strClip = (string)data.GetData(DataFormats.Text, true);
                sTarget = sTarget.Replace("%clip%", strClip);
            }
            if (sTarget.Contains("%1%"))
            {
                string strArgs = ""; //arguments passed to command
                if (textInBox.StartsWith(cmd.sCmdShortcut)) //must be an actual match to pass args, otherwise "" is passed
                {
                    if (cmd.sCmdShortcut == textInBox)
                        strArgs = "";
                    else
                        strArgs = textInBox.Substring(cmd.sCmdShortcut.Length).Trim();
                    sTarget = sTarget.Replace("%1%", strArgs);
                }
                else
                    sTarget = sTarget.Replace("%1%", ""); 
            }
            // the %.% has already been replaced. And, all of the custom constants have been replaced
            Debug.Assert(!sTarget.Contains("%")); //should have done all templates now

            

            ProcessStartInfo psi;
            string[] commandargs = sTarget.Split('\t');
            if (commandargs.Length == 1)
            {
                psi = new ProcessStartInfo(commandargs[0]);
            }
            else
            {
                string commandExe = commandargs[0];
                StringBuilder sb = new StringBuilder();
                for (int i = 1; i < commandargs.Length; i++) 
                    sb.Append("\"" + commandargs[i].Replace("\"", "\"\"") + "\" ");
                string sArgString = sb.ToString();
                sArgString = sArgString.Substring(0, sArgString.Length - 1); //get rid of trailing space if it's there

                psi = new ProcessStartInfo(commandExe, sArgString);
            }

            if (cmd.bRemainOpenAfterRunning)
            {
                psi.WindowStyle = ProcessWindowStyle.Minimized;
                psi.RedirectStandardOutput = true;
                psi.UseShellExecute = false; // necessary for stream redirect
                psi.CreateNoWindow = true;
            }
            else
            {
                psi.UseShellExecute = true; // ?? so that directories can be opened
            }

            
            Process process;
            try
            {
                process = System.Diagnostics.Process.Start(psi);
            }
            catch (Exception e) //(Win32Exception e)
            {
                throw new LnzLaunchDataException("Error: " + e.Message);
            }

            
            if (cmd.bRemainOpenAfterRunning)
            {
                StreamReader myOutput = process.StandardOutput;
                process.WaitForExit(9000); //TODO: let user set this number
                if (!process.HasExited)
                    throw new LnzLaunchDataException("Process timed out.");

                return myOutput.ReadToEnd().Trim(); //sometimes output has a leading newline
            }
            else
                return null;

        }
    }
}
