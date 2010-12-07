using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Drawing2D;

namespace HitBox_Editor
{
  class Sprite{
    public Image image;
    public Rectangle pos;

    public Sprite(){
      pos = new Rectangle(0,0,0,0);
    }
  }

  public class Player
  {
    List<Sprite> sprites;
    
    List<PropertyGridCharacter> props;
    public int imageLength { get; set; }

    public Player(){
      sprites = new List<Sprite>();
      imageLength = 0;
    }

    ~Player(){
      foreach (var i in sprites){
        i.image.Dispose();
      }
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
      s.pos.Width = i.Width;
      s.pos.Height = i.Height;
      sprites.Add(s);
      imageLength++;
    }
  }
}
