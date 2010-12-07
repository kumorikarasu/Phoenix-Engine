using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using System.IO;
using System.Threading;

namespace HitBox_Editor
{
  public partial class HitBoxEditor : Form
  {
    public Film_Roll filmRoll;
    public Player player;
    
    enum ToolType
    {
      None = 0,
      Move,
      Select,
      Add,
      AddHB,
      AddAHB
    }

    int CurX, CurY;
    int MouseX, MouseY;
    float ScaleX,ScaleY;
    bool MouseDown;
    Bitmap bp;
    ToolType Tool;
    bool DisplayGrid;
    public int currentFrame;
    int maxFrame;
    AutoResetEvent playAnimation;
    bool StopAnimation;

    public HitBoxEditor()
    {
      filmRoll = null;
      InitializeComponent();
      CurX = 0;
      CurY = 0;
      MouseX = 0;
      MouseY = 0;
      ScaleX = 1;
      ScaleY = 1;
      DisplayGrid = true;
      currentFrame = 0;
      StopAnimation = false;
    }

    private void Form1_Load(object sender, EventArgs e)
    {
      PropertyGridCharacter p = new PropertyGridCharacter();
      p.Name = "Hi";
      propertyGrid1.SelectedObject = p;

      Graphics g;
      bp = new Bitmap(this.ClientRectangle.Width, this.ClientRectangle.Height,
        System.Drawing.Imaging.PixelFormat.Format24bppRgb);
      g = Graphics.FromImage(bp);
      var myPen = new System.Drawing.Pen(System.Drawing.Color.Green);
      g.DrawLine(myPen, MainGraphicPanel.Width / 2 + CurX, 0, MainGraphicPanel.Width / 2 + CurX, MainGraphicPanel.Height);
      g.DrawLine(myPen, 0, MainGraphicPanel.Height / 2 + CurY, MainGraphicPanel.Width, MainGraphicPanel.Height / 2 + CurY);
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

    private void MainGraphicPanel_Paint(object sender, PaintEventArgs e)
    {
      System.Drawing.Graphics g = e.Graphics;

      if (player != null){
        Image i = player.GetImage(currentFrame);
        if (i != null)
          g.DrawImage(i, CurX + (MainGraphicPanel.Width / 2) - i.Width / 2 * ScaleX,
                      CurY + (MainGraphicPanel.Height / 2) - i.Height / 2 * ScaleY,
                      i.Width * ScaleX,i.Height * ScaleY);
      }

      if (DisplayGrid){
        var myPen = new System.Drawing.Pen(System.Drawing.Color.Green);
        myPen.Width = 1;
        g.DrawLine(myPen,(int) (MainGraphicPanel.Width / 2), 0, MainGraphicPanel.Width / 2, MainGraphicPanel.Height);
        g.DrawLine(myPen, 0,(int) (MainGraphicPanel.Height / 2), MainGraphicPanel.Width, (int) (MainGraphicPanel.Height / 2));

        myPen = new System.Drawing.Pen(System.Drawing.Color.Blue);
        g.DrawLine(myPen, 0,(int) (MainGraphicPanel.Height / 2) + 50, MainGraphicPanel.Width, (int) (MainGraphicPanel.Height / 2) + 50);
        myPen.Dispose();
      }
      if (filmRoll != null)
        filmRoll.panel2.Invalidate();
    }

    private void MainGraphicPanel_MouseDown(object sender, MouseEventArgs e)
    {
      MouseDown = true;
      MouseX = MousePosition.X;
      MouseY = MousePosition.Y;
    }

    private void MainGraphicPanel_MouseUp(object sender, MouseEventArgs e)
    {
      MouseDown = false;
    }

    private void MainGraphicPanel_MouseMove(object sender, MouseEventArgs e)
    {
      if (MouseDown && Tool == ToolType.Move)
      {
        CurX += MousePosition.X - MouseX;
        CurY += MousePosition.Y - MouseY;
        MouseX = MousePosition.X;
        MouseY = MousePosition.Y;
        MainGraphicPanel.Invalidate();
        if (CurX > MainGraphicPanel.Width)
          CurX = MainGraphicPanel.Width;
        if (CurX < -MainGraphicPanel.Width)
          CurX = -MainGraphicPanel.Width;
        if (CurY > MainGraphicPanel.Height)
          CurY = MainGraphicPanel.Height;
        if (CurY < -MainGraphicPanel.Height)
          CurY = -MainGraphicPanel.Height;
      }
    }

    private void HitBoxEditor_Resize(object sender, EventArgs e)
    {
      MainGraphicPanel.Invalidate();
    }

    private void MoveTool_Click(object sender, EventArgs e)
    {
      if (MoveTool.Checked){
        Tool = ToolType.Move;
        MainGraphicPanel.Cursor = Cursors.Hand;
        EditTool.Checked = false;
        AddATool.Checked = false;
        AddTool.Checked = false;
      }else{
        Tool = ToolType.None;
        MainGraphicPanel.Cursor = Cursors.Default;
      }
    }

    private void Grid_Click(object sender, EventArgs e)
    {
      DisplayGrid = !DisplayGrid;
      MainGraphicPanel.Invalidate();
    }

    private void EditTool_Click(object sender, EventArgs e)
    {
      if (EditTool.Checked){
        Tool = ToolType.Select;
        MoveTool.Checked = false;
        AddATool.Checked = false;
        AddTool.Checked = false;
        MainGraphicPanel.Cursor = Cursors.Cross;
      }else{
        Tool = ToolType.None;
        MainGraphicPanel.Cursor = Cursors.Default;
      }
    }

    private void AddTool_Click(object sender, EventArgs e)
    {
      if (AddTool.Checked){
        Tool = ToolType.AddHB;
        MoveTool.Checked = false;
        EditTool.Checked = false;
        AddATool.Checked = false;
        MainGraphicPanel.Cursor = Cursors.SizeAll;
      }else{
        Tool = ToolType.None;
        MainGraphicPanel.Cursor = Cursors.Default;
      }
    }

    private void AddATool_Click(object sender, EventArgs e)
    {
      if (AddATool.Checked){
        Tool = ToolType.AddAHB;
        MoveTool.Checked = false;
        EditTool.Checked = false;
        AddTool.Checked = false;
        MainGraphicPanel.Cursor = Cursors.SizeAll;
      }else{
        Tool = ToolType.None;
        MainGraphicPanel.Cursor = Cursors.Default;
      }

    }

    private void New_Click(object sender, EventArgs e)
    {
      var dia = new NewDialog();
      if (dia.ShowDialog() == DialogResult.OK){
        var d = new FolderBrowserDialog();
        if (d.ShowDialog() == DialogResult.OK){
          string path = d.SelectedPath;
          player = new Player();
          FrameNumber.Visible = false;
          Progress.Visible = true;
          double i = 0;

//TODO: DEBUG ONRY< REMOVE THIS
          path = "C:\\Dev\\Reimu";

          string[] dir = Directory.GetFiles(path, "*.png");
          double length = dir.Length;
          try{
            foreach (var image in dir){
              player.LoadImage(image);
              Progress.Value = (int)(i / length * 100);
              i++;
            }
          }
          catch (Exception ex){
            FrameNumber.Text = "Unable to Load Directory";
            return;
          }
          FrameNumber.Visible = true;
          Progress.Visible = false;
          maxFrame = player.imageLength - 1;
          FrameNumber.Text = "Frame " + currentFrame + " out of " + maxFrame;

          this.Invalidate();
          MainGraphicPanel.Invalidate();
        }
      }
    }

    private void NextFrame_Click(object sender, EventArgs e)
    {
      SaveProperties();
      UpdateFrame(currentFrame + 1);
      LoadProperties();
    }

    private void LoadProperties()
    {
     // throw new NotImplementedException();
    }

    private void SaveProperties()
    {
      new System.Threading.Thread(() => {

        return;
      }).Start();
    }

    private void PrevFrame_Click(object sender, EventArgs e)
    {
      UpdateFrame(currentFrame - 1);
    }

    private void JumpTo_Click(object sender, EventArgs e)
    {
      var frame = Int32.Parse(FrameMoveBox.Text);
      UpdateFrame(frame);
    }

    private void filmRollToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (filmRoll == null)
        filmRoll = new Film_Roll(this);
      filmRoll.Show();
    }

