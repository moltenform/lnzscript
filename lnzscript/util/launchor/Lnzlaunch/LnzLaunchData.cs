using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows.Forms;
using System.Diagnostics;
using System.ComponentModel;

namespace Lnzlaunch
{
    public class /*struct*/ LnzLaunchCommand : IComparable
    {
        public string sCmdShortcut;
        public string sCmdTarget; // tab-delimited command. tabs for arguments.
        public string sCustomIcon;
        public bool bRemainOpenAfterRunning;

        public LnzLaunchCommand(string stCmdShortcut, string stCmdTarget, bool bbRemainOpenAfterRunning)
        {
            sCmdShortcut = stCmdShortcut; 
            sCmdTarget = stCmdTarget;
            sCustomIcon = null;
            bRemainOpenAfterRunning = bbRemainOpenAfterRunning;
        }

        public int CompareTo(object obj)
        {
            if (!(obj is LnzLaunchCommand))
                throw new ArgumentException("Argument 'obj' is not of correct type.");
            return String.Compare(this.sCmdShortcut, ((LnzLaunchCommand) obj).sCmdShortcut);
        }
        public override string ToString()
        {
            return "short=" + sCmdShortcut + "|target=" + sCmdTarget + "|stay=" + this.bRemainOpenAfterRunning.ToString() + "|icon=" + sCustomIcon;
        }
    }

    class LnzLaunchDataException : Exception
    {
        public LnzLaunchDataException(string str) : base(str) { }
    }

    public class LnzLaunchData
    {
        public Dictionary<string, string> m_dictConstants;
        public LnzLaunchCommand[] m_arrCommands;

        //TODO: allow standard variables like %sysdrive%
        /*
         builtin variables: %1% %.% %clip% %eq% for = sign
         */
        public LnzLaunchData()
        {
        }

        //NOTE: will throw LnzLaunchDataException upon error.
        public void loadData(List<KeyValuePair<string, string>> constants, List<KeyValuePair<string, string>> commands, List<KeyValuePair<string, string>> icons)
        {
            //load constants
            m_dictConstants = new Dictionary<string, string>();
            /*dictConstants["%clip%"] = null;
            dictConstants["%1%"] = null;
            dictConstants["%.%"] = Path.GetDirectoryName(Application.ExecutablePath);*/
            foreach (KeyValuePair<string, string> pair in constants)
            {
                string constantName = pair.Key;
                string constantValue = pair.Value;
                if (constantName=="" || !(constantName.StartsWith("%")&&constantName.EndsWith("%")))
                    throw new LnzLaunchDataException("Error: constants must be in form %a%. Percentage symbol was missing: '"+constantName+"' .");
                if (m_dictConstants.ContainsKey(constantName))
                    throw new LnzLaunchDataException("Error: constant named '"+constantName+"' already defined.");
                constantValue = doSubstitutions(constantValue, m_dictConstants); //perform substitutions on the value. so can have constants in constants.
                m_dictConstants[constantName] = constantValue;
            }

            //load commands
            if (commands == null || commands.Count == 0)
                throw new LnzLaunchDataException("Error: no commands defined in the configuration file. It's not useful if there aren't any shortcuts.");
            this.m_arrCommands = null; //stops anything trying to use m_arrCommands before it's been formed
            List<LnzLaunchCommand> listCommands = new List<LnzLaunchCommand>();
            bool bRemainOpen;
            foreach (KeyValuePair<string, string> pair in commands)
            {
                bRemainOpen = false;
                string commandName = pair.Key;
                string commandValue = pair.Value;
                commandName = commandName.Replace("%eq%", "="); 
                commandValue = commandValue.Replace("%eq%", "=");
                if (commandName.EndsWith("*")) {bRemainOpen=true; commandName = commandName.Substring(0, commandName.Length-1);}
                if (commandName == "" || commandValue == "") throw new LnzLaunchDataException("Error: command name or target cannot be an empty string.");

                commandValue = doSubstitutions(commandValue, m_dictConstants);
                commandValue = commandValue.Replace("%.%", Path.GetDirectoryName(Application.ExecutablePath));
                //see if any undefined constants
                string tmp = commandValue; tmp=tmp.Replace("%clip%", "").Replace("%1%","").Replace("%.%","");
                if (tmp.Contains("%"))
                    throw new LnzLaunchDataException("Error: unknown constant in the line '"+commandValue+"'.");

                //replace multiple tabs (note takes place after substitution)
                commandValue = commandValue.Replace("\t\t", "\t").Replace("\t\t", "\t").Replace("\t\t", "\t").Replace("\t\t", "\t");

                //is it already in our list of commands?
                for (int i = 0; i < listCommands.Count; i++)
                {
                    if (listCommands[i].sCmdShortcut == commandName)
                        throw new LnzLaunchDataException("Error: cannot define two commands with the same name. there are two named '" + commandName + "'.");
                }
                LnzLaunchCommand cmd = new LnzLaunchCommand(commandName, commandValue, bRemainOpen);
                listCommands.Add(cmd);

            }
            listCommands.Sort();
            this.m_arrCommands = listCommands.ToArray();
            listCommands = null; //catch anything trying to use this

            //load icons
            if (icons != null)
            {
                foreach (KeyValuePair<string, string> pair in icons)
                {
                    string commandName = pair.Key;
                    string iconValue = pair.Value;
                    if (iconValue == "") throw new LnzLaunchDataException("Error: custom icon, cannot have empty string for cmd '" + commandName + "'.");

                    commandName = commandName.Replace("%eq%", "=");
                    if (commandName.EndsWith("*")) { commandName = commandName.Substring(0, commandName.Length - 1); }

                    iconValue = doSubstitutions(iconValue, m_dictConstants);
                    iconValue = iconValue.Replace("%.%", Path.GetDirectoryName(Application.ExecutablePath));
                    if (iconValue.Contains("%"))
                        throw new LnzLaunchDataException("Error: unknown constant in the icon value  '" + iconValue + "' ('clip' or args not valid here).");
                    int index = lookupExactCommandIndex(commandName);
                    if (index == -1)
                        throw new LnzLaunchDataException("Error: trying to set an icon for command '" + commandName + "' but that command isn't defined.");
                    this.m_arrCommands[index].sCustomIcon = iconValue;
                }
            }
        }

