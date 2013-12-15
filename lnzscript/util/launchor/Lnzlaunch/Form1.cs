using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;

namespace Lnzlaunch
{
    //todo: version 2, automatically detect changes in cfg file
    public partial class FormLnzLaunch : Form
    {
        string PATH_CLIPBOARD = @"C:\Documents and Settings\bfisher\My Documents\Visual Studio 2005\Projects\Lnzlaunch\clipboard\";
        string PATH_CFG = @"C:\Documents and Settings\bfisher\My Documents\Visual Studio 2005\Projects\Lnzlaunch\act.cfg";

        //create mutex to disallow > 1 instance? For now the alt-space does that.
        //todo: localize strings, by looking for lnztrace() messages and mbox and exceptions
        //if you type something that doesn't match, and then type up/down, should it look for an apprproiate index?

        // the "CurrentDirectory" should not be important. Use absolute paths for everything!
        // (using dialogs will chxange the currentdirectory, unless a flag is passed.)
        KeyboardHook m_hook = new KeyboardHook();
        LnzLaunchData m_launchData = new LnzLaunchData();
        int m_currentIndex;
        public FormLnzLaunch()
        {
            InitializeComponent();
            this.txtInput.LostFocus += new EventHandler(Form1_LostFocus);
            this.txtInput.KeyDown += new KeyEventHandler(Form1_KeyDown);

            this.txtInput.TextChanged += new EventHandler(txtInput_TextChanged);

            this.MouseDown += new MouseEventHandler(Form1_MouseDown);

            m_hook.KeyPressed += new EventHandler<KeyPressedEventArgs>(m_hook_KeyPressed);
            this.ShowInTaskbar = false;
            this.TopMost = true;
            this.Text = "lnzlaunch";
            this.txtShortcut.Text = "";
            this.txtOutput.Text = "";
            

            loadCfgFile(PATH_CFG);

            //test loading cfg file
            //TextWriter tw = new StreamWriter(@"C:\Documents and Settings\bfisher\My Documents\Visual Studio 2005\Projects\Lnzlaunch\testout.txt");
            //tw.Write(this.m_launchData.ToString());
            //tw.Close();
                       
            m_currentIndex = -1; //start with index before everything
            lnzhide();
        }


        //http://www.codeproject.com/KB/cs/csharpmovewindow.aspx
        //or maybe http://74.125.113.132/search?q=cache:uTpnxcbUsmAJ:community.sharpdevelop.net/forums/p/5713/16376.aspx+c%23+drag+window&cd=4&hl=en&ct=clnk&gl=us&client=firefox-a, but this works ok
        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HT_CAPTION = 0x2;
        [DllImportAttribute("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);
        [DllImportAttribute("user32.dll")]
        public static extern bool ReleaseCapture();
        private void Form1_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                ReleaseCapture();
                SendMessage(Handle, WM_NCLBUTTONDOWN, HT_CAPTION, 0);
            }
        }
        
        void txtInput_TextChanged(object sender, EventArgs e)
        {
            lnztrace(""); //clear the output

            string sInput = this.txtInput.Text;
            // if before the space, it's a complete match, then allow passing arguments
            if (sInput.Contains(" "))
            {
                int found = this.m_launchData.lookupExactCommandIndex(sInput.Split(' ')[0]);
                if (found!=-1)
                    sInput = sInput.Split(' ')[0]; // allow passing arguments. otherwise won't match.
            }
            
            //todo: if command is a symbol, like = , maybe doesn't need a space before arguments.

            int index = this.m_launchData.lookupApproximateCommandIndex(sInput);
            this.m_currentIndex = index;
            if (index == -1 || index == this.m_launchData.m_arrCommands.Length)
            {
                lnzsetIcon(null);
                this.txtShortcut.Text = "";
            }
            else
            {
                lnzsetIcon(this.m_launchData.m_arrCommands[index]);
                this.txtShortcut.Text = (this.m_launchData.m_arrCommands[index].sCmdShortcut);
            }
        }

