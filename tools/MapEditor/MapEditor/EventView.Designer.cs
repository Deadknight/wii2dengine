namespace MapEditor
{
    partial class EventView
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
            this.lstBoxEvents = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // lstBoxEvents
            // 
            this.lstBoxEvents.FormattingEnabled = true;
            this.lstBoxEvents.Location = new System.Drawing.Point(12, 12);
            this.lstBoxEvents.Name = "lstBoxEvents";
            this.lstBoxEvents.Size = new System.Drawing.Size(260, 368);
            this.lstBoxEvents.TabIndex = 3;
            this.lstBoxEvents.MouseDown += new System.Windows.Forms.MouseEventHandler(this.lstBoxEvents_MouseDown);
            // 
            // EventView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 388);
            this.Controls.Add(this.lstBoxEvents);
            this.Name = "EventView";
            this.Text = "EventView";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox lstBoxEvents;
    }
}