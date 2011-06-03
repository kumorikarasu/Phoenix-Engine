namespace HitBox_Editor
{
  partial class PropertyWindow
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
      this.button1 = new System.Windows.Forms.Button();
      this.button2 = new System.Windows.Forms.Button();
      this.animation = new System.Windows.Forms.CheckBox();
      this.projectile = new System.Windows.Forms.CheckBox();
      this.label1 = new System.Windows.Forms.Label();
      this.ProjectileHits = new System.Windows.Forms.TextBox();
      this.SuspendLayout();
      // 
      // button1
      // 
      this.button1.Location = new System.Drawing.Point(195, 301);
      this.button1.Name = "button1";
      this.button1.Size = new System.Drawing.Size(75, 23);
      this.button1.TabIndex = 0;
      this.button1.Text = "Ok";
      this.button1.UseVisualStyleBackColor = true;
      // 
      // button2
      // 
      this.button2.Location = new System.Drawing.Point(114, 301);
      this.button2.Name = "button2";
      this.button2.Size = new System.Drawing.Size(75, 23);
      this.button2.TabIndex = 1;
      this.button2.Text = "Cancel";
      this.button2.UseVisualStyleBackColor = true;
      // 
      // animation
      // 
      this.animation.AutoSize = true;
      this.animation.Location = new System.Drawing.Point(13, 13);
      this.animation.Name = "animation";
      this.animation.Size = new System.Drawing.Size(72, 17);
      this.animation.TabIndex = 2;
      this.animation.Text = "Animation";
      this.animation.UseVisualStyleBackColor = true;
      // 
      // projectile
      // 
      this.projectile.AutoSize = true;
      this.projectile.Location = new System.Drawing.Point(13, 36);
      this.projectile.Name = "projectile";
      this.projectile.Size = new System.Drawing.Size(69, 17);
      this.projectile.TabIndex = 3;
      this.projectile.Text = "Projectile";
      this.projectile.UseVisualStyleBackColor = true;
      this.projectile.CheckedChanged += new System.EventHandler(this.projectile_CheckedChanged);
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(13, 60);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(80, 13);
      this.label1.TabIndex = 4;
      this.label1.Text = "Number of Hits:";
      // 
      // ProjectileHits
      // 
      this.ProjectileHits.Enabled = false;
      this.ProjectileHits.Location = new System.Drawing.Point(13, 76);
      this.ProjectileHits.Name = "ProjectileHits";
      this.ProjectileHits.Size = new System.Drawing.Size(100, 20);
      this.ProjectileHits.TabIndex = 5;
      // 
      // PropertyWindow
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(282, 336);
      this.Controls.Add(this.ProjectileHits);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.projectile);
      this.Controls.Add(this.animation);
      this.Controls.Add(this.button2);
      this.Controls.Add(this.button1);
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
      this.Name = "PropertyWindow";
      this.Text = "Properties";
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Button button1;
    private System.Windows.Forms.Button button2;
    private System.Windows.Forms.CheckBox animation;
    private System.Windows.Forms.CheckBox projectile;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.TextBox ProjectileHits;
  }
}