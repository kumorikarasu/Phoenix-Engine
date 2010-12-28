using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Xml.Serialization;

namespace HitBox_Editor
{
  [Serializable]
  public class HitBox{
    public int x, y, xx, yy;
    public int type;
    public bool selected;
    public int xoff,yoff;
    const int DRAWSIZE = 3;
    const int CHECKSIZE = 5;

    [XmlIgnore]
    private int xset,yset;

    public HitBox(){

    }

    public HitBox(Sprite par, Point p){
      xoff = p.X;
      yoff = p.Y;
    }

    internal void Draw(Graphics g, Point Cur)
    {
      SolidBrush myBrush;
      Pen myPen;

      if (type == 0){
        myBrush = new System.Drawing.SolidBrush(Color.FromArgb(128,0,255,0));
        myPen = new Pen(Color.FromArgb(128,0,255,0));
      }else{ 
        myBrush = new System.Drawing.SolidBrush(Color.FromArgb(128,255,0,0));
        myPen = new Pen(Color.FromArgb(128,255,0,0));
      }
      int bx = x, by = y, bxx = xx, byy = yy;
      x += xset = (Cur.X - xoff) / 2;
      y += yset = (Cur.Y - yoff) / 2;
      xx += xset;
      yy += yset;

      if (xx > x && yy > y)
        g.FillRectangle(myBrush,x, y, xx - x, yy - y);
      if (x > xx && yy > y)
        g.FillRectangle(myBrush,xx, y, x - xx, yy - y);
      if (xx > x && y > yy)
        g.FillRectangle(myBrush,x, yy, xx - x, y - yy);
      if (x > xx && y > yy)
        g.FillRectangle(myBrush,xx, yy, x - xx, y - yy);


      if (selected){
        var width = xx - x;
        var height = yy - y;
        width /= 2;
        height /= 2;

        g.DrawRectangle(myPen, x - DRAWSIZE, y - DRAWSIZE, DRAWSIZE * 2, DRAWSIZE * 2);
        g.DrawRectangle(myPen, x - DRAWSIZE, yy - DRAWSIZE, DRAWSIZE * 2, DRAWSIZE * 2);
        g.DrawRectangle(myPen, xx - DRAWSIZE, y - DRAWSIZE, DRAWSIZE * 2, DRAWSIZE * 2);
        g.DrawRectangle(myPen, xx - DRAWSIZE, yy - DRAWSIZE, DRAWSIZE * 2, DRAWSIZE * 2);
        g.DrawRectangle(myPen, x + width - DRAWSIZE, y - DRAWSIZE, DRAWSIZE * 2, DRAWSIZE * 2);
        g.DrawRectangle(myPen, x - DRAWSIZE, y + height - DRAWSIZE, DRAWSIZE * 2, DRAWSIZE * 2);
        g.DrawRectangle(myPen, x + width - DRAWSIZE, yy - DRAWSIZE, DRAWSIZE * 2, DRAWSIZE * 2);
        g.DrawRectangle(myPen, xx - DRAWSIZE, y + height - DRAWSIZE, DRAWSIZE * 2, DRAWSIZE * 2);
      }

      myBrush.Dispose();
      x = bx;
      y = by;
      xx = bxx;
      yy = byy;
    }

    internal void Correct()
    {
      int bx = x, by = y, bxx = xx, byy = yy;
      x += xset;
      y += yset;
      xx += xset;
      yy += yset;

      if (xx < x){
        int tx = x;
        x = xx;
        xx = tx;
      }
      if (yy < y){
        int ty = y;
        y = yy;
        yy = ty;
      }

      x = bx;
      y = by;
      xx = bxx;
      yy = byy;
    }

