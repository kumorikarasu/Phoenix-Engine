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
  public partial class Summary : Form
  {
    private   HitBoxEditor hitBoxEditor;

    public Summary()
    {
      InitializeComponent();
    }

    public Summary(HitBoxEditor hitBoxEditor)
    {
      // TODO: Complete member initialization
      this.hitBoxEditor = hitBoxEditor;
    }

    public void Add(string name){
      SummaryList.Items.Add(name);
    }

    public void Clear(){
      SummaryList.Items.Clear();
    }

    internal void Remove(string p)
    {
      SummaryList.Items.Remove(p);
    }

    private void Summary_FormClosing(object sender, FormClosingEventArgs e)
    {
      this.Hide();
      e.Cancel = true;
    }
  }
}