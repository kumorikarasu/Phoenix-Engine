using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace HitBox_Editor
{
  public partial class HitBoxEditor : Form
  {
    enum ToolType
    {
      None = 0,
      Move,
      Select,
      Add
    }
    int CurX, CurY;
    int MouseX, MouseY;
    bool MouseDown;
    Bitmap bp;
    ToolType Tool;
    bool DisplayGrid;

    public HitBoxEditor()
    {
      InitializeComponent();
      CurX = -100;
      CurY = 100;
      MouseX = 0;
      MouseY = 0;
      DisplayGrid = true;
    }

    private void Form1_Load(object sender, EventArgs e)
    {
      Proporties p = new Proporties();
      p.Name = "Hi";
      propertyGrid1.SelectedObject = p;

      Graphics g;
      bp = new Bitmap(this.ClientRectangle.Width, this.ClientRectangle.Height,
        System.Drawing.Imaging.PixelFormat.Format24bppRgb);
      g = Graphics.FromImage(bp);
      var myPen = new System.Drawing.Pen(System.Drawing.Color.Green);
      g.DrawLine(myPen, panel1.Width / 2 + CurX, 0, panel1.Width / 2 + CurX, panel1.Height);
      g.DrawLine(myPen, 0, panel1.Height / 2 + CurY, panel1.Width, panel1.Height / 2 + CurY);
      myPen.Dispose();
      g.Dispose();
    }

    private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
    {
      AboutBox ab = new AboutBox();
      ab.Show();
    }

    private void exitToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.Close();
    }

    private void panel1_Paint(object sender, PaintEventArgs e)
    {
      if (DisplayGrid){
        var myPen = new System.Drawing.Pen(System.Drawing.Color.Green);
        myPen.Width = 1;
        System.Drawing.Graphics formGraphics = panel1.CreateGraphics();
        formGraphics.DrawLine(myPen, panel1.Width / 2 + CurX, 0, panel1.Width / 2 + CurX, panel1.Height);
        formGraphics.DrawLine(myPen, 0, panel1.Height / 2 + CurY, panel1.Width, panel1.Height / 2 + CurY);
        myPen.Dispose();
        formGraphics.Dispose();
      }
    }

    private void panel1_MouseDown(object sender, MouseEventArgs e)
    {
      MouseDown = true;
      MouseX = MousePosition.X;
      MouseY = MousePosition.Y;
    }

    private void panel1_MouseUp(object sender, MouseEventArgs e)
    {
      MouseDown = false;
    }

    private void panel1_MouseMove(object sender, MouseEventArgs e)
    {
      if (MouseDown && Tool == ToolType.Move)
      {
        CurX += MousePosition.X - MouseX;
        CurY += MousePosition.Y - MouseY;
        MouseX = MousePosition.X;
        MouseY = MousePosition.Y;
        panel1.Invalidate();
        if (CurX > panel1.Width / 2)
          CurX = panel1.Width / 2;
        if (CurX < panel1.Width / -2)
          CurX = panel1.Width / -2;
        if (CurY > panel1.Height / 2)
          CurY = panel1.Height / 2;
        if (CurY < panel1.Height / -2)
          CurY = panel1.Height / -2;
      }
    }

    private void HitBoxEditor_Resize(object sender, EventArgs e)
    {
      panel1.Invalidate();
    }

    private void MoveTool_Click(object sender, EventArgs e)
    {
      if (MoveTool.Checked){
        Tool = ToolType.Move;
        panel1.Cursor = Cursors.SizeAll;
      }else{
        Tool = ToolType.None;
        panel1.Cursor = Cursors.Default;
      }
    }

    private void Grid_Click(object sender, EventArgs e)
    {
      DisplayGrid = !DisplayGrid;
      panel1.Invalidate();
    }

  }
}
