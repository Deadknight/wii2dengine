namespace MapEditor
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Main));
            this.pictBoxRender = new System.Windows.Forms.PictureBox();
            this.thumbnail = new System.Windows.Forms.PictureBox();
            this.listBoxSurface = new System.Windows.Forms.ListBox();
            this.contextMenuStripSurface = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.deleteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenuStripSO = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.deleteToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.txtX = new System.Windows.Forms.TextBox();
            this.txtY = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.txtSY = new System.Windows.Forms.TextBox();
            this.txtSX = new System.Windows.Forms.TextBox();
            this.tBarFrame = new System.Windows.Forms.TrackBar();
            this.butSave = new System.Windows.Forms.Button();
            this.toolStrip = new System.Windows.Forms.ToolStrip();
            this.toolStripButOpen = new System.Windows.Forms.ToolStripButton();
            this.toolStripButSave = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripDropDownButton();
            this.imageViewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.soundViewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.eventViewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripButStaticObject = new System.Windows.Forms.ToolStripButton();
            this.toolStripButDrawBoundary = new System.Windows.Forms.ToolStripButton();
            this.toolStripButDrawObjectBoundary = new System.Windows.Forms.ToolStripButton();
            this.toolStripButMoveSurface = new System.Windows.Forms.ToolStripButton();
            this.toolStripButMoveStatic = new System.Windows.Forms.ToolStripButton();
            this.toolStripButDrawStandalonePhysicObject = new System.Windows.Forms.ToolStripButton();
            this.toolStripButDisplayPhysics = new System.Windows.Forms.ToolStripButton();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.progressBarStatus = new System.Windows.Forms.ProgressBar();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.butUnselect = new System.Windows.Forms.Button();
            this.chkBoxAnimated = new System.Windows.Forms.CheckBox();
            this.pGrid = new System.Windows.Forms.PropertyGrid();
            this.cBoxType = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.txtVY = new System.Windows.Forms.TextBox();
            this.txtVX = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.txtRot = new System.Windows.Forms.TextBox();
            this.contextMenuStripPO = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.deleteToolStripMenuItemPO = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabX = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabY = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabelRelPath = new System.Windows.Forms.ToolStripStatusLabel();
            this.listBoxPO = new MapEditor.RListBox();
            this.listBoxSO = new MapEditor.RListBox();
            this.folderBrowserDialogRelative = new System.Windows.Forms.FolderBrowserDialog();
            this.butRelPath = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictBoxRender)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.thumbnail)).BeginInit();
            this.contextMenuStripSurface.SuspendLayout();
            this.contextMenuStripSO.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.tBarFrame)).BeginInit();
            this.toolStrip.SuspendLayout();
            this.contextMenuStripPO.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictBoxRender
            // 
            this.pictBoxRender.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pictBoxRender.Location = new System.Drawing.Point(0, 28);
            this.pictBoxRender.Name = "pictBoxRender";
            this.pictBoxRender.Size = new System.Drawing.Size(640, 480);
            this.pictBoxRender.TabIndex = 0;
            this.pictBoxRender.TabStop = false;
            this.pictBoxRender.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictBoxRender_MouseMove);
            this.pictBoxRender.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictBoxRender_MouseDown);
            this.pictBoxRender.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictBoxRender_MouseUp);
            // 
            // thumbnail
            // 
            this.thumbnail.Location = new System.Drawing.Point(12, 33);
            this.thumbnail.Name = "thumbnail";
            this.thumbnail.Size = new System.Drawing.Size(100, 50);
            this.thumbnail.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.thumbnail.TabIndex = 1;
            this.thumbnail.TabStop = false;
            // 
            // listBoxSurface
            // 
            this.listBoxSurface.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.listBoxSurface.ContextMenuStrip = this.contextMenuStripSurface;
            this.listBoxSurface.FormattingEnabled = true;
            this.listBoxSurface.Location = new System.Drawing.Point(646, 49);
            this.listBoxSurface.Name = "listBoxSurface";
            this.listBoxSurface.Size = new System.Drawing.Size(326, 212);
            this.listBoxSurface.TabIndex = 2;
            this.listBoxSurface.TabStop = false;
            this.listBoxSurface.SelectedIndexChanged += new System.EventHandler(this.listBoxSurface_SelectedIndexChanged);
            // 
            // contextMenuStripSurface
            // 
            this.contextMenuStripSurface.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.deleteToolStripMenuItem});
            this.contextMenuStripSurface.Name = "contextMenuStripSurface";
            this.contextMenuStripSurface.Size = new System.Drawing.Size(108, 26);
            // 
            // deleteToolStripMenuItem
            // 
            this.deleteToolStripMenuItem.Name = "deleteToolStripMenuItem";
            this.deleteToolStripMenuItem.Size = new System.Drawing.Size(107, 22);
            this.deleteToolStripMenuItem.Text = "Delete";
            this.deleteToolStripMenuItem.Click += new System.EventHandler(this.deleteToolStripMenuItem_Click);
            // 
            // contextMenuStripSO
            // 
            this.contextMenuStripSO.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.deleteToolStripMenuItem1});
            this.contextMenuStripSO.Name = "contextMenuStripSO";
            this.contextMenuStripSO.Size = new System.Drawing.Size(108, 26);
            // 
            // deleteToolStripMenuItem1
            // 
            this.deleteToolStripMenuItem1.Name = "deleteToolStripMenuItem1";
            this.deleteToolStripMenuItem1.Size = new System.Drawing.Size(107, 22);
            this.deleteToolStripMenuItem1.Text = "Delete";
            this.deleteToolStripMenuItem1.Click += new System.EventHandler(this.deleteToolStripMenuItem1_Click);
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(646, 33);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(49, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Surfaces";
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(643, 264);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(73, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Static Objects";
            // 
            // txtX
            // 
            this.txtX.Location = new System.Drawing.Point(24, 549);
            this.txtX.Name = "txtX";
            this.txtX.Size = new System.Drawing.Size(45, 20);
            this.txtX.TabIndex = 6;
            this.txtX.TextChanged += new System.EventHandler(this.txtX_TextChanged);
            // 
            // txtY
            // 
            this.txtY.Location = new System.Drawing.Point(104, 549);
            this.txtY.Name = "txtY";
            this.txtY.Size = new System.Drawing.Size(46, 20);
            this.txtY.TabIndex = 7;
            this.txtY.TextChanged += new System.EventHandler(this.txtY_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(4, 552);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(14, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "X";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(84, 552);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(14, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "Y";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(87, 578);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(34, 13);
            this.label5.TabIndex = 13;
            this.label5.Text = "SizeY";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(5, 578);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(34, 13);
            this.label6.TabIndex = 12;
            this.label6.Text = "SizeX";
            // 
            // txtSY
            // 
            this.txtSY.Location = new System.Drawing.Point(127, 575);
            this.txtSY.Name = "txtSY";
            this.txtSY.Size = new System.Drawing.Size(36, 20);
            this.txtSY.TabIndex = 11;
            this.txtSY.TextChanged += new System.EventHandler(this.txtSY_TextChanged);
            // 
            // txtSX
            // 
            this.txtSX.Location = new System.Drawing.Point(46, 575);
            this.txtSX.Name = "txtSX";
            this.txtSX.Size = new System.Drawing.Size(36, 20);
            this.txtSX.TabIndex = 10;
            this.txtSX.TextChanged += new System.EventHandler(this.txtSX_TextChanged);
            // 
            // tBarFrame
            // 
            this.tBarFrame.Location = new System.Drawing.Point(178, 578);
            this.tBarFrame.Name = "tBarFrame";
            this.tBarFrame.Size = new System.Drawing.Size(130, 45);
            this.tBarFrame.TabIndex = 14;
            this.tBarFrame.ValueChanged += new System.EventHandler(this.tBarFrame_ValueChanged);
            // 
            // butSave
            // 
            this.butSave.Location = new System.Drawing.Point(12, 677);
            this.butSave.Name = "butSave";
            this.butSave.Size = new System.Drawing.Size(75, 23);
            this.butSave.TabIndex = 15;
            this.butSave.Text = "Save";
            this.butSave.UseVisualStyleBackColor = true;
            this.butSave.Click += new System.EventHandler(this.butSave_Click);
            // 
            // toolStrip
            // 
            this.toolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButOpen,
            this.toolStripButSave,
            this.toolStripButton1,
            this.toolStripButStaticObject,
            this.toolStripButDrawBoundary,
            this.toolStripButDrawObjectBoundary,
            this.toolStripButMoveSurface,
            this.toolStripButMoveStatic,
            this.toolStripButDrawStandalonePhysicObject,
            this.toolStripButDisplayPhysics});
            this.toolStrip.Location = new System.Drawing.Point(0, 0);
            this.toolStrip.Name = "toolStrip";
            this.toolStrip.Size = new System.Drawing.Size(975, 25);
            this.toolStrip.TabIndex = 16;
            this.toolStrip.Text = "toolStrip1";
            // 
            // toolStripButOpen
            // 
            this.toolStripButOpen.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButOpen.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButOpen.Image")));
            this.toolStripButOpen.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButOpen.Name = "toolStripButOpen";
            this.toolStripButOpen.Size = new System.Drawing.Size(40, 22);
            this.toolStripButOpen.Text = "Open";
            this.toolStripButOpen.Click += new System.EventHandler(this.toolStripButOpen_Click);
            // 
            // toolStripButSave
            // 
            this.toolStripButSave.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButSave.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButSave.Image")));
            this.toolStripButSave.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButSave.Name = "toolStripButSave";
            this.toolStripButSave.Size = new System.Drawing.Size(35, 22);
            this.toolStripButSave.Text = "Save";
            this.toolStripButSave.Click += new System.EventHandler(this.toolStripButSave_Click);
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButton1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.imageViewToolStripMenuItem,
            this.soundViewToolStripMenuItem,
            this.eventViewToolStripMenuItem});
            this.toolStripButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton1.Image")));
            this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(45, 22);
            this.toolStripButton1.Text = "View";
            // 
            // imageViewToolStripMenuItem
            // 
            this.imageViewToolStripMenuItem.Name = "imageViewToolStripMenuItem";
            this.imageViewToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.imageViewToolStripMenuItem.Text = "Image View";
            this.imageViewToolStripMenuItem.Click += new System.EventHandler(this.imageViewToolStripMenuItem_Click);
            // 
            // soundViewToolStripMenuItem
            // 
            this.soundViewToolStripMenuItem.Name = "soundViewToolStripMenuItem";
            this.soundViewToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.soundViewToolStripMenuItem.Text = "Sound View";
            this.soundViewToolStripMenuItem.Click += new System.EventHandler(this.soundViewToolStripMenuItem_Click);
            // 
            // eventViewToolStripMenuItem
            // 
            this.eventViewToolStripMenuItem.Name = "eventViewToolStripMenuItem";
            this.eventViewToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.eventViewToolStripMenuItem.Text = "Event View";
            this.eventViewToolStripMenuItem.Click += new System.EventHandler(this.eventViewToolStripMenuItem_Click);
            // 
            // toolStripButStaticObject
            // 
            this.toolStripButStaticObject.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButStaticObject.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButStaticObject.Image")));
            this.toolStripButStaticObject.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButStaticObject.Name = "toolStripButStaticObject";
            this.toolStripButStaticObject.Size = new System.Drawing.Size(78, 22);
            this.toolStripButStaticObject.Text = "Static Object";
            this.toolStripButStaticObject.ToolTipText = "Static Object";
            this.toolStripButStaticObject.Click += new System.EventHandler(this.toolStripButStaticObject_Click);
            // 
            // toolStripButDrawBoundary
            // 
            this.toolStripButDrawBoundary.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButDrawBoundary.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButDrawBoundary.Image")));
            this.toolStripButDrawBoundary.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButDrawBoundary.Name = "toolStripButDrawBoundary";
            this.toolStripButDrawBoundary.Size = new System.Drawing.Size(92, 22);
            this.toolStripButDrawBoundary.Text = "Draw Boundary";
            this.toolStripButDrawBoundary.Click += new System.EventHandler(this.toolStripButDrawBoundary_Click);
            // 
            // toolStripButDrawObjectBoundary
            // 
            this.toolStripButDrawObjectBoundary.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButDrawObjectBoundary.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButDrawObjectBoundary.Image")));
            this.toolStripButDrawObjectBoundary.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButDrawObjectBoundary.Name = "toolStripButDrawObjectBoundary";
            this.toolStripButDrawObjectBoundary.Size = new System.Drawing.Size(130, 22);
            this.toolStripButDrawObjectBoundary.Text = "Draw Object Boundary";
            this.toolStripButDrawObjectBoundary.Click += new System.EventHandler(this.toolStripButDrawObjectBoundary_Click);
            // 
            // toolStripButMoveSurface
            // 
            this.toolStripButMoveSurface.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButMoveSurface.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButMoveSurface.Image")));
            this.toolStripButMoveSurface.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButMoveSurface.Name = "toolStripButMoveSurface";
            this.toolStripButMoveSurface.Size = new System.Drawing.Size(73, 22);
            this.toolStripButMoveSurface.Text = "Edit Surface";
            this.toolStripButMoveSurface.Click += new System.EventHandler(this.toolStripButMoveSurface_Click);
            // 
            // toolStripButMoveStatic
            // 
            this.toolStripButMoveStatic.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButMoveStatic.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButMoveStatic.Image")));
            this.toolStripButMoveStatic.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButMoveStatic.Name = "toolStripButMoveStatic";
            this.toolStripButMoveStatic.Size = new System.Drawing.Size(63, 22);
            this.toolStripButMoveStatic.Text = "Edit Static";
            this.toolStripButMoveStatic.Click += new System.EventHandler(this.toolStripButMoveStatic_Click);
            // 
            // toolStripButDrawStandalonePhysicObject
            // 
            this.toolStripButDrawStandalonePhysicObject.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButDrawStandalonePhysicObject.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButDrawStandalonePhysicObject.Image")));
            this.toolStripButDrawStandalonePhysicObject.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButDrawStandalonePhysicObject.Name = "toolStripButDrawStandalonePhysicObject";
            this.toolStripButDrawStandalonePhysicObject.Size = new System.Drawing.Size(175, 22);
            this.toolStripButDrawStandalonePhysicObject.Text = "Draw Standalone Physic Object";
            this.toolStripButDrawStandalonePhysicObject.Click += new System.EventHandler(this.toolStripButDrawStandalonePhysicObject_Click);
            // 
            // toolStripButDisplayPhysics
            // 
            this.toolStripButDisplayPhysics.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButDisplayPhysics.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButDisplayPhysics.Image")));
            this.toolStripButDisplayPhysics.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButDisplayPhysics.Name = "toolStripButDisplayPhysics";
            this.toolStripButDisplayPhysics.Size = new System.Drawing.Size(91, 22);
            this.toolStripButDisplayPhysics.Text = "Display Physics";
            this.toolStripButDisplayPhysics.Click += new System.EventHandler(this.toolStripButDisplayPhysics_Click);
            // 
            // saveFileDialog
            // 
            this.saveFileDialog.Filter = "Map files|*.map";
            // 
            // progressBarStatus
            // 
            this.progressBarStatus.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.progressBarStatus.Location = new System.Drawing.Point(872, 28);
            this.progressBarStatus.Name = "progressBarStatus";
            this.progressBarStatus.Size = new System.Drawing.Size(100, 18);
            this.progressBarStatus.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBarStatus.TabIndex = 17;
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "Map files|*.map";
            // 
            // butUnselect
            // 
            this.butUnselect.Location = new System.Drawing.Point(89, 677);
            this.butUnselect.Name = "butUnselect";
            this.butUnselect.Size = new System.Drawing.Size(75, 23);
            this.butUnselect.TabIndex = 18;
            this.butUnselect.Text = "Unselect";
            this.butUnselect.UseVisualStyleBackColor = true;
            this.butUnselect.Click += new System.EventHandler(this.butUnselect_Click);
            // 
            // chkBoxAnimated
            // 
            this.chkBoxAnimated.AutoSize = true;
            this.chkBoxAnimated.Location = new System.Drawing.Point(187, 610);
            this.chkBoxAnimated.Name = "chkBoxAnimated";
            this.chkBoxAnimated.Size = new System.Drawing.Size(15, 14);
            this.chkBoxAnimated.TabIndex = 19;
            this.chkBoxAnimated.UseVisualStyleBackColor = true;
            // 
            // pGrid
            // 
            this.pGrid.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pGrid.Location = new System.Drawing.Point(314, 517);
            this.pGrid.Name = "pGrid";
            this.pGrid.Size = new System.Drawing.Size(326, 196);
            this.pGrid.TabIndex = 20;
            // 
            // cBoxType
            // 
            this.cBoxType.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.cBoxType.Enabled = false;
            this.cBoxType.FormattingEnabled = true;
            this.cBoxType.Location = new System.Drawing.Point(12, 607);
            this.cBoxType.Name = "cBoxType";
            this.cBoxType.Size = new System.Drawing.Size(121, 21);
            this.cBoxType.TabIndex = 21;
            this.cBoxType.SelectedIndexChanged += new System.EventHandler(this.cBoxType_SelectedIndexChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(118, 517);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(59, 13);
            this.label7.TabIndex = 25;
            this.label7.Text = "ViewPort Y";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(3, 517);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(58, 13);
            this.label8.TabIndex = 24;
            this.label8.Text = "Viewport X";
            // 
            // txtVY
            // 
            this.txtVY.Location = new System.Drawing.Point(182, 514);
            this.txtVY.Name = "txtVY";
            this.txtVY.Size = new System.Drawing.Size(46, 20);
            this.txtVY.TabIndex = 23;
            this.txtVY.TextChanged += new System.EventHandler(this.txtVY_TextChanged);
            // 
            // txtVX
            // 
            this.txtVX.Location = new System.Drawing.Point(67, 514);
            this.txtVX.Name = "txtVX";
            this.txtVX.Size = new System.Drawing.Size(45, 20);
            this.txtVX.TabIndex = 22;
            this.txtVX.TextChanged += new System.EventHandler(this.txtVX_TextChanged);
            // 
            // label9
            // 
            this.label9.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(643, 508);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(77, 13);
            this.label9.TabIndex = 27;
            this.label9.Text = "Physic Objects";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(168, 552);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(47, 13);
            this.label10.TabIndex = 29;
            this.label10.Text = "Rotation";
            // 
            // txtRot
            // 
            this.txtRot.Location = new System.Drawing.Point(221, 549);
            this.txtRot.Name = "txtRot";
            this.txtRot.Size = new System.Drawing.Size(36, 20);
            this.txtRot.TabIndex = 28;
            // 
            // contextMenuStripPO
            // 
            this.contextMenuStripPO.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.deleteToolStripMenuItemPO});
            this.contextMenuStripPO.Name = "contextMenuStripSO";
            this.contextMenuStripPO.Size = new System.Drawing.Size(108, 26);
            // 
            // deleteToolStripMenuItemPO
            // 
            this.deleteToolStripMenuItemPO.Name = "deleteToolStripMenuItemPO";
            this.deleteToolStripMenuItemPO.Size = new System.Drawing.Size(107, 22);
            this.deleteToolStripMenuItemPO.Text = "Delete";
            this.deleteToolStripMenuItemPO.Click += new System.EventHandler(this.deleteToolStripMenuItemPO_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabX,
            this.toolStripStatusLabel1,
            this.toolStripStatusLabY,
            this.toolStripStatusLabel2,
            this.toolStripStatusLabelRelPath});
            this.statusStrip1.Location = new System.Drawing.Point(0, 718);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(975, 22);
            this.statusStrip1.TabIndex = 30;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabX
            // 
            this.toolStripStatusLabX.Name = "toolStripStatusLabX";
            this.toolStripStatusLabX.Size = new System.Drawing.Size(14, 17);
            this.toolStripStatusLabX.Text = "X";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(10, 17);
            this.toolStripStatusLabel1.Text = ",";
            // 
            // toolStripStatusLabY
            // 
            this.toolStripStatusLabY.Name = "toolStripStatusLabY";
            this.toolStripStatusLabY.Size = new System.Drawing.Size(14, 17);
            this.toolStripStatusLabY.Text = "Y";
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(78, 17);
            this.toolStripStatusLabel2.Text = "Relative Path:";
            // 
            // toolStripStatusLabelRelPath
            // 
            this.toolStripStatusLabelRelPath.Name = "toolStripStatusLabelRelPath";
            this.toolStripStatusLabelRelPath.Size = new System.Drawing.Size(0, 17);
            // 
            // listBoxPO
            // 
            this.listBoxPO.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.listBoxPO.ContextMenuStrip = this.contextMenuStripPO;
            this.listBoxPO.FormattingEnabled = true;
            this.listBoxPO.Location = new System.Drawing.Point(646, 527);
            this.listBoxPO.Name = "listBoxPO";
            this.listBoxPO.Size = new System.Drawing.Size(326, 186);
            this.listBoxPO.TabIndex = 26;
            this.listBoxPO.TabStop = false;
            this.listBoxPO.SelectedIndexChanged += new System.EventHandler(this.listBoxPO_SelectedIndexChanged);
            // 
            // listBoxSO
            // 
            this.listBoxSO.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.listBoxSO.ContextMenuStrip = this.contextMenuStripSO;
            this.listBoxSO.FormattingEnabled = true;
            this.listBoxSO.Location = new System.Drawing.Point(646, 280);
            this.listBoxSO.Name = "listBoxSO";
            this.listBoxSO.Size = new System.Drawing.Size(326, 225);
            this.listBoxSO.TabIndex = 3;
            this.listBoxSO.TabStop = false;
            this.listBoxSO.SelectedIndexChanged += new System.EventHandler(this.listBoxSO_SelectedIndexChanged);
            // 
            // butRelPath
            // 
            this.butRelPath.Location = new System.Drawing.Point(171, 677);
            this.butRelPath.Name = "butRelPath";
            this.butRelPath.Size = new System.Drawing.Size(86, 23);
            this.butRelPath.TabIndex = 31;
            this.butRelPath.Text = "Relative Path";
            this.butRelPath.UseVisualStyleBackColor = true;
            this.butRelPath.Click += new System.EventHandler(this.butRelPath_Click);
            // 
            // Main
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(975, 740);
            this.Controls.Add(this.butRelPath);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.txtRot);
            this.Controls.Add(this.listBoxPO);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.txtVY);
            this.Controls.Add(this.txtVX);
            this.Controls.Add(this.progressBarStatus);
            this.Controls.Add(this.chkBoxAnimated);
            this.Controls.Add(this.pGrid);
            this.Controls.Add(this.toolStrip);
            this.Controls.Add(this.butUnselect);
            this.Controls.Add(this.listBoxSurface);
            this.Controls.Add(this.thumbnail);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.butSave);
            this.Controls.Add(this.pictBoxRender);
            this.Controls.Add(this.cBoxType);
            this.Controls.Add(this.tBarFrame);
            this.Controls.Add(this.listBoxSO);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.txtSY);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtSX);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txtY);
            this.Controls.Add(this.txtX);
            this.Name = "Main";
            this.Text = "Main";
            this.Load += new System.EventHandler(this.Main_Load);
            this.DragLeave += new System.EventHandler(this.Main_DragLeave);
            this.DragDrop += new System.Windows.Forms.DragEventHandler(this.Main_DragDrop);
            this.DragEnter += new System.Windows.Forms.DragEventHandler(this.Main_DragEnter);
            this.DragOver += new System.Windows.Forms.DragEventHandler(this.Main_DragOver);
            ((System.ComponentModel.ISupportInitialize)(this.pictBoxRender)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.thumbnail)).EndInit();
            this.contextMenuStripSurface.ResumeLayout(false);
            this.contextMenuStripSO.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.tBarFrame)).EndInit();
            this.toolStrip.ResumeLayout(false);
            this.toolStrip.PerformLayout();
            this.contextMenuStripPO.ResumeLayout(false);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictBoxRender;
        private System.Windows.Forms.PictureBox thumbnail;
        private System.Windows.Forms.ListBox listBoxSurface;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ContextMenuStrip contextMenuStripSurface;
        private System.Windows.Forms.ToolStripMenuItem deleteToolStripMenuItem;
        private System.Windows.Forms.ContextMenuStrip contextMenuStripSO;
        private System.Windows.Forms.ToolStripMenuItem deleteToolStripMenuItem1;
        private System.Windows.Forms.TextBox txtX;
        private System.Windows.Forms.TextBox txtY;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtSY;
        private System.Windows.Forms.TextBox txtSX;
        private System.Windows.Forms.TrackBar tBarFrame;
        private System.Windows.Forms.Button butSave;
        private System.Windows.Forms.ToolStrip toolStrip;
        private System.Windows.Forms.ToolStripButton toolStripButOpen;
        private System.Windows.Forms.ToolStripButton toolStripButSave;
        private System.Windows.Forms.ToolStripButton toolStripButStaticObject;
        private System.Windows.Forms.ToolStripButton toolStripButDrawBoundary;
        private System.Windows.Forms.ToolStripButton toolStripButDrawObjectBoundary;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.ProgressBar progressBarStatus;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.ToolStripButton toolStripButMoveSurface;
        private System.Windows.Forms.ToolStripButton toolStripButDisplayPhysics;
        private System.Windows.Forms.Button butUnselect;
        private System.Windows.Forms.CheckBox chkBoxAnimated;
        private System.Windows.Forms.PropertyGrid pGrid;
        private System.Windows.Forms.ComboBox cBoxType;
        private RListBox listBoxSO;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox txtVY;
        private System.Windows.Forms.TextBox txtVX;
        private System.Windows.Forms.ToolStripButton toolStripButMoveStatic;
        private RListBox listBoxPO;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.ToolStripButton toolStripButDrawStandalonePhysicObject;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox txtRot;
        private System.Windows.Forms.ContextMenuStrip contextMenuStripPO;
        private System.Windows.Forms.ToolStripMenuItem deleteToolStripMenuItemPO;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabY;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabX;
        private System.Windows.Forms.ToolStripDropDownButton toolStripButton1;
        private System.Windows.Forms.ToolStripMenuItem imageViewToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem soundViewToolStripMenuItem;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialogRelative;
        private System.Windows.Forms.Button butRelPath;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabelRelPath;
        private System.Windows.Forms.ToolStripMenuItem eventViewToolStripMenuItem;
    }
}

