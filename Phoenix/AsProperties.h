#ifndef _ASPROPERTIES_H_
#define _ASPROPERTIES_H_

namespace PhoenixFight{

  struct sAttackProp
  {
    //Frame Data
    int		nHitStun;
    int		nBlockStun;
    int		nCounterHit;
    int		nStartup;
    int		nRecovery;
    int		nInvun;
    int		nThrowInvun;
    int		nSuperArmor;
    int		nAutoGaurd;

    //Damage!
    int		nDamage;

    //Gaurd Crush
    int		nGaurdLevel;
    int		nGaurdCrush;

    //Meter
    int		nMeterGained;
    int		nMeterCost;

    //Super Flash Object
    void*	pFlash;

    //Where it hits
    char	fHitAttribute;	//location of where it hits (head/mid/foot)
    char	fHitType;		//How it hits (high/mid/low) 0x0F = all 3

    //location of what it would invince
    char	fHitInvun;

    //Does it wallbounce or floorbounce?
    bool	bWallBounce;
    bool	bFloorBounce;

    //% of the prorate amount
    int		nProrate;

    //Character Specific
    int		nAspect;

  };


  struct sCharacterProp
  {
    //the amount of life a player has
    int		nLife;

    //gaurd data
    int		nGaurdType;
    int		nGaurd;

    //super bar
    int		nMeter;

    //character specific bars
    int		nAspect;
    int		nInstall;

    //proration information
    int		nProrate;
    int		nComborate;

    //weight value (if applicable)
    int		nWeight;
  };
}

#endif