    private void HitBoxEditor_KeyDown(object sender, KeyEventArgs e)
    {
      if (e.Modifiers == Keys.Control && e.KeyCode == Keys.R){
        if (filmRoll == null)
          filmRoll = new Film_Roll(this);
        filmRoll.Show();
      }

      if (Tool == ToolType.Move){
        if (e.KeyCode == Keys.Left)
          if (CurX > 0)
            CurX--;
      }
    }

    private void newToolStripMenuItem_Click(object sender, EventArgs e)
    {
      New_Click(sender,e);
    }

    private void toolStripButton2_Click(object sender, EventArgs e)
    {
      ScaleY *= 1.10f;
      ScaleX *= 1.10f;
      MainGraphicPanel.Invalidate();
    }

    private void toolStripButton3_Click(object sender, EventArgs e)
    {
      ScaleX = 1;
      ScaleY = 1;
      MainGraphicPanel.Invalidate();
    }

    private void toolStripButton1_Click(object sender, EventArgs e)
    {
      if (player != null){
        if (playAnimation == null){

          System.Threading.Timer t = null;
          playAnimation = new AutoResetEvent(false);
          StopAnimation = false;

          t = new System.Threading.Timer(o => {
            if (!UpdateFrame(currentFrame + 1))
              t.Dispose();

            if (StopAnimation){
              t.Dispose();
              playAnimation.Dispose();
              playAnimation = null;
            }
            return;
          },playAnimation,0,1000 / Int32.Parse(playspeed.Text));
        }else{
          StopAnimation = true;
          playAnimation.Dispose();
          playAnimation = null;
        }
      }
    }

    public bool UpdateFrame(int FrameNumber){
      if (player != null)
        if (FrameNumber >= 0 && FrameNumber < player.imageLength){
          currentFrame = FrameNumber;
          this.FrameNumber.Text = "Frame " + FrameNumber + " out of " + (player.imageLength - 1);
          //this.FrameMoveBox.Text = "" + FrameNumber;
          MainGraphicPanel.Invalidate();

          if (filmRoll != null)
            filmRoll.position = currentFrame;

          return true;
        }
      return false;
    }
  }
}
