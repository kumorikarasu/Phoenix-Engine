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
    int count = 0;
    public int position = 0;

    public Film_Roll(HitBoxEditor hb)
    {
      InitializeComponent();
      parent = hb;
    }

    private void Film_Roll_Load(object sender, EventArgs e)
    {
      position = parent.currentFrame;
    }

    private void Film_Roll_FormClosed(object sender, FormClosedEventArgs e)
    {
      parent.filmRoll = null;
    }

    private void panel2_Paint(object sender, PaintEventArgs e)
    {
      Graphics g = e.Graphics;
      if (parent.player != null){
        var imageWidth = 0;
        for(int i = position; i < parent.player.imageLength; i++){
          var f = new Font("Times New Roman",11);
          var b = new SolidBrush(Color.Green);
          var p = new PointF();
          
          Image image = parent.player.GetImage(i);
          if (image != null)
          {
            p.X = 0 + imageWidth;
            g.DrawImage(image, 0 + imageWidth, 0);
            g.DrawString("" + i,f,b,p);
            imageWidth += image.Width;
          }
        }
        FilmRollScroll.Maximum = parent.player.imageLength;
      }
    }

    private void FilmRollScroll_Scroll(object sender, ScrollEventArgs e)
    {
      position = FilmRollScroll.Value;
      panel2.Invalidate();
    }

    private void panel2_MouseClick(object sender, MouseEventArgs e)
    {
      if (parent.player != null){
        var imageWidth = 0;
        for(int i = position; i < parent.player.imageLength; i++){
          Image image = parent.player.GetImage(i);
          if (image != null)
          {
            if (e.X > imageWidth && e.X < imageWidth + image.Width){
              parent.currentFrame = i;
              parent.MainGraphicPanel.Invalidate();
              parent.FrameMoveBox.Text = "" + i;
            }
            imageWidth += image.Width;
          }
        }
      }
    }

    private void Film_Roll_KeyUp(object sender, KeyEventArgs e)
    {
      if (e.KeyCode == Keys.Left){
        if (position > 0){
          position--;
          parent.currentFrame = position;
          parent.MainGraphicPanel.Invalidate();
          parent.FrameMoveBox.Text = "" + position;
          panel2.Invalidate();
        }
      }
      if (e.KeyCode == Keys.Right){
        if (position < parent.player.imageLength)
          position++;
          parent.currentFrame = position;
          parent.MainGraphicPanel.Invalidate();
          parent.FrameMoveBox.Text = "" + position;
          panel2.Invalidate();
      }
    }
  }
}