        private void switchicon(Image b)
        {
            Image oldimage = this.lblIcon.Image;
            this.lblIcon.Image = b;
            if (oldimage != null) oldimage.Dispose();
        }
        public void lnzsetIcon(LnzLaunchCommand cmd)
        {
            if (cmd== null) {switchicon(null); return;}
            string sFilename = (cmd.sCustomIcon!=null) ? cmd.sCustomIcon : LaunchFiles.getBaseFileFromCommand(cmd);
            if (sFilename== null) {switchicon(null); return;}
            Icon icn = GetFileIcon.Getfileicon(sFilename);
            if (icn == null) { switchicon(null); return; }
            
            this.switchicon( icn.ToBitmap());
            icn.Dispose(); //it has been copied to the bitmap, so this can be freed.
        }
        public bool registerHotKey()
        {
            try
            {
                m_hook.RegisterHotKey(LnzlaunchModifierKeys.Alt, System.Windows.Forms.Keys.Space);
            }
            catch (InvalidOperationException)
            {
                MessageBox.Show("LnzLaunchor: Could not register the hotkey Alt-Space. Maybe another instance of LnzLaunchor is already open.");
                return false;
            }
            return true;
        }

        void Form1_LostFocus(object sender, EventArgs e)
        {
            lnzhide();
        }


        private void lnzhide()
        {
            this.Visible = false;
            //this.WindowState = FormWindowState.Minimized;
        }
       
        private void lnzshow()
        {
            //select everything in the textbox
            txtInput.SelectAll();

            this.Visible = true;
            //this.Focus();
            this.txtInput.Focus();
            this.Activate(); //this is crucial! activates the form
        }
        private void lnztrace(string s)
        {
            this.txtOutput.Text = s;
        }
        private void lnzbox(string s) { MessageBox.Show(s); }

        void m_hook_KeyPressed(object sender, KeyPressedEventArgs e)
        {
            if (!this.Visible)
                lnzshow();
            else
                lnzhide();
        }

        void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            string sPrevOutput = this.txtOutput.Text;
            
            if (e.KeyCode == Keys.Escape && !e.Control && !e.Alt && !e.Shift) //escape hides window
            {
                e.SuppressKeyPress = true;
                lnzhide();
            }
            else if (e.KeyCode == Keys.Escape && !e.Control && !e.Alt && e.Shift) //shift+escape closes
            {
                this.Close();
            }
            else if (e.KeyCode == Keys.Escape && !e.Control && !e.Alt && e.Shift) //control+shift+c copies from output
            {
                Clipboard.SetDataObject(sPrevOutput, true);
                lnztrace("Output copied.");
            }
            else if (e.KeyCode == Keys.Up && !e.Control && !e.Alt && !e.Shift)
            {
                e.SuppressKeyPress = true;
                this.moveUpDown(-1);
            }
            else if (e.KeyCode == Keys.Down && !e.Control && !e.Alt && !e.Shift)
            {
                e.SuppressKeyPress = true;
                this.moveUpDown(1);
            }
            //else if (e.KeyCode == Keys.Tab && !e.Control && !e.Alt && !e.Shift)
            else if (e.KeyCode == Keys.Space && e.Control && !e.Alt && !e.Shift)
            {
                e.SuppressKeyPress = true;
                string sOptions = this.m_launchData.lookupOtherOptions(this.txtInput.Text);
                if (sOptions == "")
                    lnztrace("No cmds begin with: " + this.txtInput.Text);
                else
                    lnztrace(sOptions);
            }
            else if (e.KeyCode == Keys.Enter && !e.Control && !e.Alt)
            {
                e.SuppressKeyPress = true;
                if (txtInput.Text == "") 
                    lnzhide();
                else
                    runCurrentCommand(e.Shift);
            }
            else if (e.KeyCode == Keys.C && e.Control && !e.Alt && e.Shift) //Cntrl+shift+c copies output to clipboard
            {
                e.SuppressKeyPress = true;
                Clipboard.SetText(this.txtOutput.Text);
            }
            else if (e.KeyCode == Keys.Back && e.Control && !e.Alt && !e.Shift) //Control-backspace deletes word
            {
                //TODO: should this work with space as well? originally for space, but that's not used much, so just changed to .
                //see http://stackoverflow.com/questions/1124639/winforms-textbox-using-ctrl-backspace-to-delete-whole-word
                e.SuppressKeyPress = true;
                int selStart = txtInput.SelectionStart;
                while (selStart > 0 && txtInput.Text.Substring(selStart - 1, 1) == ".")
                {
                    selStart--;
                }
                int prevSpacePos = -1;
                if (selStart != 0)
                {
                    prevSpacePos = txtInput.Text.LastIndexOf('.', selStart - 1);
                }
                txtInput.Select(prevSpacePos + 1, txtInput.SelectionStart - prevSpacePos - 1);
                txtInput.SelectedText = "";

            }
            else if (e.KeyCode == Keys.S && e.Control && !e.Alt && e.Shift) //Ctrl+Shift+S saves what is on clipboard
            {
                e.SuppressKeyPress = true;
                saveClip();
            }
            else if (e.Alt && !e.Shift && (int)e.KeyCode >= (int)Keys.A && (int)e.KeyCode <= (int)Keys.Z)
            {
                e.SuppressKeyPress = true;
                string letter = new string((char)e.KeyValue, 1); //turn Keys.A into "A"
                saveClipboardBucket(e.Control, letter);
            }
        }

