namespace MapEditor
{
    partial class SoundFileView
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
            this.butBrowse = new System.Windows.Forms.Button();
            this.butStop = new System.Windows.Forms.Button();
            this.folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.lstBoxSounds = new System.Windows.Forms.ListBox();
            this.butPlay = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // butBrowse
            // 
            this.butBrowse.Location = new System.Drawing.Point(12, 375);
            this.butBrowse.Name = "butBrowse";
            this.butBrowse.Size = new System.Drawing.Size(75, 23);
            this.butBrowse.TabIndex = 0;
            this.butBrowse.Text = "Browse";
            this.butBrowse.UseVisualStyleBackColor = true;
            this.butBrowse.Click += new System.EventHandler(this.butBrowse_Click);
            // 
            // butStop
            // 
            this.butStop.Location = new System.Drawing.Point(174, 375);
            this.butStop.Name = "butStop";
            this.butStop.Size = new System.Drawing.Size(75, 23);
            this.butStop.TabIndex = 1;
            this.butStop.Text = "Stop";
            this.butStop.UseVisualStyleBackColor = true;
            this.butStop.Click += new System.EventHandler(this.butStop_Click);
            // 
            // lstBoxSounds
            // 
            this.lstBoxSounds.FormattingEnabled = true;
            this.lstBoxSounds.Location = new System.Drawing.Point(12, 12);
            this.lstBoxSounds.Name = "lstBoxSounds";
            this.lstBoxSounds.Size = new System.Drawing.Size(442, 355);
            this.lstBoxSounds.TabIndex = 2;
            this.lstBoxSounds.DoubleClick += new System.EventHandler(this.lstBoxSounds_DoubleClick);
            this.lstBoxSounds.MouseDown += new System.Windows.Forms.MouseEventHandler(this.lstBoxSounds_MouseDown);
            // 
            // butPlay
            // 
            this.butPlay.Location = new System.Drawing.Point(93, 375);
            this.butPlay.Name = "butPlay";
            this.butPlay.Size = new System.Drawing.Size(75, 23);
            this.butPlay.TabIndex = 3;
            this.butPlay.Text = "Play";
            this.butPlay.UseVisualStyleBackColor = true;
            this.butPlay.Click += new System.EventHandler(this.butPlay_Click);
            // 
            // SoundFileView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(466, 410);
            this.Controls.Add(this.butPlay);
            this.Controls.Add(this.lstBoxSounds);
            this.Controls.Add(this.butStop);
            this.Controls.Add(this.butBrowse);
            this.Name = "SoundFileView";
            this.Text = "SoundFileView";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button butBrowse;
        private System.Windows.Forms.Button butStop;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog;
        private System.Windows.Forms.ListBox lstBoxSounds;
        private System.Windows.Forms.Button butPlay;
    }
}