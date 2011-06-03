namespace HitBox_Editor
{
  partial class Summary
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
      if (disposing && (components != null)) {
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
      this.SummaryList = new System.Windows.Forms.ListBox();
      this.SuspendLayout();
      // 
      // SummaryList
      // 
      this.SummaryList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                  | System.Windows.Forms.AnchorStyles.Left)
                  | System.Windows.Forms.AnchorStyles.Right)));
      this.SummaryList.FormattingEnabled = true;
      this.SummaryList.Location = new System.Drawing.Point(0, -1);
      this.SummaryList.Name = "SummaryList";
      this.SummaryList.Size = new System.Drawing.Size(287, 264);
      this.SummaryList.TabIndex = 0;
      // 
      // Summary
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(284, 262);
      this.Controls.Add(this.SummaryList);
      this.Name = "Summary";
      this.Text = "Summary";
      this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Summary_FormClosing);
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.ListBox SummaryList;


  }
}