        private void saveClipboardBucket(bool bSaveOrRead, string letter)
        {
            string file = PATH_CLIPBOARD + letter + ".txt";

            if (bSaveOrRead)
            {
                //save into the clipboard bin
                lnztrace("Saved into bucket " + letter + ".");
                IDataObject data = Clipboard.GetDataObject();
                if (data == null) { lnztrace("Nothing in clipboard."); return; }
                if (!data.GetDataPresent(DataFormats.Text)) { lnztrace("No text in clipboard."); return; }
                    
                string s = (string)data.GetData(DataFormats.Text, true);
                try
                {
                    TextWriter tw = new StreamWriter(file, false); //don't append
                    tw.Write(s);
                    tw.Close();
                }
                catch
                {
                    lnztrace("Error writing to bucket " + letter + ".");
                    return;
                }
                lnztrace("Saved to bucket " + letter + ".");
            }
            else
            {
                //read from the clipboard bin
                if (!File.Exists(file)) { lnztrace("Nothing saved into bucket " + letter + "."); return; }

                TextReader tr = new StreamReader(file);
                Clipboard.SetText(tr.ReadToEnd());
                tr.Close();
                lnztrace("Copied from bucket " + letter + ".");
            }
        }

        private void runCurrentCommand(bool bOpenFolderInstead)
        {
            if (this.m_currentIndex != -1 && this.m_currentIndex != this.m_launchData.m_arrCommands.Length)
            {
                if (bOpenFolderInstead)
                {
                    LaunchFiles.openCommandContainingFolder(this.m_launchData.m_arrCommands[this.m_currentIndex]);
                    lnzhide();
                }
                else
                {
                    string sStdOut = "";
                    bool bErrorOccurred = false;
                    try
                    {
                        sStdOut = LaunchFiles.runCommand(this.txtInput.Text, this.m_launchData.m_arrCommands[this.m_currentIndex]);
                    }
                    catch (LnzLaunchDataException ex)
                    {
                        lnztrace(ex.Message);
                        bErrorOccurred = true;
                    }
                    if (!bErrorOccurred)
                    {
                        if (this.m_launchData.m_arrCommands[this.m_currentIndex].bRemainOpenAfterRunning)
                        {
                            //txtInput.Text = ""; that clears the icon, which looks odd
                            txtInput.SelectAll();
                            lnztrace(sStdOut);
                        }
                        else
                            lnzhide();
                    }
                }
            }
        }

        private void moveUpDown(int change)
        {
            int newIndex = this.m_currentIndex + change;
            //never let it get more than one away from the data
            newIndex = Math.Max(-1, newIndex);
            newIndex = Math.Min(this.m_launchData.m_arrCommands.Length, newIndex);

            if (newIndex == -1 || newIndex == this.m_launchData.m_arrCommands.Length)
            {
                this.txtInput.Text = ""; //calls textChanged() ! right now!
            }
            else
            {
                this.txtInput.Text = this.m_launchData.m_arrCommands[newIndex].sCmdShortcut;
                //calls textChanged() ! right now!
                this.txtInput.SelectAll();
            }

            this.m_currentIndex = newIndex; //put this after this.txtInput, because textChanged() could have set index differently
        }




