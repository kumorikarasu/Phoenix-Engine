namespace HitBox_Editor
{
    partial class HitBoxEditor
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
          System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(HitBoxEditor));
          this.menuStrip1 = new System.Windows.Forms.MenuStrip();
          this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
          this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
          this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
          this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
          this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
          this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
          this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
          this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
          this.toolStrip1 = new System.Windows.Forms.ToolStrip();
          this.New = new System.Windows.Forms.ToolStripButton();
          this.Open = new System.Windows.Forms.ToolStripButton();
          this.Save = new System.Windows.Forms.ToolStripButton();
          this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
          this.PrevFrame = new System.Windows.Forms.ToolStripButton();
          this.NextFrame = new System.Windows.Forms.ToolStripButton();
          this.toolStripTextBox1 = new System.Windows.Forms.ToolStripTextBox();
          this.JumpTo = new System.Windows.Forms.ToolStripButton();
          this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
          this.Grid = new System.Windows.Forms.ToolStripButton();
          this.ToggleAttack = new System.Windows.Forms.ToolStripButton();
          this.ToggleHitbox = new System.Windows.Forms.ToolStripButton();
          this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
          this.MoveTool = new System.Windows.Forms.ToolStripButton();
          this.statusStrip1 = new System.Windows.Forms.StatusStrip();
          this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
          this.splitContainer1 = new System.Windows.Forms.SplitContainer();
          this.propertyGrid1 = new System.Windows.Forms.PropertyGrid();
          this.panel1 = new System.Windows.Forms.Panel();
          this.menuStrip1.SuspendLayout();
          this.toolStrip1.SuspendLayout();
          this.statusStrip1.SuspendLayout();
          ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
          this.splitContainer1.Panel1.SuspendLayout();
          this.splitContainer1.Panel2.SuspendLayout();
          this.splitContainer1.SuspendLayout();
          this.SuspendLayout();
          // 
          // menuStrip1
          // 
          this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.helpToolStripMenuItem});
          this.menuStrip1.Location = new System.Drawing.Point(0, 0);
          this.menuStrip1.Name = "menuStrip1";
          this.menuStrip1.Size = new System.Drawing.Size(963, 24);
          this.menuStrip1.TabIndex = 0;
          this.menuStrip1.Text = "menuStrip1";
          // 
          // fileToolStripMenuItem
          // 
          this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.saveAsToolStripMenuItem,
            this.exitToolStripMenuItem});
          this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
          this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
          this.fileToolStripMenuItem.Text = "File";
          // 
          // newToolStripMenuItem
          // 
          this.newToolStripMenuItem.Name = "newToolStripMenuItem";
          this.newToolStripMenuItem.Size = new System.Drawing.Size(123, 22);
          this.newToolStripMenuItem.Text = "&New";
          // 
          // openToolStripMenuItem
          // 
          this.openToolStripMenuItem.Name = "openToolStripMenuItem";
          this.openToolStripMenuItem.Size = new System.Drawing.Size(123, 22);
          this.openToolStripMenuItem.Text = "&Open";
          // 
          // saveToolStripMenuItem
          // 
          this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
          this.saveToolStripMenuItem.Size = new System.Drawing.Size(123, 22);
          this.saveToolStripMenuItem.Text = "&Save";
          // 
          // saveAsToolStripMenuItem
          // 
          this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
          this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(123, 22);
          this.saveAsToolStripMenuItem.Text = "Save &As...";
          // 
          // exitToolStripMenuItem
          // 
          this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
          this.exitToolStripMenuItem.Size = new System.Drawing.Size(123, 22);
          this.exitToolStripMenuItem.Text = "E&xit";
          this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
          // 
          // helpToolStripMenuItem
          // 
          this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem});
          this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
          this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
          this.helpToolStripMenuItem.Text = "Help";
          // 
          // aboutToolStripMenuItem
          // 
          this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
          this.aboutToolStripMenuItem.Size = new System.Drawing.Size(107, 22);
          this.aboutToolStripMenuItem.Text = "&About";
          this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
          // 
          // toolStrip1
          // 
          this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.New,
            this.Open,
            this.Save,
            this.toolStripSeparator2,
            this.PrevFrame,
            this.NextFrame,
            this.toolStripTextBox1,
            this.JumpTo,
            this.toolStripSeparator1,
            this.Grid,
            this.ToggleAttack,
            this.ToggleHitbox,
            this.toolStripSeparator3,
            this.MoveTool});
          this.toolStrip1.Location = new System.Drawing.Point(0, 24);
          this.toolStrip1.Name = "toolStrip1";
          this.toolStrip1.Size = new System.Drawing.Size(963, 25);
          this.toolStrip1.TabIndex = 2;
          this.toolStrip1.Text = "toolStrip1";
          // 
          // New
          // 
          this.New.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
          this.New.Image = ((System.Drawing.Image)(resources.GetObject("New.Image")));
          this.New.ImageTransparentColor = System.Drawing.Color.Magenta;
          this.New.Name = "New";
          this.New.Size = new System.Drawing.Size(23, 22);
          this.New.Text = "New";
          // 
          // Open
          // 
          this.Open.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
          this.Open.Image = ((System.Drawing.Image)(resources.GetObject("Open.Image")));
          this.Open.ImageTransparentColor = System.Drawing.Color.Magenta;
          this.Open.Name = "Open";
          this.Open.Size = new System.Drawing.Size(23, 22);
          this.Open.Text = "Open";
          // 
          // Save
          // 
          this.Save.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
          this.Save.Image = ((System.Drawing.Image)(resources.GetObject("Save.Image")));
          this.Save.ImageTransparentColor = System.Drawing.Color.Magenta;
          this.Save.Name = "Save";
          this.Save.Size = new System.Drawing.Size(23, 22);
          this.Save.Text = "Save";
          // 
          // toolStripSeparator2
          // 
          this.toolStripSeparator2.Name = "toolStripSeparator2";
          this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
          // 
          // PrevFrame
          // 
          this.PrevFrame.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
          this.PrevFrame.Image = ((System.Drawing.Image)(resources.GetObject("PrevFrame.Image")));
          this.PrevFrame.ImageTransparentColor = System.Drawing.Color.Magenta;
          this.PrevFrame.Name = "PrevFrame";
          this.PrevFrame.Size = new System.Drawing.Size(23, 22);
          this.PrevFrame.Text = "Previous Frame";
          // 
          // NextFrame
          // 
          this.NextFrame.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
          this.NextFrame.Image = ((System.Drawing.Image)(resources.GetObject("NextFrame.Image")));
          this.NextFrame.ImageTransparentColor = System.Drawing.Color.Magenta;
          this.NextFrame.Name = "NextFrame";
          this.NextFrame.Size = new System.Drawing.Size(23, 22);
          this.NextFrame.Text = "Next Frame";
          // 
          // toolStripTextBox1
          // 
          this.toolStripTextBox1.MaxLength = 5;
          this.toolStripTextBox1.Name = "toolStripTextBox1";
          this.toolStripTextBox1.Size = new System.Drawing.Size(30, 25);
          this.toolStripTextBox1.Text = "0";
          this.toolStripTextBox1.ToolTipText = "Jump To Frame";
          // 
          // JumpTo
          // 
          this.JumpTo.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
          this.JumpTo.Image = ((System.Drawing.Image)(resources.GetObject("JumpTo.Image")));
          this.JumpTo.ImageTransparentColor = System.Drawing.Color.Magenta;
          this.JumpTo.Name = "JumpTo";
          this.JumpTo.Size = new System.Drawing.Size(23, 22);
          this.JumpTo.Text = "toolStripButton1";
          this.JumpTo.ToolTipText = "Jump To Frame";
          // 
          // toolStripSeparator1
          // 
          this.toolStripSeparator1.Name = "toolStripSeparator1";
          this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
          // 
          // Grid
          // 
          this.Grid.Checked = true;
          this.Grid.CheckOnClick = true;
          this.Grid.CheckState = System.Windows.Forms.CheckState.Checked;
          this.Grid.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
          this.Grid.Image = ((System.Drawing.Image)(resources.GetObject("Grid.Image")));
          this.Grid.ImageTransparentColor = System.Drawing.Color.Magenta;
          this.Grid.Name = "Grid";
          this.Grid.Size = new System.Drawing.Size(23, 22);
          this.Grid.Text = "Toggle Grid";
          this.Grid.Click += new System.EventHandler(this.Grid_Click);
          // 
          // ToggleAttack
          // 
          this.ToggleAttack.Checked = true;
          this.ToggleAttack.CheckOnClick = true;
          this.ToggleAttack.CheckState = System.Windows.Forms.CheckState.Checked;
          this.ToggleAttack.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
          this.ToggleAttack.Image = ((System.Drawing.Image)(resources.GetObject("ToggleAttack.Image")));
          this.ToggleAttack.ImageTransparentColor = System.Drawing.Color.Magenta;
          this.ToggleAttack.Name = "ToggleAttack";
          this.ToggleAttack.Size = new System.Drawing.Size(23, 22);
          this.ToggleAttack.Text = "Toggle Attack Hitbox Display";
          // 
          // ToggleHitbox
          // 
          this.ToggleHitbox.Checked = true;
          this.ToggleHitbox.CheckOnClick = true;
          this.ToggleHitbox.CheckState = System.Windows.Forms.CheckState.Checked;
          this.ToggleHitbox.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
          this.ToggleHitbox.Image = ((System.Drawing.Image)(resources.GetObject("ToggleHitbox.Image")));
          this.ToggleHitbox.ImageTransparentColor = System.Drawing.Color.Magenta;
          this.ToggleHitbox.Name = "ToggleHitbox";
          this.ToggleHitbox.Size = new System.Drawing.Size(23, 22);
          this.ToggleHitbox.Text = "Toggle Hitbox Display";
          // 
          // toolStripSeparator3
          // 
          this.toolStripSeparator3.Name = "toolStripSeparator3";
          this.toolStripSeparator3.Size = new System.Drawing.Size(6, 25);
          // 
          // MoveTool
          // 
          this.MoveTool.CheckOnClick = true;
          this.MoveTool.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
          this.MoveTool.Image = ((System.Drawing.Image)(resources.GetObject("MoveTool.Image")));
          this.MoveTool.ImageTransparentColor = System.Drawing.Color.White;
          this.MoveTool.Name = "MoveTool";
          this.MoveTool.Size = new System.Drawing.Size(23, 22);
          this.MoveTool.Text = "Move Tool";
          this.MoveTool.Click += new System.EventHandler(this.MoveTool_Click);
          // 
          // statusStrip1
          // 
          this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
          this.statusStrip1.Location = new System.Drawing.Point(0, 671);
          this.statusStrip1.Name = "statusStrip1";
          this.statusStrip1.Size = new System.Drawing.Size(963, 22);
          this.statusStrip1.TabIndex = 3;
          this.statusStrip1.Text = "statusStrip1";
          // 
          // toolStripStatusLabel1
          // 
          this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
          this.toolStripStatusLabel1.Size = new System.Drawing.Size(95, 17);
          this.toolStripStatusLabel1.Text = "Frame X out of Y";
          // 
          // splitContainer1
          // 
          this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
          this.splitContainer1.Location = new System.Drawing.Point(0, 49);
          this.splitContainer1.Name = "splitContainer1";
          // 
          // splitContainer1.Panel1
          // 
          this.splitContainer1.Panel1.Controls.Add(this.propertyGrid1);
          // 
          // splitContainer1.Panel2
          // 
          this.splitContainer1.Panel2.Controls.Add(this.panel1);
          this.splitContainer1.Size = new System.Drawing.Size(963, 622);
          this.splitContainer1.SplitterDistance = 252;
          this.splitContainer1.TabIndex = 4;
          // 
          // propertyGrid1
          // 
          this.propertyGrid1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                      | System.Windows.Forms.AnchorStyles.Left)
                      | System.Windows.Forms.AnchorStyles.Right)));
          this.propertyGrid1.Location = new System.Drawing.Point(3, 3);
          this.propertyGrid1.Name = "propertyGrid1";
          this.propertyGrid1.Size = new System.Drawing.Size(246, 619);
          this.propertyGrid1.TabIndex = 0;
          // 
          // panel1
          // 
          this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                      | System.Windows.Forms.AnchorStyles.Left)
                      | System.Windows.Forms.AnchorStyles.Right)));
          this.panel1.BackColor = System.Drawing.SystemColors.WindowText;
          this.panel1.Location = new System.Drawing.Point(3, 3);
          this.panel1.Name = "panel1";
          this.panel1.Size = new System.Drawing.Size(701, 619);
          this.panel1.TabIndex = 2;
          this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint);
          this.panel1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseDown);
          this.panel1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseMove);
          this.panel1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseUp);
          // 
          // HitBoxEditor
          // 
          this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
          this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
          this.ClientSize = new System.Drawing.Size(963, 693);
          this.Controls.Add(this.splitContainer1);
          this.Controls.Add(this.statusStrip1);
          this.Controls.Add(this.toolStrip1);
          this.Controls.Add(this.menuStrip1);
          this.MainMenuStrip = this.menuStrip1;
          this.Name = "HitBoxEditor";
          this.Text = "HitBox Editor";
          this.Load += new System.EventHandler(this.Form1_Load);
          this.Resize += new System.EventHandler(this.HitBoxEditor_Resize);
          this.menuStrip1.ResumeLayout(false);
          this.menuStrip1.PerformLayout();
          this.toolStrip1.ResumeLayout(false);
          this.toolStrip1.PerformLayout();
          this.statusStrip1.ResumeLayout(false);
          this.statusStrip1.PerformLayout();
          this.splitContainer1.Panel1.ResumeLayout(false);
          this.splitContainer1.Panel2.ResumeLayout(false);
          ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
          this.splitContainer1.ResumeLayout(false);
          this.ResumeLayout(false);
          this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton PrevFrame;
        private System.Windows.Forms.ToolStripButton NextFrame;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox1;
        private System.Windows.Forms.ToolStripButton JumpTo;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripButton Grid;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton New;
        private System.Windows.Forms.ToolStripButton Save;
        private System.Windows.Forms.ToolStripButton Open;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton ToggleAttack;
        private System.Windows.Forms.ToolStripButton ToggleHitbox;
        private System.Windows.Forms.ToolStripButton MoveTool;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.PropertyGrid propertyGrid1;
    }
}

