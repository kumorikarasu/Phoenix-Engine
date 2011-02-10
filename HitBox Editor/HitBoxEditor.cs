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
using System.Xml.Serialization;
using System.Reflection;
using System.IO.Compression;

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
      AddAHB,
      MoveImage
    }

    private int     curX, curY;
    private int     mouseX, mouseY;
    private int     resizing;
    private int     maxFrame;
    private float   scaleX,scaleY;
    private bool    mouseDown;
    private bool    displayGrid;
    private bool    stopAnimation;
    private string  saveFilePath;
    private string  imageFilePath;
    private Vector2   drawOffSet;
    private Vector2   drawVelocity;
    private Summary summaryBox;
    private Bitmap  bp;
    private HitBox  hitBox;
    private HitBox  storedHitbox;
    private ToolType tool;
    private AutoResetEvent playAnimation;
    private PropertyGridCharacter propertyGrid;
    private System.Windows.Forms.Timer playAnimationTimer;

    public int      currentFrame;

    public HitBoxEditor()
    {
      InitializeComponent();

      currentFrame  = 0;

      curX          = 0;
      curY          = 0;
      mouseX        = 0;
      mouseY        = 0;
      scaleX        = 1;
      scaleY        = 1;
      resizing      = 0;
      saveFilePath  = "";
      filmRoll      = null;
      storedHitbox  = null;
      displayGrid   = true;
      stopAnimation = false;

      summaryBox    = new Summary();
      drawOffSet    = new Vector2(0,0);
      drawVelocity  = new Vector2(0,0);
      playAnimationTimer = new System.Windows.Forms.Timer();
    }

    private void Form1_Load(object sender, EventArgs e)
    {
      propertyGrid = new PropertyGridCharacter();
      propertyGrid1.SelectedObject = propertyGrid;

      bp = new Bitmap(this.ClientRectangle.Width, this.ClientRectangle.Height,
                      System.Drawing.Imaging.PixelFormat.Format24bppRgb);
      var g = Graphics.FromImage(bp);

      var myPen = new System.Drawing.Pen(System.Drawing.Color.Green);

      g.DrawLine(myPen, MainGraphicPanel.Width / 2 + curX,
                        0,
                        MainGraphicPanel.Width / 2 + curX, 
                        MainGraphicPanel.Height);
      g.DrawLine(myPen, 0, 
                        MainGraphicPanel.Height / 2 + curY,
                        MainGraphicPanel.Width,
                        MainGraphicPanel.Height / 2 + curY);

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

        Image image = player.GetImage(currentFrame);
        if (image != null)
          g.DrawImage(image, 
                      curX + player.sprites[currentFrame].pos.X + drawOffSet.X + (MainGraphicPanel.Width / 2) - image.Width / 2 * scaleX,
                      curY + player.sprites[currentFrame].pos.Y + drawOffSet.Y + (MainGraphicPanel.Height / 2) - image.Height / 2 * scaleY,
                      image.Width * scaleX,image.Height * scaleY);

        
        if (ToggleHitbox.Checked){
          foreach(var i in player.sprites[currentFrame].hitBoxes){
            i.Draw(g, new Point(MainGraphicPanel.Width + (int)drawOffSet.X, MainGraphicPanel.Height + (int)drawOffSet.Y));
          }
        }

      }

      if (displayGrid){
        var myPen = new System.Drawing.Pen(System.Drawing.Color.Green);
        myPen.Width = 1;
        g.DrawLine(myPen,(int) (MainGraphicPanel.Width / 2), 0, MainGraphicPanel.Width / 2, MainGraphicPanel.Height);
        g.DrawLine(myPen, 0,(int) (MainGraphicPanel.Height / 2), MainGraphicPanel.Width, (int) (MainGraphicPanel.Height / 2));

        myPen = new System.Drawing.Pen(System.Drawing.Color.Blue);
        g.DrawLine(myPen, 0,(int) (MainGraphicPanel.Height / 2) + 50, MainGraphicPanel.Width, (int) (MainGraphicPanel.Height / 2) + 50);
        myPen.Dispose();
      }

      if (hitBox != null){
            hitBox.Draw(g, new Point(MainGraphicPanel.Width,MainGraphicPanel.Height));
      }

      if (filmRoll != null)
        filmRoll.panel2.Invalidate();

    }

    private void MainGraphicPanel_MouseDown(object sender, MouseEventArgs e)
    {
      if (e.Button == MouseButtons.Left){
        mouseDown = true;
        mouseX = MousePosition.X;
        mouseY = MousePosition.Y;
      }
      
      if (e.Button == MouseButtons.Right){
        hitBox = null;

        //<3 lambda
        player.sprites[currentFrame].hitBoxes.ForEach(i => { i.selected = false; }); 
        MainGraphicPanel.Invalidate();
      }

      if (mouseDown && tool == ToolType.AddHB && player != null){
        hitBox = new HitBox(player.sprites[currentFrame], new Point(MainGraphicPanel.Width,MainGraphicPanel.Height));
        var p = MainGraphicPanel.PointToClient(new Point(mouseX,mouseY));
        hitBox.x = p.X;
        hitBox.y = p.Y;
      }

      if (mouseDown && tool == ToolType.AddAHB && player != null){
        hitBox = new HitBox(player.sprites[currentFrame], new Point(MainGraphicPanel.Width,MainGraphicPanel.Height));
        hitBox.type = 1;
        var p = MainGraphicPanel.PointToClient(new Point(mouseX,mouseY));
        hitBox.x = p.X;
        hitBox.y = p.Y;
      }

      if (mouseDown && tool == ToolType.Select && player != null){
        foreach(var hb in player.sprites[currentFrame].hitBoxes){
          var p = MainGraphicPanel.PointToClient(new Point(mouseX,mouseY));
          if (hb.CheckCollision(p)){
            player.sprites[currentFrame].hitBoxes.ForEach(i => { i.selected = false; }); 
            hb.selected = true;
            MainGraphicPanel.Invalidate();
            break;
          }
        }
      }
    }

    private void MainGraphicPanel_MouseUp(object sender, MouseEventArgs e)
    {
      if (mouseDown && (tool == ToolType.AddHB || tool == ToolType.AddAHB)){
        if (hitBox != null){
          hitBox.Correct();
          player.sprites[currentFrame].hitBoxes.ForEach(i => { i.selected = false; }); 
          player.sprites[currentFrame].hitBoxes.Add(hitBox);
          hitBox.selected = true;
          tool = ToolType.Select;
          EditTool.Checked = true;
          AddATool.Checked = false;
          AddTool.Checked = false;
          MainGraphicPanel.Invalidate();

          hitBox = null;
        }
      }

      resizing = 0;
      mouseDown = false;
    }

    private void MainGraphicPanel_MouseMove(object sender, MouseEventArgs e)
    {
      if (mouseDown && tool == ToolType.Move)
      {
        curX += MousePosition.X - mouseX;
        curY += MousePosition.Y - mouseY;
        mouseX = MousePosition.X;
        mouseY = MousePosition.Y;
        if (curX > MainGraphicPanel.Width)
          curX = MainGraphicPanel.Width;
        if (curX < -MainGraphicPanel.Width)
          curX = -MainGraphicPanel.Width;
        if (curY > MainGraphicPanel.Height)
          curY = MainGraphicPanel.Height;
        if (curY < -MainGraphicPanel.Height)
          curY = -MainGraphicPanel.Height;
        MainGraphicPanel.Invalidate();
      }
      if (mouseDown && tool == ToolType.MoveImage){
        var pos = player.sprites[currentFrame].pos;
        int x = pos.X += MousePosition.X - mouseX;
        int y = pos.Y += MousePosition.Y - mouseY;
        mouseX = MousePosition.X;
        mouseY = MousePosition.Y;
        if (x > MainGraphicPanel.Width)
          x = MainGraphicPanel.Width;
        if (x < -MainGraphicPanel.Width)
          x = -MainGraphicPanel.Width;
        if (y > MainGraphicPanel.Height)
          y = MainGraphicPanel.Height;
        if (y < -MainGraphicPanel.Height)
          y = -MainGraphicPanel.Height;
        player.sprites[currentFrame].pos = new Rectangle(x, y, pos.Width, pos.Height);
        MainGraphicPanel.Invalidate();
      }

      if (mouseDown && (tool == ToolType.AddHB || tool == ToolType.AddAHB) && hitBox != null){
        var p = MainGraphicPanel.PointToClient(new Point(MousePosition.X,MousePosition.Y));
        hitBox.xx = p.X;
        hitBox.yy = p.Y;
        MainGraphicPanel.Invalidate();
      }

      if (tool == ToolType.Select && player != null){
        var result = player.sprites[currentFrame].hitBoxes.SingleOrDefault(i => i.selected == true);
        if (result != null){
          var p = MainGraphicPanel.PointToClient(new Point(MousePosition.X, MousePosition.Y));
          int corner = result.CheckCorners(p);
          if (resizing != 5 && (corner == 7 /*top left*/ || resizing == 7)) {
            MainGraphicPanel.Cursor = Cursors.SizeNWSE;
            if (mouseDown){
              result.x += MousePosition.X - mouseX;
              result.y += MousePosition.Y - mouseY;
              mouseX = MousePosition.X;
              mouseY = MousePosition.Y;
              MainGraphicPanel.Invalidate();
              resizing = 7;
            }
          }else
          if (resizing != 5 && (corner == 9 /*top right*/ || resizing == 9)) {
            MainGraphicPanel.Cursor = Cursors.SizeNESW;
            if (mouseDown){
              result.xx += MousePosition.X - mouseX;
              result.y += MousePosition.Y - mouseY;
              mouseX = MousePosition.X;
              mouseY = MousePosition.Y;
              MainGraphicPanel.Invalidate();
              resizing = 9;
            }
          }else
          if (resizing != 5 && (corner == 3 /*bottom right*/ || resizing == 3)) {
            MainGraphicPanel.Cursor = Cursors.SizeNWSE;
            if (mouseDown){
              result.xx += MousePosition.X - mouseX;
              result.yy += MousePosition.Y - mouseY;
              mouseX = MousePosition.X;
              mouseY = MousePosition.Y;
              MainGraphicPanel.Invalidate();
              resizing = 3;
            }
          }else
          if (resizing != 5 && (corner == 1 /*bottom left*/ || resizing == 1)) {
            MainGraphicPanel.Cursor = Cursors.SizeNESW;
            if (mouseDown){
              result.x += MousePosition.X - mouseX;
              result.yy += MousePosition.Y - mouseY;
              mouseX = MousePosition.X;
              mouseY = MousePosition.Y;
              MainGraphicPanel.Invalidate();
              resizing = 1;
            }
          }else
          if (resizing != 5 && (corner == 2 /*bottom*/ || resizing == 2)) {
            MainGraphicPanel.Cursor = Cursors.SizeNS;
            if (mouseDown){
              result.yy += MousePosition.Y - mouseY;
              mouseY = MousePosition.Y;
              MainGraphicPanel.Invalidate();
              resizing = 2;
            }
          }else
          if (resizing != 5 && (corner == 8 /*top*/ || resizing == 8)) {
            MainGraphicPanel.Cursor = Cursors.SizeNS;
            if (mouseDown){
              result.y += MousePosition.Y - mouseY;
              mouseY = MousePosition.Y;
              MainGraphicPanel.Invalidate();
              resizing = 8;
            }
          }else
          if (resizing != 5 && (corner == 6 /*right*/ || resizing == 6)) {
            MainGraphicPanel.Cursor = Cursors.SizeWE;
            if (mouseDown){
              result.xx += MousePosition.X - mouseX;
              mouseX = MousePosition.X;
              mouseY = MousePosition.Y;
              MainGraphicPanel.Invalidate();
              resizing = 6;
            }
          }else
          if (resizing != 5 && (corner == 4 /*left*/ || resizing == 4)) {
            MainGraphicPanel.Cursor = Cursors.SizeWE;
            if (mouseDown){
              result.x += MousePosition.X - mouseX;
              mouseX = MousePosition.X;
              mouseY = MousePosition.Y;
              MainGraphicPanel.Invalidate();
              resizing = 4;
            }
          } else if (mouseDown && (resizing == 0 || resizing == 5)) {
            MainGraphicPanel.Cursor = Cursors.SizeAll;
            result.x += MousePosition.X - mouseX;
            result.y += MousePosition.Y - mouseY;
            result.xx += MousePosition.X - mouseX;
            result.yy += MousePosition.Y - mouseY;
            mouseX = MousePosition.X;
            mouseY = MousePosition.Y;
            MainGraphicPanel.Invalidate();
            resizing = 5;
          } else {
            MainGraphicPanel.Cursor = Cursors.Cross;
          }

          result.Correct();
        }
      }
    }

    private void HitBoxEditor_Resize(object sender, EventArgs e)
    {
      MainGraphicPanel.Invalidate();
    }

    private void MoveImageTool_Click(object sender, EventArgs e)
    {
      if (MoveImageTool.Checked){
        tool = ToolType.MoveImage;
        MainGraphicPanel.Cursor = Cursors.Hand;
        MoveTool.Checked = false;
        EditTool.Checked = false;
        AddATool.Checked = false;
        AddTool.Checked = false;
      }else{
        tool = ToolType.None;
        MainGraphicPanel.Cursor = Cursors.Default;
      }
    }

    private void MoveTool_Click(object sender, EventArgs e)
    {
      if (MoveTool.Checked){
        tool = ToolType.Move;
        MainGraphicPanel.Cursor = Cursors.Hand;
        MoveImageTool.Checked = false;
        EditTool.Checked = false;
        AddATool.Checked = false;
        AddTool.Checked = false;
      }else{
        tool = ToolType.None;
        MainGraphicPanel.Cursor = Cursors.Default;
      }
    }

    private void Grid_Click(object sender, EventArgs e)
    {
      displayGrid = !displayGrid;
      MainGraphicPanel.Invalidate();
    }

    private void EditTool_Click(object sender, EventArgs e)
    {
      if (EditTool.Checked){
        tool = ToolType.Select;
        MoveImageTool.Checked = false;
        MoveTool.Checked = false;
        AddATool.Checked = false;
        AddTool.Checked = false;
        MainGraphicPanel.Cursor = Cursors.Cross;
      }else{
        tool = ToolType.None;
        MainGraphicPanel.Cursor = Cursors.Default;
      }
    }

    private void AddTool_Click(object sender, EventArgs e)
    {
      if (AddTool.Checked){
        tool = ToolType.AddHB;
        MoveImageTool.Checked = false;
        MoveTool.Checked = false;
        EditTool.Checked = false;
        AddATool.Checked = false;
        MainGraphicPanel.Cursor = Cursors.SizeAll;
      }else{
        tool = ToolType.None;
        MainGraphicPanel.Cursor = Cursors.Default;
      }
    }

    private void AddATool_Click(object sender, EventArgs e)
    {
      if (AddATool.Checked){
        tool = ToolType.AddAHB;
        MoveImageTool.Checked = false;
        MoveTool.Checked = false;
        EditTool.Checked = false;
        AddTool.Checked = false;
        MainGraphicPanel.Cursor = Cursors.SizeAll;
      }else{
        tool = ToolType.None;
        MainGraphicPanel.Cursor = Cursors.Default;
      }

    }

    private void New_Click(object sender, EventArgs e)
    {
      var dia = new NewDialog();
      if (dia.ShowDialog() == DialogResult.OK){
        var d = new FolderBrowserDialog();
        if (d.ShowDialog() == DialogResult.OK){
          imageFilePath = d.SelectedPath;
          imageFilePath = System.IO.Path.Combine(Application.StartupPath, imageFilePath);
          player = new Player();
          FrameNumber.Visible = false;
          Progress.Visible = true;

          if (!LoadPath(imageFilePath))
            return;
        }
      }
    }

    private bool LoadPath(string imageFilePath)
    {
      try {
      double i = 0;
      string[] dir = Directory.GetFiles(imageFilePath, "*.png");
      double length = dir.Length;
        foreach (var image in dir) {
          player.LoadImage(image);
          Progress.Value = (int)(i / length * 100);
          i++;
        }
      }
      catch (Exception ex){
        FrameNumber.Text = "Unable to Load Directory";
        return false;
      }

      FrameNumber.Visible = true;
      Progress.Visible = false;
      maxFrame = player.imageLength - 1;
      FrameNumber.Text = "Frame " + currentFrame + " out of " + maxFrame;

      this.Invalidate();
      MainGraphicPanel.Invalidate();
      LoadProperties();

      return true;
    }

    private void NextFrame_Click(object sender, EventArgs e)
    {
      SaveProperties();
      UpdateFrame(currentFrame + 1);
      drawOffSet = new Vector2(0,0);
      LoadProperties();
    }

    public void LoadProperties()
    {
      if (player != null){
        propertyGrid = player.GetGrid(currentFrame);
        propertyGrid1.SelectedObject = propertyGrid;
      }
    }

    public void SaveProperties()
    {
    }

    private void PrevFrame_Click(object sender, EventArgs e)
    {
      SaveProperties();
      UpdateFrame(currentFrame - 1);
      drawOffSet = new Vector2(0,0);
      LoadProperties();
    }

    private void JumpTo_Click(object sender, EventArgs e)
    {
      SaveProperties();
      var frame = Int32.Parse(FrameMoveBox.Text);
      UpdateFrame(frame);
      drawOffSet = new Vector2(0,0);
      LoadProperties();
    }

    private void filmRollToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (filmRoll == null)
        filmRoll = new Film_Roll(this);
      filmRoll.Show();
    }

    private void HitBoxEditor_KeyUp(object sender, KeyEventArgs e)
    {
      if (e.KeyCode == Keys.Delete){
        var result = player.sprites[currentFrame].hitBoxes.SingleOrDefault(i => i.selected == true);
        player.sprites[currentFrame].hitBoxes.Remove(result);
        MainGraphicPanel.Invalidate();
      }

      if (e.Modifiers == Keys.Control && e.KeyCode == Keys.R){
        if (filmRoll == null)
          filmRoll = new Film_Roll(this);

        if (!filmRoll.Visible){
          filmRoll.Show();
        }else{
          filmRoll.Hide();
        }
      }

      if (e.Modifiers == Keys.Control && e.KeyCode == Keys.F){
        if (summaryBox == null)
          summaryBox = new Summary(this);

        if (!summaryBox.Visible){
          summaryBox.Show();
        }else{
          summaryBox.Hide();
        }
      }

      if (e.Modifiers == Keys.Control && e.KeyCode == Keys.C){
        foreach(var hb in player.sprites[currentFrame].hitBoxes){
          var p = MainGraphicPanel.PointToClient(new Point(mouseX,mouseY));
          if (hb.selected){
            storedHitbox = hb;
          }
        }
      }

      if (e.Modifiers == Keys.Control && e.KeyCode == Keys.V){
        if (storedHitbox != null){
          player.sprites[currentFrame].hitBoxes.ForEach(n => n.selected = false);
          var hit = new HitBox();
          hit.x = storedHitbox.x;
          hit.y = storedHitbox.y;
          hit.xx = storedHitbox.xx;
          hit.yy = storedHitbox.yy;
          hit.type = storedHitbox.type;
          hit.xoff = storedHitbox.xoff;
          hit.yoff = storedHitbox.yoff;
          hit.selected = true;
          player.sprites[currentFrame].hitBoxes.Add(hit);
          MainGraphicPanel.Invalidate();
        }
        
      }

      if (tool == ToolType.Move){
        if (e.KeyCode == Keys.Left)
          if (curX > 0)
            curX--;
      }
    }

    private void newToolStripMenuItem_Click(object sender, EventArgs e)
    {
      New_Click(sender,e);
    }

    private void toolStripButton2_Click(object sender, EventArgs e)
    {
      /*
      ScaleY *= 1.10f;
      ScaleX *= 1.10f;
      MainGraphicPanel.Invalidate();
      */
    }

    private void toolStripButton3_Click(object sender, EventArgs e)
    {
      scaleX = 1;
      scaleY = 1;
      MainGraphicPanel.Invalidate();
    }

    private void toolStripButton1_Click(object sender, EventArgs e)
    {
      int startFrame;
      if (player != null){
        if (playAnimationTimer.Enabled == false){

         // System.Threading.Timer t = null;
          stopAnimation = false;
          startFrame = currentFrame;
          drawOffSet = new Vector2(0,0);
          drawVelocity = new Vector2(0,0);

          playAnimationTimer = new System.Windows.Forms.Timer();
          playAnimationTimer.Interval = 1000 / Int32.Parse(playspeed.Text);
          playAnimationTimer.Enabled = true;
          playAnimationTimer.Tick += new System.EventHandler((object sender2, EventArgs e2) => {

            var j = player.props[currentFrame];
            drawVelocity.X += j.VelocityX;
            drawVelocity.Y += j.VelocityY;
            drawOffSet.X += drawVelocity.X;
            drawOffSet.Y += drawVelocity.Y;

            drawVelocity.Y += 0.5f;
            if (drawVelocity.Y > 0 && drawOffSet.Y > 0)
              drawVelocity.Y = 0;

            SaveProperties();
            if (propertyGrid.JumpToImage != -1 && propertyGrid.JumpToImage <= player.imageLength && propertyGrid.JumpToImage > 1) {
              currentFrame = propertyGrid.JumpToImage - 1;
            }
            
            if (!UpdateFrame(currentFrame + 1))
              playAnimationTimer.Enabled = false;;
            LoadProperties();

            var i = player.props[currentFrame];
            if (i.EndFrame == true) {
              playAnimationTimer.Enabled = false;
              SaveProperties();
              drawOffSet = new Vector2(0,0);
              currentFrame = startFrame;
              LoadProperties();
            }

          });

        }else{
          playAnimationTimer.Enabled = false;
          drawOffSet = new Vector2(0,0);
          drawVelocity = new Vector2(0,0);
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

            LoadProperties();
          return true;
        }
      return false;
    }

    private void playspeed_KeyPress(object sender, KeyEventArgs e)
    {
      if (e.KeyCode == Keys.Enter){
        toolStripButton1_Click(sender, e);
        e.Handled = true;
      }
    }

    private void FrameMoveBox_KeyUp(object sender, KeyEventArgs e)
    {
      if (e.KeyCode == Keys.Enter){
        JumpTo_Click(sender, e);
        e.Handled = true;
      }
    }

    private void Save_Click(object sender, EventArgs e)
    {
      if (player != null){
        if (saveFilePath == ""){
          SaveFileDialog sfd = new SaveFileDialog();
          sfd.DefaultExt = "chr";
          sfd.Filter = "Character File (*.chr)|*.chr";
          sfd.AddExtension = true;
          sfd.RestoreDirectory = true;
          if (sfd.ShowDialog() == DialogResult.OK){
            saveFilePath = sfd.FileName;
          }
          sfd.Dispose();
        }

        if (saveFilePath != ""){
          try{
          var dir = saveFilePath.Substring(0,saveFilePath.Length - 4);
          var name = Path.GetFileName(saveFilePath);
          System.IO.Directory.CreateDirectory(dir);
          dir += "\\";

          using (var datawriter = new StreamWriter(dir + "1File.xml")) {
            using (var writer = new StreamWriter(dir + "0SpriteInfo")) {
              using (var spritewriter = new StreamWriter(dir + "2Sprite.xml")) {
                var saver = new XmlSerializer(typeof(List<PropertyGridCharacter>));
                var saver2 = new XmlSerializer(typeof(List<Sprite>));

                writer.Write(imageFilePath);
                writer.Write("\r\n" + curX);
                writer.Write("\r\n" + curY);
                saver.Serialize(datawriter, player.props);
                saver2.Serialize(spritewriter, player.sprites);
              }
            }
          }

          //now we win?
          DirectoryInfo di = new DirectoryInfo(dir);
          var final = new FileStream(saveFilePath, FileMode.Create);

          byte[] buffer = new byte[2000];
          int i = 0;
          string s;
          foreach( var f in di.GetFiles()){
            s = "" + i++ + "," + f.Name + "," + f.CreationTime + "," + f.Length + "\r\n";
            final.Write(StrToByteArray(s), 0, s.Length);
            var a = f.OpenRead();
            CopyStream(a,final);
            a.Close();
            s = "\r\n";
            final.Write(StrToByteArray(s),0,s.Length);
          }

          final.Dispose();


          var x = new FileInfo(saveFilePath);
          Compress(x);

          File.Delete(saveFilePath);
          //File.Move(saveFilePath, saveFilePath + "backup");
          File.Move(saveFilePath + ".gz", saveFilePath);

          Directory.Delete(dir.Substring(0,dir.Length - 1), true);
          }catch(Exception ex){
            Console.WriteLine(ex.Message);
            Console.WriteLine(ex.ToString());
          }
        }
      }
    }

    // C# to convert a string to a byte array.
    public static byte[] StrToByteArray(string str)
    {
        System.Text.UTF8Encoding  encoding=new System.Text.UTF8Encoding();
        return encoding.GetBytes(str);
    }


    private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
    {
      string a = saveFilePath;
      saveFilePath = "";
      Save_Click(sender, e);
      if (saveFilePath == ""){
        saveFilePath = a;
      }
    }


    private void Open_Click(object sender, EventArgs e)
    {
      OpenFileDialog sfd = new OpenFileDialog();
      sfd.DefaultExt = "chr";
      sfd.Filter = "Character File (*.chr)|*.chr";
      sfd.AddExtension = true;
      sfd.RestoreDirectory = true;

      if (sfd.ShowDialog() == DialogResult.OK) {
        try{
          var loadFilePath = sfd.FileName;

          var x = new FileInfo(loadFilePath);
          Decompress(x);

          string origName = x.FullName.Remove(x.FullName.Length -
              x.Extension.Length);

          player = new Player();

          var fileStream = new FileStream(origName,FileMode.Open);
          var reader = new StreamReader(fileStream);
          string line = reader.ReadLine();

          imageFilePath = reader.ReadLine();
          curX = Int32.Parse(reader.ReadLine());
          curY = Int32.Parse(reader.ReadLine());
          LoadPath(imageFilePath);

          line = reader.ReadLine();
          var numb = Int32.Parse(line.Split(',').Last());
          var buffer = new char[numb];
          reader.ReadBlock(buffer,0,numb);
          var stringBufffer = System.Text.UTF8Encoding.UTF8.GetString(System.Text.UTF8Encoding.UTF8.GetBytes(buffer));
          var stringReader = new StringReader(stringBufffer);
          
          var saver = new XmlSerializer(typeof(List<PropertyGridCharacter>));
          player.props = saver.Deserialize(stringReader) as List<PropertyGridCharacter>;


          line = reader.ReadLine();
          line = reader.ReadLine();
          numb = Int32.Parse(line.Split(',').Last());
          buffer = new char[numb];
          reader.ReadBlock(buffer,0,numb);
          stringBufffer = System.Text.UTF8Encoding.UTF8.GetString(System.Text.UTF8Encoding.UTF8.GetBytes(buffer));
          stringReader = new StringReader(stringBufffer);
          
          var saver2 = new XmlSerializer(typeof(List<Sprite>));
          var list = saver2.Deserialize(stringReader) as List<Sprite>;
          //player.sprites
          for(int i = 0; i < list.Count; i++){
            player.sprites[i].ID = list[i].ID;
            player.sprites[i].pos = list[i].pos;
            player.sprites[i].hitBoxes = list[i].hitBoxes;
          }

          saveFilePath = loadFilePath;
          LoadProperties();

          fileStream.Close();
          File.Delete(origName);
          MainGraphicPanel.Invalidate();
        }catch(Exception ex){
          MessageBox.Show("Error loading file");
          Console.WriteLine(ex.ToString());
        }
      }
      sfd.Dispose();
    }

    //  --------------------------- CopyStream ---------------------------
    /// <summary>
    ///   Copies data from a source stream to a target stream.</summary>
    /// <param name="source">
    ///   The source stream to copy from.</param>
    /// <param name="target">
    ///   The destination stream to copy to.</param>
    private static void CopyStream(Stream source, Stream target)
    {
        const int bufSize = 0x1000;
        byte[] buf = new byte[bufSize];
        int bytesRead = 0;
        while ((bytesRead = source.Read(buf, 0, bufSize)) > 0)
            target.Write(buf, 0, bytesRead);
    }// end:CopyStream()

    public static void Compress(FileInfo fi)
    {
      // Get the stream of the source file.
      using (FileStream inFile = fi.OpenRead()) {
        // Prevent compressing hidden and 
        // already compressed files.
        if ((File.GetAttributes(fi.FullName)
          & FileAttributes.Hidden)
          != FileAttributes.Hidden & fi.Extension != ".gz") {
          // Create the compressed file.
          using (FileStream outFile = 
                    			File.Create(fi.FullName + ".gz")) {
            using (GZipStream Compress = 
                        	new GZipStream(outFile,
              CompressionMode.Compress)) {
              // Copy the source file into 
              // the compression stream.
              inFile.CopyTo(Compress);

              Console.WriteLine("Compressed {0} from {1} to {2} bytes.",
                  fi.Name, fi.Length.ToString(), outFile.Length.ToString());
            }
          }
        }
      }
    }

    public static void Decompress(FileInfo fi)
    {
      // Get the stream of the source file.
      using (FileStream inFile = fi.OpenRead()) {
        // Get original file extension, for example
        // "doc" from report.doc.gz.
        string curFile = fi.FullName;
        string origName = curFile.Remove(curFile.Length -
            fi.Extension.Length);

        //Create the decompressed file.
        using (FileStream outFile = File.Create(origName)) {
          using (GZipStream Decompress = new GZipStream(inFile,
                  CompressionMode.Decompress)) {
            // Copy the decompression stream 
            // into the output file.
            Decompress.CopyTo(outFile);

            Console.WriteLine("Decompressed: {0}", fi.Name);

          }
        }
      }
    }

    private void ToggleHitbox_Click(object sender, EventArgs e)
    {
      MainGraphicPanel.Invalidate();
    }

    //PREPARE FOR HUGE FUNCTION SINCE THIS IS PRETTY MUCH THE EDITOR ITSELF SHOULD TRY TO KEEP THIS AT THE BOTTOM OF THE FILE
    private void propertyGrid1_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
    {
      if (player != null) {
        if (e.ChangedItem.Label == "DelayAnimation") {
          if (e.ChangedItem.Value.Equals(true))
            player.AddFrame(currentFrame);
          else
            player.RemoveFrame(currentFrame);
        }

        if (e.ChangedItem.Label == "BeginFrame"){
          string name = player.getName(currentFrame);
          if (name != null && name != ""){
            summaryBox.Remove(name);
            summaryBox.Add(name);
          }else{
            propertyGrid.BeginFrame = false;
            FrameNumber.Text = "Error: Attack Name Required";
          }
        }
      }

    }
  }

  public class Vector2{
    public Vector2(float X, float Y){
      this.X = X;
      this.Y = Y;
    }
    public float X,Y;
  }

}
