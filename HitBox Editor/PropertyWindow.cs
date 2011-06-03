using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace HitBox_Editor
{
  public partial class PropertyWindow : Form
  {
    public PropertyWindow()
    {
      InitializeComponent();
    }

    private void projectile_CheckedChanged(object sender, EventArgs e)
    {
      if (projectile.Checked){
        ProjectileHits.Enabled = true;
      }else{
        ProjectileHits.Enabled = false;
      }
    }
  }
}