        public void loadCfgFile(string filepath)
        {
            // if there isn't a file, should copy default cfg file to that location.
            if (!File.Exists(filepath))
            {
                //copy default to that location
                //raise an exception if that copy fails
                lnzbox("cfg file not found");
                //lnztrace("cfg file not found, using defaults.");
                return;
            }

            IniFileParsing inifile;
            List<KeyValuePair<string, string>> constants; 
            List<KeyValuePair<string, string>> commands; 
            List<KeyValuePair<string, string>> icons;
            try
            {
                inifile = new IniFileParsing(filepath, true);
                List<string> l = inifile.GetCategories();
                if (l.IndexOf("commands") == -1)
                { 
                    lnzbox("Error loading cfg file: no 'commands' section.");
                    return;
                }
                constants = inifile.GetKeysAndValues("constants");
                commands = inifile.GetKeysAndValues("commands");
                icons = inifile.GetKeysAndValues("icons");
            }
            catch (IniFileParsingException ex) 
            {
                lnzbox("Error loading cfg file: "+ex.Message);
                return;
            }
            
            try
            {
                m_launchData.loadData(constants, commands, icons);
            }
            catch (LnzLaunchDataException ex) 
            {
                lnzbox("cfg file: "+ex.Message);
                return;
            }
        }

        public void saveClip()
        {
            if (Clipboard.GetDataObject() != null)
            {
                IDataObject data = Clipboard.GetDataObject();

                if (data.GetDataPresent(DataFormats.Bitmap))
                {
                    Image image = (Image)data.GetData(DataFormats.Bitmap, true);

                    // Displays a SaveFileDialog so the user can save the Image
                    SaveFileDialog saveFileDialog1 = new SaveFileDialog();
                    saveFileDialog1.Filter = "Png Image|*.png|Bitmap Image|*.bmp";
                    saveFileDialog1.Title = "Save clipboard contents...";
                    saveFileDialog1.ShowDialog();

                    if (saveFileDialog1.FileName != "")
                    {
                        System.IO.FileStream fs = (System.IO.FileStream)saveFileDialog1.OpenFile();
                        // Saves the Image in the appropriate ImageFormat based upon the
                        // File type selected in the dialog box.
                        // NOTE that the FilterIndex property is one-based.
                        if (saveFileDialog1.FilterIndex == 1)
                            image.Save(fs, System.Drawing.Imaging.ImageFormat.Png);
                        else
                            image.Save(fs, System.Drawing.Imaging.ImageFormat.Bmp);

                        fs.Close();
                    }
                    image.Dispose();
                    lnzhide();
                }
                else if (data.GetDataPresent(DataFormats.Text))
                {
                    string s = (string)data.GetData(DataFormats.Text, true);
                    SaveFileDialog saveFileDialog1 = new SaveFileDialog();
                    saveFileDialog1.Filter = "Text file|*.txt";
                    saveFileDialog1.Title = "Save clipboard contents...";
                    saveFileDialog1.ShowDialog();
                    if (saveFileDialog1.FileName != "")
                    {
                        TextWriter tw = new StreamWriter(saveFileDialog1.FileName);
                        tw.Write(s);
                        tw.Close();
                    }
                    lnzhide();
                }
                else
                {
                    lnztrace("Data in clipboard not in a known format.");
                }
            }
            else
            {
                lnztrace("The clipboard was empty.");
            }
        }

        private void mnItemExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        private void mnuItemAbout_Click(object sender, EventArgs e)
        {
            MessageBox.Show("LnzLaunch 0.1\r\n\r\nBen Fisher, 2009. GPLv3.\r\nhttps://github.com/moltenform/lnzscript");
        }
        private void mnuItemHelp_Click(object sender, EventArgs e)
        {
            Process.Start("https://github.com/moltenform/lnzscript");
        }
        private void mnuItemReload_Click(object sender, EventArgs e)
        {
            loadCfgFile(PATH_CFG);
        }
        private void mnuItemShow_Click(object sender, EventArgs e)
        {
            LaunchFiles.showFileInExplorer(PATH_CFG);
        }
        private void mnuItemEdit_Click(object sender, EventArgs e)
        {
            Process.Start("notepad",  "\"" + PATH_CFG + "\"");
        }

     
    }
}

