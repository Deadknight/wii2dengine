namespace UnitCreator
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
            this.contextMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.deleteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label1 = new System.Windows.Forms.Label();
            this.butAdd = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.lstBoxLookDirection = new System.Windows.Forms.ListBox();
            this.lstBoxMF = new System.Windows.Forms.ListBox();
            this.label3 = new System.Windows.Forms.Label();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.lstBoxMS = new System.Windows.Forms.ListBox();
            this.label4 = new System.Windows.Forms.Label();
            this.txtName = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.butSave = new System.Windows.Forms.Button();
            this.butLoadUnit = new System.Windows.Forms.Button();
            this.butNew = new System.Windows.Forms.Button();
            this.openFileDialogLoad = new System.Windows.Forms.OpenFileDialog();
            this.butSaveUnit = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.txtDir = new System.Windows.Forms.TextBox();
            this.saveFileDialogSave = new System.Windows.Forms.SaveFileDialog();
            this.cBoxDual = new System.Windows.Forms.CheckBox();
            this.cBoxFlipX = new System.Windows.Forms.CheckBox();
            this.cBoxFlipY = new System.Windows.Forms.CheckBox();
            this.label7 = new System.Windows.Forms.Label();
            this.txtPhoto = new System.Windows.Forms.TextBox();
            this.contextMenuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // lstBoxImage
            // 
            this.lstBoxImage.ContextMenuStrip = this.contextMenuStrip;
            this.lstBoxImage.FormattingEnabled = true;
            this.lstBoxImage.Location = new System.Drawing.Point(12, 25);
            this.lstBoxImage.Name = "lstBoxImage";
            this.lstBoxImage.Size = new System.Drawing.Size(120, 329);
            this.lstBoxImage.TabIndex = 0;
            this.lstBoxImage.SelectedIndexChanged += new System.EventHandler(this.lstBoxImage_SelectedIndexChanged);
            // 
            // contextMenuStrip
            // 
            this.contextMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.deleteToolStripMenuItem});
            this.contextMenuStrip.Name = "contextMenuStrip";
            this.contextMenuStrip.Size = new System.Drawing.Size(153, 48);
            // 
            // deleteToolStripMenuItem
            // 
            this.deleteToolStripMenuItem.Name = "deleteToolStripMenuItem";
            this.deleteToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.deleteToolStripMenuItem.Text = "Delete";
            this.deleteToolStripMenuItem.Click += new System.EventHandler(this.deleteToolStripMenuItem_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Image List";
            // 
            // butAdd
            // 
            this.butAdd.Location = new System.Drawing.Point(143, 331);
            this.butAdd.Name = "butAdd";
            this.butAdd.Size = new System.Drawing.Size(75, 23);
            this.butAdd.TabIndex = 2;
            this.butAdd.Text = "Add";
            this.butAdd.UseVisualStyleBackColor = true;
            this.butAdd.Click += new System.EventHandler(this.butAdd_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(151, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(76, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Look Direction";
            // 
            // lstBoxLookDirection
            // 
            this.lstBoxLookDirection.FormattingEnabled = true;
            this.lstBoxLookDirection.Location = new System.Drawing.Point(138, 25);
            this.lstBoxLookDirection.Name = "lstBoxLookDirection";
            this.lstBoxLookDirection.SelectionMode = System.Windows.Forms.SelectionMode.MultiSimple;
            this.lstBoxLookDirection.Size = new System.Drawing.Size(130, 212);
            this.lstBoxLookDirection.TabIndex = 4;
            // 
            // lstBoxMF
            // 
            this.lstBoxMF.FormattingEnabled = true;
            this.lstBoxMF.Location = new System.Drawing.Point(274, 25);
            this.lstBoxMF.Name = "lstBoxMF";
            this.lstBoxMF.SelectionMode = System.Windows.Forms.SelectionMode.MultiSimple;
            this.lstBoxMF.Size = new System.Drawing.Size(165, 212);
            this.lstBoxMF.TabIndex = 6;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(300, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(80, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Movement Flag";
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "PNG Files|*.png";
            // 
            // lstBoxMS
            // 
            this.lstBoxMS.FormattingEnabled = true;
            this.lstBoxMS.Location = new System.Drawing.Point(445, 25);
            this.lstBoxMS.Name = "lstBoxMS";
            this.lstBoxMS.SelectionMode = System.Windows.Forms.SelectionMode.MultiSimple;
            this.lstBoxMS.Size = new System.Drawing.Size(207, 212);
            this.lstBoxMS.TabIndex = 8;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(456, 9);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(85, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Movement State";
            // 
            // txtName
            // 
            this.txtName.Location = new System.Drawing.Point(181, 243);
            this.txtName.Name = "txtName";
            this.txtName.Size = new System.Drawing.Size(100, 20);
            this.txtName.TabIndex = 9;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(140, 246);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "Name";
            // 
            // butSave
            // 
            this.butSave.Location = new System.Drawing.Point(287, 241);
            this.butSave.Name = "butSave";
            this.butSave.Size = new System.Drawing.Size(75, 23);
            this.butSave.TabIndex = 11;
            this.butSave.Text = "Save";
            this.butSave.UseVisualStyleBackColor = true;
            this.butSave.Click += new System.EventHandler(this.butSave_Click);
            // 
            // butLoadUnit
            // 
            this.butLoadUnit.Location = new System.Drawing.Point(224, 331);
            this.butLoadUnit.Name = "butLoadUnit";
            this.butLoadUnit.Size = new System.Drawing.Size(75, 23);
            this.butLoadUnit.TabIndex = 12;
            this.butLoadUnit.Text = "Load Unit";
            this.butLoadUnit.UseVisualStyleBackColor = true;
            this.butLoadUnit.Click += new System.EventHandler(this.butLoadUnit_Click);
            // 
            // butNew
            // 
            this.butNew.Location = new System.Drawing.Point(577, 331);
            this.butNew.Name = "butNew";
            this.butNew.Size = new System.Drawing.Size(75, 23);
            this.butNew.TabIndex = 13;
            this.butNew.Text = "New";
            this.butNew.UseVisualStyleBackColor = true;
            this.butNew.Click += new System.EventHandler(this.butNew_Click);
            // 
            // openFileDialogLoad
            // 
            this.openFileDialogLoad.Filter = "Unit File|*.unit";
            // 
            // butSaveUnit
            // 
            this.butSaveUnit.Location = new System.Drawing.Point(305, 331);
            this.butSaveUnit.Name = "butSaveUnit";
            this.butSaveUnit.Size = new System.Drawing.Size(75, 23);
            this.butSaveUnit.TabIndex = 15;
            this.butSaveUnit.Text = "Save Unit";
            this.butSaveUnit.UseVisualStyleBackColor = true;
            this.butSaveUnit.Click += new System.EventHandler(this.butSaveUnit_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(140, 272);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(20, 13);
            this.label6.TabIndex = 17;
            this.label6.Text = "Dir";
            // 
            // txtDir
            // 
            this.txtDir.Location = new System.Drawing.Point(181, 269);
            this.txtDir.Name = "txtDir";
            this.txtDir.Size = new System.Drawing.Size(100, 20);
            this.txtDir.TabIndex = 16;
            // 
            // saveFileDialogSave
            // 
            this.saveFileDialogSave.Filter = "Unit File|*.unit";
            // 
            // cBoxDual
            // 
            this.cBoxDual.AutoSize = true;
            this.cBoxDual.Location = new System.Drawing.Point(287, 270);
            this.cBoxDual.Name = "cBoxDual";
            this.cBoxDual.Size = new System.Drawing.Size(48, 17);
            this.cBoxDual.TabIndex = 18;
            this.cBoxDual.Text = "Dual";
            this.cBoxDual.UseVisualStyleBackColor = true;
            // 
            // cBoxFlipX
            // 
            this.cBoxFlipX.AutoSize = true;
            this.cBoxFlipX.Location = new System.Drawing.Point(341, 270);
            this.cBoxFlipX.Name = "cBoxFlipX";
            this.cBoxFlipX.Size = new System.Drawing.Size(49, 17);
            this.cBoxFlipX.TabIndex = 19;
            this.cBoxFlipX.Text = "FlipX";
            this.cBoxFlipX.UseVisualStyleBackColor = true;
            // 
            // cBoxFlipY
            // 
            this.cBoxFlipY.AutoSize = true;
            this.cBoxFlipY.Location = new System.Drawing.Point(396, 270);
            this.cBoxFlipY.Name = "cBoxFlipY";
            this.cBoxFlipY.Size = new System.Drawing.Size(49, 17);
            this.cBoxFlipY.TabIndex = 20;
            this.cBoxFlipY.Text = "FlipY";
            this.cBoxFlipY.UseVisualStyleBackColor = true;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(140, 298);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(35, 13);
            this.label7.TabIndex = 22;
            this.label7.Text = "Photo";
            // 
            // txtPhoto
            // 
            this.txtPhoto.Location = new System.Drawing.Point(181, 295);
            this.txtPhoto.Name = "txtPhoto";
            this.txtPhoto.Size = new System.Drawing.Size(100, 20);
            this.txtPhoto.TabIndex = 21;
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(664, 360);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.txtPhoto);
            this.Controls.Add(this.cBoxFlipY);
            this.Controls.Add(this.cBoxFlipX);
            this.Controls.Add(this.cBoxDual);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.txtDir);
            this.Controls.Add(this.butSaveUnit);
            this.Controls.Add(this.butLoadUnit);
            this.Controls.Add(this.butNew);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.butSave);
            this.Controls.Add(this.txtName);
            this.Controls.Add(this.lstBoxMF);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.lstBoxLookDirection);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.lstBoxMS);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.butAdd);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lstBoxImage);
            this.Name = "Main";
            this.Text = "Unit Creator";
            this.contextMenuStrip.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox lstBoxImage;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button butAdd;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ListBox lstBoxLookDirection;
        private System.Windows.Forms.ListBox lstBoxMF;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.ListBox lstBoxMS;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtName;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button butSave;
        private System.Windows.Forms.Button butLoadUnit;
        private System.Windows.Forms.Button butNew;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem deleteToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialogLoad;
        private System.Windows.Forms.Button butSaveUnit;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtDir;
        private System.Windows.Forms.SaveFileDialog saveFileDialogSave;
        private System.Windows.Forms.CheckBox cBoxDual;
        private System.Windows.Forms.CheckBox cBoxFlipX;
        private System.Windows.Forms.CheckBox cBoxFlipY;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox txtPhoto;
    }
}