        public int lookupExactCommandIndex(string s)
        {
            //currently a linear search. too slow??? could switch to binary search easily
            for (int i = 0; i < m_arrCommands.Length; i++)
            {
                if (m_arrCommands[i].sCmdShortcut == s)
                    return i;
            }
            return -1;
        }

        public int lookupApproximateCommandIndex(string s) { return lookupApproximateCommandIndex(s, 0); }
        public int lookupApproximateCommandIndex(string s, int hintIndex /*=0*/)
        {
            //LnzLaunchCommand dummy = new LnzLaunchCommand(s, null, false);
            //int index = Array.BinarySearch<LnzLaunchCommand>(this.listCommands.ToArray(), dummy);
            //(a linear search might be more efficient. Also, .ToArray() is expensive

            /* heuristic search- it's likely that the next hit will be close to previous hit.
             * hintIndex = Math.Max(0, hintIndex); 
            hintIndex = Math.Min(m_arrCommands.Length - 1, hintIndex);
            int found = int.MinValue;
            //want something where s > a[i] and s < a[i+1]
            for (int i = hintIndex; i < m_arrCommands.Length; i++)
            {
                
            }
            for (int i = 0; i < hintIndex; i++)
            {

            }*/
            
            
            /*but no, we're not searching, we want begins with
             * if (s < m_arrCommands[0])
                return -1; //before everything.
            for (int i = 0; i < m_arrCommands.Length-1; i++)
            {
                if (s >= m_arrCommands[i].sCmdShortcut && s < m_arrCommands[i + 1].sCmdShortcut)
                    return i;
            }
            //if we got to the end, then we're at the end
            */
            
            if (s == "") return -1; //matches first of list?

            for (int i = 0; i < m_arrCommands.Length; i++)
            {
                if (m_arrCommands[i].sCmdShortcut.StartsWith(s))
                    return i;
            }
            
            return -1; //no match found
        }
        public string lookupOtherOptions(string prefix)
        {
            if (prefix == "") return "";            
            StringBuilder sb = new StringBuilder();
            
            for (int i = 0; i < m_arrCommands.Length; i++)
            {
                if (m_arrCommands[i].sCmdShortcut.StartsWith(prefix))
                {
                    sb.Append(m_arrCommands[i].sCmdShortcut);
                    sb.Append(",");
                }
            }
            string result = sb.ToString();
            return (result == "") ? result : result.Substring(0, result.Length - 1); //strip final ","
        }

        private string doSubstitutions(string s, Dictionary<string, string> d)
        {
            foreach (string key in d.Keys)
            {
                if (s.Contains(key))
                    s = s.Replace(key, d[key]);
            }
            return s;
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("constants:");
            sb.AppendLine("============");
            foreach (string key in m_dictConstants.Keys) sb.AppendLine(key + "=" + m_dictConstants[key]);
            sb.AppendLine("commands:");
            sb.AppendLine("============");
            foreach (LnzLaunchCommand cmd in m_arrCommands) sb.AppendLine(cmd.ToString());
            return sb.ToString();
        }

    }

    public class LnzLaunchBrowser
    {
        // run it. gives 

        public int lookupSection(string s)
        {
            return 0;

        }

        

    }
}
