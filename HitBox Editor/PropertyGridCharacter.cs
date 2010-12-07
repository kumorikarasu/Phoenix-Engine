using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace HitBox_Editor
{
  [DefaultPropertyAttribute("Name")]
  public class PropertyGridCharacter
  {
    public PropertyGridCharacter()
    {
      Spawn = "";
    }


    [System.ComponentModel.Editor(
      typeof(FileProperty),
      typeof(System.Drawing.Design.UITypeEditor)),
    CategoryAttribute("Frame"), DescriptionAttribute("Spawn an object on this frame")]
    public string Spawn { get; set; }

    [CategoryAttribute("Frame"), DescriptionAttribute("The X Cordinate to spawn it, relative to you")]
    public int SpawnX { get; set; }

    [CategoryAttribute("Frame"), DescriptionAttribute("The Y Cordinate to spawn it, relative to you")]
    public int SpawnY { get; set; }

    [CategoryAttribute("Frame"), DescriptionAttribute("Move the player X pixels at the start of this frame")]
    public int MoveX { get; set; }

    [CategoryAttribute("Frame"), DescriptionAttribute("Move the player Y pixels at the start of this frame")]
    public int MoveY { get; set; }

    [CategoryAttribute("Frame"), DescriptionAttribute("Total number of frames - when this is set, the next X number of frames are part of this animation, and this value cannot be changed")]
    public int TotalFrames { get; set; }

    [CategoryAttribute("Frame"), DescriptionAttribute("Autoguard hit")]
    public bool AutoGuard { get; set; }

    [CategoryAttribute("Frame"), DescriptionAttribute("Head Invincible")]
    public bool HeadInvincible { get; set; }

    [CategoryAttribute("Frame"), DescriptionAttribute("Body Invincible")]
    public bool BodyInvincible { get; set; }

    [CategoryAttribute("Frame"), DescriptionAttribute("Foot Invincible")]
    public bool FootInvincible { get; set; }

    [CategoryAttribute("Frame"), DescriptionAttribute("Projectile Invincible")]
    public bool ProjectileInvincible { get; set; }

    [CategoryAttribute("Frame"), DescriptionAttribute("Projectile Guard - Takes a hit but receives no damage")]
    public bool ProjectileGuard { get; set; }

    [CategoryAttribute("Frame"), DescriptionAttribute("Receives zero hitstun from all attacks")]
    public bool SuperArmor { get; set; }

    [CategoryAttribute("Frame"), DescriptionAttribute("Clash, special animation if it meets another attack or clash hitbox and removes hitboxes from both attacks")]
    public bool Clash { get; set; }

    [CategoryAttribute("Frame"), DescriptionAttribute("False Roman Cancel - Allows you to cancel the attack on this frame")]
    public bool FalseRomanCancel { get; set; }

    [CategoryAttribute("Frame"), DescriptionAttribute("EX attacks only, freezes the screen, may have other special animations such as darkened background")]
    public bool Superflash { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Name of the attack")]
    public string Name { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Attack level, you describe this.  I had thought it determined hitstun and blockstun but it seems you have separate values for them")]
    public int Level { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Amount of damage the attack will deal")]
    public int Damage { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Minimum amount of damage the attack will do if it hits no matter what proration is set at.")]
    public int MinimumDamage { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Damage the attack will do even if the opponent is blocking")]
    public int ChipDamage { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Damage the attack will do a guard bar")]
    public int GuardDamage { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Proration, the percentage the following hits will be reduced to.")]
    public int Proration { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Amount of frames opponent will be in blockstun if this attack is guarded")]
    public int Blockstun { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Amount of frames opponent will be in hitstun if this attack connects")]
    public int Hitstun { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Amount of meter the attack gives the character")]
    public int Metergain { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Amount of meter the attack costs to use.")]
    public int Metercost { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Grab, connects whether the opponent is blocking or not")]
    public bool Grab { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("High, hits if the opponent is guarding low")]
    public bool High { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Low, hits if the opponent is guarding high")]
    public bool Low { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Unblockable only if the opponent is in the air")]
    public bool AirUnblockable { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Unblockable in all instances")]
    public bool Unblockable { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Can cancel the recovery frames of the attack into a jump")]
    public bool JumpCancelable { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Can cancel the recovery frames of the attack into another attack")]
    public bool AttackCancelable { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("Total number of frames the oponent is frozen and cannot do anything")]
    public int FreezeFrames { get; set; }

    [CategoryAttribute("Attack"), DescriptionAttribute("The sequence of characters used to detect this attack being pressed")]
    public string MoveInput { get; set; }

    [CategoryAttribute("Animation"), DescriptionAttribute("Delay the animation, meaning the next frame will have the same image")]
    public bool DelayAnimation { get; set; }

    [CategoryAttribute("Animation"), DescriptionAttribute("Jumps to a specified image number")]
    public int JumpToImage { get; set; }
  }
}
