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
      AddAHB
    }

    System.Windows.Forms.Timer PlayAnimationTimer;
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
    private PropertyGridCharacter p;
    private  Summary SummaryBox;
    private  string saveFilePath;
    private  string imageFilePath;

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
      PlayAnimationTimer = new System.Windows.Forms.Timer();
      SummaryBox = new Summary();
      saveFilePath = "";
    }

    private void Form1_Load(object sender, EventArgs e)
    {
      p = new PropertyGridCharacter();
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
          imageFilePath = d.SelectedPath;

//TODO: DEBUG ONRY< REMOVE THIS
          imageFilePath="C:\\DEV\\Reimu";
//

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
      LoadProperties();
    }

    private void LoadProperties()
    {
      if (player != null){
        p = player.GetGrid(currentFrame);
        propertyGrid1.SelectedObject = p;
      }
    }

    private void SaveProperties()
    {
    }

    private void PrevFrame_Click(object sender, EventArgs e)
    {
      SaveProperties();
      UpdateFrame(currentFrame - 1);
      LoadProperties();
    }

    private void JumpTo_Click(object sender, EventArgs e)
    {
      SaveProperties();
      var frame = Int32.Parse(FrameMoveBox.Text);
      UpdateFrame(frame);
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
        if (SummaryBox == null)
          SummaryBox = new Summary(this);

        if (!SummaryBox.Visible){
          SummaryBox.Show();
        }else{
          SummaryBox.Hide();
        }
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
        if (PlayAnimationTimer.Enabled == false){

         // System.Threading.Timer t = null;
          StopAnimation = false;

          PlayAnimationTimer = new System.Windows.Forms.Timer();
          PlayAnimationTimer.Interval = 1000 / Int32.Parse(playspeed.Text);
          PlayAnimationTimer.Enabled = true;
          PlayAnimationTimer.Tick += new System.EventHandler((object sender2, EventArgs e2) => {

            if (p.JumpToImage != -1 && p.JumpToImage <= player.imageLength && p.JumpToImage > 1) {
              currentFrame = p.JumpToImage - 1;
            }
            
            if (!UpdateFrame(currentFrame + 1))
              PlayAnimationTimer.Enabled = false;;

          });

        }else{
          PlayAnimationTimer.Enabled = false;
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

      if (saveFilePath != "" && player != null){
        try{
        var dir = saveFilePath.Substring(0,saveFilePath.Length - 4);
        var name = Path.GetFileName(saveFilePath);
        System.IO.Directory.CreateDirectory(dir);
        dir += "\\";

        using (var datawriter = new StreamWriter(dir + "File.xml")) {
          using (var writer = new StreamWriter(dir + "SpriteInfo")) {
            using (var spritewriter = new StreamWriter(dir + "Sprite.xml")) {
              var saver = new XmlSerializer(typeof(List<PropertyGridCharacter>));
              var saver2 = new XmlSerializer(typeof(List<Sprite>));

              writer.Write(imageFilePath + "\r\n");
              saver.Serialize(datawriter, player.props);
             // saver2.Serialize(spritewriter, player.sprites);
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
          CopyStream(f.OpenRead(),final);
        }

        final.Dispose();


        var x = new FileInfo(saveFilePath);
        Compress(x);

        File.Delete(saveFilePath);
        File.Move(saveFilePath + ".gz", saveFilePath);

        Directory.Delete(dir.Substring(0,dir.Length - 1), true);
        }catch(Exception ex){
          Console.WriteLine(ex.Message);
        }
      }
    }

    // C# to convert a string to a byte array.
    public static byte[] StrToByteArray(string str)
    {
        System.Text.UTF8Encoding  encoding=new System.Text.UTF8Encoding();
        return encoding.GetBytes(str);
    }


    private void Open_Click(object sender, EventArgs e)
    {
      OpenFileDialog sfd = new OpenFileDialog();
      sfd.DefaultExt = "chr";
      sfd.Filter = "Character File (*.chr)|*.chr";
      sfd.AddExtension = true;
      sfd.RestoreDirectory = true;
      if (sfd.ShowDialog() == DialogResult.OK) {
        var loadFilePath = sfd.FileName;

        /*
        var saver = new XmlSerializer(typeof(List<PropertyGridCharacter>));
        var saver2 = new XmlSerializer(typeof(List<PropertyGridCharacter>));
        var reader = new StreamReader(loadFilePath);
        var datareader = new StreamReader(loadFilePath.Substring(0,loadFilePath.Length-4) + "Frame" + ".xml");
        var spritereader = new StreamReader(loadFilePath.Substring(0,loadFilePath.Length-4) + "Image" + ".xml");
        imageFilePath = reader.ReadLine();
        player = new Player();
        LoadPath(imageFilePath);
        player.props = (List<PropertyGridCharacter>)saver.Deserialize(datareader);
        reader.Close();
        datareader.Close();
         */
      }
      sfd.Dispose();

      if (saveFilePath != ""){
      }
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
            SummaryBox.Remove(name);
            SummaryBox.Add(name);
          }else{
            p.BeginFrame = false;
            FrameNumber.Text = "Error: Attack Name Required";
          }
        }
      }

    }


  }
}
