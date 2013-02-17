namespace Lnzlaunch
{
    partial class FormLnzLaunch
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.txtInput = new System.Windows.Forms.TextBox();
            this.txtShortcut = new System.Windows.Forms.Label();
            this.contextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.mnuItemAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.mnItemExit = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuItemHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuItemReload = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuItemShow = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuItemEdit = new System.Windows.Forms.ToolStripMenuItem();
            this.txtOutput = new System.Windows.Forms.TextBox();
            this.lblIcon = new System.Windows.Forms.Label();
            this.contextMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // txtInput
            // 
            this.txtInput.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.txtInput.Font = new System.Drawing.Font("Verdana", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtInput.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.txtInput.Location = new System.Drawing.Point(12, 12);
            this.txtInput.Name = "txtInput";
            this.txtInput.Size = new System.Drawing.Size(180, 37);
            this.txtInput.TabIndex = 0;
            // 
            // txtShortcut
            // 
            this.txtShortcut.AutoSize = true;
            this.txtShortcut.Font = new System.Drawing.Font("Verdana", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtShortcut.ForeColor = System.Drawing.Color.Silver;
            this.txtShortcut.Location = new System.Drawing.Point(450, 20);
            this.txtShortcut.Name = "txtShortcut";
            this.txtShortcut.Size = new System.Drawing.Size(83, 29);
            this.txtShortcut.TabIndex = 1;
            this.txtShortcut.Text = "label1";
            this.txtShortcut.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // contextMenu
            // 
            this.contextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuItemAbout,
            this.mnItemExit,
            this.mnuItemHelp,
            this.toolStripSeparator1,
            this.mnuItemReload,
            this.mnuItemShow,
            this.mnuItemEdit});
            this.contextMenu.Name = "contextMenu";
            this.contextMenu.Size = new System.Drawing.Size(184, 164);
            // 
            // mnuItemAbout
            // 
            this.mnuItemAbout.Name = "mnuItemAbout";
            this.mnuItemAbout.Size = new System.Drawing.Size(183, 22);
            this.mnuItemAbout.Text = "About";
            this.mnuItemAbout.Click += new System.EventHandler(this.mnuItemAbout_Click);
            // 
            // mnItemExit
            // 
            this.mnItemExit.Name = "mnItemExit";
            this.mnItemExit.Size = new System.Drawing.Size(183, 22);
            this.mnItemExit.Text = "Quit";
            this.mnItemExit.Click += new System.EventHandler(this.mnItemExit_Click);
            // 
            // mnuItemHelp
            // 
            this.mnuItemHelp.Name = "mnuItemHelp";
            this.mnuItemHelp.Size = new System.Drawing.Size(183, 22);
            this.mnuItemHelp.Text = "Help";
            this.mnuItemHelp.Click += new System.EventHandler(this.mnuItemHelp_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(180, 6);
            // 
            // mnuItemReload
            // 
            this.mnuItemReload.Name = "mnuItemReload";
            this.mnuItemReload.Size = new System.Drawing.Size(183, 22);
            this.mnuItemReload.Text = "Reload cfg";
            this.mnuItemReload.Click += new System.EventHandler(this.mnuItemReload_Click);
            // 
            // mnuItemShow
            // 
            this.mnuItemShow.Name = "mnuItemShow";
            this.mnuItemShow.Size = new System.Drawing.Size(183, 22);
            this.mnuItemShow.Text = "Show cfg in explorer";
            this.mnuItemShow.Click += new System.EventHandler(this.mnuItemShow_Click);
            // 
            // mnuItemEdit
            // 
            this.mnuItemEdit.Name = "mnuItemEdit";
            this.mnuItemEdit.Size = new System.Drawing.Size(183, 22);
            this.mnuItemEdit.Text = "Edit cfg in notepad";
            this.mnuItemEdit.Click += new System.EventHandler(this.mnuItemEdit_Click);
            // 
            // txtOutput
            // 
            this.txtOutput.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.txtOutput.ForeColor = System.Drawing.Color.White;
            this.txtOutput.Location = new System.Drawing.Point(1, 64);
            this.txtOutput.Name = "txtOutput";
            this.txtOutput.ReadOnly = true;
            this.txtOutput.Size = new System.Drawing.Size(543, 20);
            this.txtOutput.TabIndex = 3;
            this.txtOutput.TabStop = false;
            this.txtOutput.Text = "hi";
            this.txtOutput.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // lblIcon
            // 
            this.lblIcon.Location = new System.Drawing.Point(296, 17);
            this.lblIcon.Name = "lblIcon";
            this.lblIcon.Size = new System.Drawing.Size(32, 32);
            this.lblIcon.TabIndex = 4;
            this.lblIcon.Tag = "";
            // 
            // FormLnzLaunch
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(545, 85);
            this.ContextMenuStrip = this.contextMenu;
            this.Controls.Add(this.lblIcon);
            this.Controls.Add(this.txtInput);
            this.Controls.Add(this.txtShortcut);
            this.Controls.Add(this.txtOutput);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "FormLnzLaunch";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.contextMenu.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtInput;
        private System.Windows.Forms.Label txtShortcut;
        private System.Windows.Forms.ContextMenuStrip contextMenu;
        private System.Windows.Forms.ToolStripMenuItem mnItemExit;
        private System.Windows.Forms.ToolStripMenuItem mnuItemHelp;
        private System.Windows.Forms.TextBox txtOutput;
        private System.Windows.Forms.ToolStripMenuItem mnuItemReload;
        private System.Windows.Forms.ToolStripMenuItem mnuItemShow;
        private System.Windows.Forms.ToolStripMenuItem mnuItemEdit;
        private System.Windows.Forms.Label lblIcon;
        private System.Windows.Forms.ToolStripMenuItem mnuItemAbout;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
    }
}