    internal int CheckCorners(Point p)
    {
      int returnval = -1;
      int bx = x, by = y, bxx = xx, byy = yy;
      x += xset;
      y += yset;
      xx += xset;
      yy += yset;

      var width = xx - x;
      var height = yy - y;
      width /= 2;
      height /= 2;

      if (p.X < x + CHECKSIZE && p.X > x - CHECKSIZE && p.Y < y + CHECKSIZE && p.Y > y - CHECKSIZE)
        returnval =  7;
      else
      if (p.X < xx + CHECKSIZE && p.X > xx - CHECKSIZE && p.Y < yy + CHECKSIZE && p.Y > yy - CHECKSIZE)
        returnval =  3;
      else
      if (p.X < xx + CHECKSIZE && p.X > xx - CHECKSIZE && p.Y < y + CHECKSIZE && p.Y > y - CHECKSIZE)
        returnval = 9;
      else
      if (p.X < x + CHECKSIZE && p.X > x - CHECKSIZE && p.Y < yy + CHECKSIZE && p.Y > yy - CHECKSIZE)
        returnval = 1;
      else
      if (p.X < x + width + CHECKSIZE && p.X > x + width - CHECKSIZE && p.Y < yy + CHECKSIZE && p.Y > yy - CHECKSIZE)
        returnval =  2;
      else
      if (p.X < x + width + CHECKSIZE && p.X > x + width - CHECKSIZE && p.Y < y + CHECKSIZE && p.Y > y - CHECKSIZE)
        returnval = 8;
      else
      if (p.X < x + CHECKSIZE && p.X > x - CHECKSIZE && p.Y < y + height + CHECKSIZE && p.Y > y + height - CHECKSIZE)
        returnval =  4;
      else
      if (p.X < xx + CHECKSIZE && p.X > xx - CHECKSIZE && p.Y < y + height + CHECKSIZE && p.Y > y + height - CHECKSIZE)
        returnval = 6;

      x = bx;
      y = by;
      xx = bxx;
      yy = byy;

      return returnval;
    }

    internal bool CheckCollision(Point p)
    {
      int bx = x, by = y, bxx = xx, byy = yy;
      x += xset;
      y += yset;
      xx += xset;
      yy += yset;

      var returnval = p.X > x && p.X < xx && p.Y > y && p.Y < yy;

      x = bx;
      y = by;
      xx = bxx;
      yy = byy;

      return returnval;
    }
  }

  [Serializable]
  public class Sprite{
    [XmlIgnoreAttribute]
    public Image image;

    public Rectangle pos {get; set;}
    public long ID {get; set;}
    public List<HitBox> hitBoxes;

    public Sprite(){
      pos = new Rectangle(0,0,0,0);
      hitBoxes = new List<HitBox>();
    }
  }

  public class Player
  {
    public List<Sprite> sprites;
    public List<PropertyGridCharacter> props;
    public int imageLength { get; set; }
    long IDCount;

    public Player(){
      sprites = new List<Sprite>();
      props = new List<PropertyGridCharacter>();
      imageLength = 0;
      IDCount = 0;
    }

    ~Player(){
      foreach (var i in sprites){
        i.image.Dispose();
      }
    }

    //adds a frame
    public void AddFrame(int Frame){
      Sprite sp = sprites[Frame];
      sp.ID = ++IDCount;
      sprites.Insert(Frame + 1, sp);
      props.Insert(Frame + 1, new PropertyGridCharacter());
      imageLength++;
    }

    //removes the current frame
    public void RemoveFrame(int FrameNumber){
      sprites.RemoveAt(FrameNumber + 1);
      props.RemoveAt(FrameNumber + 1);
      imageLength--;
    }

    internal Image GetImage(int Frame){
      if (sprites != null){
        return sprites[Frame].image;
      }
      return null;
    }

    public void LoadImage(string path){
      var i = new Bitmap(path);
      var s = new Sprite();
      s.image = i;
      s.pos = new Rectangle(0,0,i.Width,i.Height);
      s.ID = ++IDCount;
      sprites.Add(s);
      props.Add(new PropertyGridCharacter());
      imageLength++;
    }

    internal PropertyGridCharacter GetGrid(int p)
    {
      return props[p];
    }

    internal string getName(int currentFrame)
    {
      return props[currentFrame].Name;
    }
  }
}
