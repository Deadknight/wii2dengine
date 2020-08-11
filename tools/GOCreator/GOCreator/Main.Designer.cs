namespace GOCreator
{
    partial class Main
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
            this.lstBoxImage = new System.Windows.Forms.ListBox();
            this.label1 = new System.Windows.Forms.Label();
            this.lstBoxGS = new System.Windows.Forms.ListBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.txtDir = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.butSave = new System.Windows.Forms.Button();
            this.txtName = new System.Windows.Forms.TextBox();
            this.butSaveGO = new System.Windows.Forms.Button();
            this.butLoadGO = new System.Windows.Forms.Button();
            this.butNew = new System.Windows.Forms.Button();
            this.butAdd = new System.Windows.Forms.Button();
            this.lstBoxGF = new System.Windows.Forms.ListBox();
            this.label3 = new System.Windows.Forms.Label();
            this.openFileDialogLoad = new System.Windows.Forms.OpenFileDialog();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialogSave = new System.Windows.Forms.SaveFileDialog();
            this.contextMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.deleteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cBoxFlipY = new System.Windows.Forms.CheckBox();
            this.cBoxFlipX = new System.Windows.Forms.CheckBox();
            this.contextMenuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // lstBoxImage
            // 
            this.lstBoxImage.FormattingEnabled = true;
            this.lstBoxImage.Location = new System.Drawing.Point(12, 25);
            this.lstBoxImage.Name = "lstBoxImage";
            this.lstBoxImage.Size = new System.Drawing.Size(120, 329);
            this.lstBoxImage.TabIndex = 1;
            this.lstBoxImage.SelectedIndexChanged += new System.EventHandler(this.lstBoxImage_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Image List";
            // 
            // lstBoxGS
            // 
            this.lstBoxGS.FormattingEnabled = true;
            this.lstBoxGS.Location = new System.Drawing.Point(138, 25);
            this.lstBoxGS.Name = "lstBoxGS";
            this.lstBoxGS.SelectionMode = System.Windows.Forms.SelectionMode.MultiSimple;
            this.lstBoxGS.Size = new System.Drawing.Size(146, 212);
            this.lstBoxGS.TabIndex = 6;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(151, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(92, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Gameobject State";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(139, 272);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(20, 13);
            this.label6.TabIndex = 22;
            this.label6.Text = "Dir";
            // 
            // txtDir
            // 
            this.txtDir.Location = new System.Drawing.Point(180, 269);
            this.txtDir.Name = "txtDir";
            this.txtDir.Size = new System.Drawing.Size(100, 20);
            this.txtDir.TabIndex = 21;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(139, 246);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 13);
            this.label5.TabIndex = 19;
            this.label5.Text = "Name";
            // 
            // butSave
            // 
            this.butSave.Location = new System.Drawing.Point(142, 295);
            this.butSave.Name = "butSave";
            this.butSave.Size = new System.Drawing.Size(75, 23);
            this.butSave.TabIndex = 20;
            this.butSave.Text = "Save";
            this.butSave.UseVisualStyleBackColor = true;
            this.butSave.Click += new System.EventHandler(this.butSave_Click);
            // 
            // txtName
            // 
            this.txtName.Location = new System.Drawing.Point(180, 243);
            this.txtName.Name = "txtName";
            this.txtName.Size = new System.Drawing.Size(100, 20);
            this.txtName.TabIndex = 18;
            // 
            // butSaveGO
            // 
            this.butSaveGO.Location = new System.Drawing.Point(302, 331);
            this.butSaveGO.Name = "butSaveGO";
            this.butSaveGO.Size = new System.Drawing.Size(75, 23);
            this.butSaveGO.TabIndex = 26;
            this.butSaveGO.Text = "Save GO";
            this.butSaveGO.UseVisualStyleBackColor = true;
            this.butSaveGO.Click += new System.EventHandler(this.butSaveGO_Click);
            // 
            // butLoadGO
            // 
            this.butLoadGO.Location = new System.Drawing.Point(221, 331);
            this.butLoadGO.Name = "butLoadGO";
            this.butLoadGO.Size = new System.Drawing.Size(75, 23);
            this.butLoadGO.TabIndex = 24;
            this.butLoadGO.Text = "Load GO";
            this.butLoadGO.UseVisualStyleBackColor = true;
            this.butLoadGO.Click += new System.EventHandler(this.butLoadGO_Click);
            // 
            // butNew
            // 
            this.butNew.Location = new System.Drawing.Point(223, 295);
            this.butNew.Name = "butNew";
            this.butNew.Size = new System.Drawing.Size(75, 23);
            this.butNew.TabIndex = 25;
            this.butNew.Text = "New";
            this.butNew.UseVisualStyleBackColor = true;
            this.butNew.Click += new System.EventHandler(this.butNew_Click);
            // 
            // butAdd
            // 
            this.butAdd.Location = new System.Drawing.Point(140, 331);
            this.butAdd.Name = "butAdd";
            this.butAdd.Size = new System.Drawing.Size(75, 23);
            this.butAdd.TabIndex = 23;
            this.butAdd.Text = "Add";
            this.butAdd.UseVisualStyleBackColor = true;
            this.butAdd.Click += new System.EventHandler(this.butAdd_Click);
            // 
            // lstBoxGF
            // 
            this.lstBoxGF.FormattingEnabled = true;
            this.lstBoxGF.Location = new System.Drawing.Point(290, 25);
            this.lstBoxGF.Name = "lstBoxGF";
            this.lstBoxGF.SelectionMode = System.Windows.Forms.SelectionMode.MultiSimple;
            this.lstBoxGF.Size = new System.Drawing.Size(158, 212);
            this.lstBoxGF.TabIndex = 28;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(287, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(87, 13);
            this.label3.TabIndex = 27;
            this.label3.Text = "Gameobject Flag";
            // 
            // openFileDialogLoad
            // 
            this.openFileDialogLoad.Filter = "Gameobject File|*.go";
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "PNG Files|*.png";
            // 
            // saveFileDialogSave
            // 
            this.saveFileDialogSave.Filter = "Gameobject File|*.go";
            // 
            // contextMenuStrip
            // 
            this.contextMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.deleteToolStripMenuItem});
            this.contextMenuStrip.Name = "contextMenuStrip";
            this.contextMenuStrip.Size = new System.Drawing.Size(108, 26);
            // 
            // deleteToolStripMenuItem
            // 
            this.deleteToolStripMenuItem.Name = "deleteToolStripMenuItem";
            this.deleteToolStripMenuItem.Size = new System.Drawing.Size(107, 22);
            this.deleteToolStripMenuItem.Text = "Delete";
            // 
            // cBoxFlipY
            // 
            this.cBoxFlipY.AutoSize = true;
            this.cBoxFlipY.Location = new System.Drawing.Point(345, 245);
            this.cBoxFlipY.Name = "cBoxFlipY";
            this.cBoxFlipY.Size = new System.Drawing.Size(49, 17);
            this.cBoxFlipY.TabIndex = 30;
            this.cBoxFlipY.Text = "FlipY";
            this.cBoxFlipY.UseVisualStyleBackColor = true;
            // 
            // cBoxFlipX
            // 
            this.cBoxFlipX.AutoSize = true;
            this.cBoxFlipX.Location = new System.Drawing.Point(290, 245);
            this.cBoxFlipX.Name = "cBoxFlipX";
            this.cBoxFlipX.Size = new System.Drawing.Size(49, 17);
            this.cBoxFlipX.TabIndex = 29;
            this.cBoxFlipX.Text = "FlipX";
            this.cBoxFlipX.UseVisualStyleBackColor = true;
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(460, 362);
            this.Controls.Add(this.cBoxFlipY);
            this.Controls.Add(this.cBoxFlipX);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.lstBoxGF);
            this.Controls.Add(this.butSaveGO);
            this.Controls.Add(this.butLoadGO);
            this.Controls.Add(this.butNew);
            this.Controls.Add(this.butAdd);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.txtDir);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.butSave);
            this.Controls.Add(this.txtName);
            this.Controls.Add(this.lstBoxGS);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lstBoxImage);
            this.Name = "Main";
            this.Text = "Gameobject Creator";
            this.contextMenuStrip.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox lstBoxImage;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListBox lstBoxGS;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtDir;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button butSave;
        private System.Windows.Forms.TextBox txtName;
        private System.Windows.Forms.Button butSaveGO;
        private System.Windows.Forms.Button butLoadGO;
        private System.Windows.Forms.Button butNew;
        private System.Windows.Forms.Button butAdd;
        private System.Windows.Forms.ListBox lstBoxGF;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.OpenFileDialog openFileDialogLoad;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.SaveFileDialog saveFileDialogSave;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem deleteToolStripMenuItem;
        private System.Windows.Forms.CheckBox cBoxFlipY;
        private System.Windows.Forms.CheckBox cBoxFlipX;
    }
}

