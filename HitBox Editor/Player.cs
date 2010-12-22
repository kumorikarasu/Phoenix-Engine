using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Drawing2D;

namespace HitBox_Editor
{
  public class Sprite{
    public Image image;
    public Rectangle pos {get; set;}
    public long ID {get; set;}

    public Sprite(){
      pos = new Rectangle(0,0,0,0);
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
