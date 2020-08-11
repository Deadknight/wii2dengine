namespace MapEditor
{
    partial class BoundaryForm
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
            this.listBoxBoundary = new System.Windows.Forms.ListBox();
            this.contextMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.deleteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label1 = new System.Windows.Forms.Label();
            this.butSave = new System.Windows.Forms.Button();
            this.butClear = new System.Windows.Forms.Button();
            this.butNew = new System.Windows.Forms.Button();
            this.contextMenuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // listBoxBoundary
            // 
            this.listBoxBoundary.ContextMenuStrip = this.contextMenuStrip;
            this.listBoxBoundary.FormattingEnabled = true;
            this.listBoxBoundary.Location = new System.Drawing.Point(12, 25);
            this.listBoxBoundary.Name = "listBoxBoundary";
            this.listBoxBoundary.Size = new System.Drawing.Size(156, 186);
            this.listBoxBoundary.TabIndex = 0;
            this.listBoxBoundary.DoubleClick += new System.EventHandler(this.listBoxBoundary_DoubleClick);
            // 
            // contextMenuStrip
            // 
            this.contextMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.deleteToolStripMenuItem});
            this.contextMenuStrip.Name = "contextMenuStrip1";
            this.contextMenuStrip.Size = new System.Drawing.Size(117, 26);
            // 
            // deleteToolStripMenuItem
            // 
            this.deleteToolStripMenuItem.Name = "deleteToolStripMenuItem";
            this.deleteToolStripMenuItem.Size = new System.Drawing.Size(116, 22);
            this.deleteToolStripMenuItem.Text = "Delete";
            this.deleteToolStripMenuItem.Click += new System.EventHandler(this.deleteToolStripMenuItem_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(71, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Boundary List";
            // 
            // butSave
            // 
            this.butSave.Location = new System.Drawing.Point(19, 217);
            this.butSave.Name = "butSave";
            this.butSave.Size = new System.Drawing.Size(43, 23);
            this.butSave.TabIndex = 2;
            this.butSave.Text = "Save";
            this.butSave.UseVisualStyleBackColor = true;
            this.butSave.Click += new System.EventHandler(this.butSave_Click);
            // 
            // butClear
            // 
            this.butClear.Location = new System.Drawing.Point(68, 217);
            this.butClear.Name = "butClear";
            this.butClear.Size = new System.Drawing.Size(43, 23);
            this.butClear.TabIndex = 3;
            this.butClear.Text = "Clear";
            this.butClear.UseVisualStyleBackColor = true;
            this.butClear.Click += new System.EventHandler(this.butClear_Click);
            // 
            // butNew
            // 
            this.butNew.Location = new System.Drawing.Point(117, 217);
            this.butNew.Name = "butNew";
            this.butNew.Size = new System.Drawing.Size(43, 23);
            this.butNew.TabIndex = 4;
            this.butNew.Text = "New";
            this.butNew.UseVisualStyleBackColor = true;
            this.butNew.Click += new System.EventHandler(this.butNew_Click);
            // 
            // BoundaryForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(179, 253);
            this.ControlBox = false;
            this.Controls.Add(this.butNew);
            this.Controls.Add(this.butSave);
            this.Controls.Add(this.butClear);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.listBoxBoundary);
            this.Name = "BoundaryForm";
            this.Text = "Boundary List";
            this.contextMenuStrip.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox listBoxBoundary;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button butSave;
        private System.Windows.Forms.Button butClear;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem deleteToolStripMenuItem;
        private System.Windows.Forms.Button butNew;
    }
}