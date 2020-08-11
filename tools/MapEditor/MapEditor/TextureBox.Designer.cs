namespace MapEditor
{
    partial class TextureBox
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
            this.pictBoxTexture = new System.Windows.Forms.PictureBox();
            this.trackBarFrame = new System.Windows.Forms.TrackBar();
            ((System.ComponentModel.ISupportInitialize)(this.pictBoxTexture)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarFrame)).BeginInit();
            this.SuspendLayout();
            // 
            // pictBoxTexture
            // 
            this.pictBoxTexture.Location = new System.Drawing.Point(0, 1);
            this.pictBoxTexture.Name = "pictBoxTexture";
            this.pictBoxTexture.Size = new System.Drawing.Size(257, 205);
            this.pictBoxTexture.TabIndex = 0;
            this.pictBoxTexture.TabStop = false;
            // 
            // trackBarFrame
            // 
            this.trackBarFrame.Location = new System.Drawing.Point(12, 212);
            this.trackBarFrame.Name = "trackBarFrame";
            this.trackBarFrame.Size = new System.Drawing.Size(218, 42);
            this.trackBarFrame.TabIndex = 1;
            // 
            // TextureBox
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(257, 249);
            this.Controls.Add(this.trackBarFrame);
            this.Controls.Add(this.pictBoxTexture);
            this.MaximumSize = new System.Drawing.Size(265, 276);
            this.MinimumSize = new System.Drawing.Size(265, 276);
            this.Name = "TextureBox";
            this.Text = "TextureBox";
            this.Load += new System.EventHandler(this.TextureBox_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictBoxTexture)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarFrame)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictBoxTexture;
        private System.Windows.Forms.TrackBar trackBarFrame;
    }
}