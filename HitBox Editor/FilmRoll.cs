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
  public partial class Film_Roll : Form
  {
    HitBoxEditor parent;
    public Film_Roll(HitBoxEditor hb)
    {
      InitializeComponent();
      parent = hb;
    }

    private void Film_Roll_Load(object sender, EventArgs e)
    {

    }

    private void Film_Roll_FormClosed(object sender, FormClosedEventArgs e)
    {
      parent.filmRoll = null;
    }
  }
}
