namespace HitBox_Editor
{
  partial class Film_Roll
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
      this.hScrollBar1 = new System.Windows.Forms.HScrollBar();
      this.panel2 = new System.Windows.Forms.Panel();
      this.hScrollBar2 = new System.Windows.Forms.HScrollBar();
      this.panel2.SuspendLayout();
      this.SuspendLayout();
      // 
      // hScrollBar1
      // 
      this.hScrollBar1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                  | System.Windows.Forms.AnchorStyles.Right)));
      this.hScrollBar1.Location = new System.Drawing.Point(9, 179);
      this.hScrollBar1.Name = "hScrollBar1";
      this.hScrollBar1.Size = new System.Drawing.Size(685, 17);
      this.hScrollBar1.TabIndex = 1;
      // 
      // panel2
      // 
      this.panel2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                  | System.Windows.Forms.AnchorStyles.Left)
                  | System.Windows.Forms.AnchorStyles.Right)));
      this.panel2.BackColor = System.Drawing.SystemColors.AppWorkspace;
      this.panel2.Controls.Add(this.hScrollBar2);
      this.panel2.Location = new System.Drawing.Point(0, 0);
      this.panel2.Name = "panel2";
      this.panel2.Size = new System.Drawing.Size(703, 202);
      this.panel2.TabIndex = 1;
      // 
      // hScrollBar2
      // 
      this.hScrollBar2.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
      this.hScrollBar2.Location = new System.Drawing.Point(0, 185);
      this.hScrollBar2.Name = "hScrollBar2";
      this.hScrollBar2.Size = new System.Drawing.Size(703, 17);
      this.hScrollBar2.TabIndex = 0;
      // 
      // Film_Roll
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(703, 202);
      this.Controls.Add(this.panel2);
      this.MaximizeBox = false;
      this.MaximumSize = new System.Drawing.Size(9999, 9999);
      this.MinimizeBox = false;
      this.MinimumSize = new System.Drawing.Size(16, 140);
      this.Name = "Film_Roll";
      this.Text = "Film Roll";
      this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Film_Roll_FormClosed);
      this.Load += new System.EventHandler(this.Film_Roll_Load);
      this.panel2.ResumeLayout(false);
      this.ResumeLayout(false);

    }

    #endregion

    private DoubleBufferPanel panel1;
    private System.Windows.Forms.HScrollBar hScrollBar1;
    private System.Windows.Forms.Panel panel2;
    private System.Windows.Forms.HScrollBar hScrollBar2;
  }
}