#ifndef _ASINPUTBUFFER_H_
#define _ASINPUTBUFFER_H_

namespace PhoenixFight{

  /// Input Buffer
  /** 
  * - Input Delay
  * - Input Buffer
  * - Parses the buffer for the last command input
  */

  enum Input{
    //Buttons (20 possible buttons)
    BUTTON_A      = 0x01,
    BUTTON_B      = 0x02,
    BUTTON_C      = 0x04,
    BUTTON_D      = 0x08,
    BUTTON_E      = 0x10,
    BUTTON_F      = 0x20,
    BUTTON_G      = 0x40,
    BUTTON_H      = 0x80,
    BUTTON_COIN   = 0x40000,
    BUTTON_START  = 0x80000, //highest possible input button

    //Directions (12 possible directions)
    DIRECTION_7   = 0x00100000,
    DIRECTION_8   = 0x00200000,
    DIRECTION_9   = 0x00400000,

    DIRECTION_4   = 0x00800000,
    DIRECTION_5   = 0x01000000,
    DIRECTION_6   = 0x02000000,

    DIRECTION_1   = 0x04000000,
    DIRECTION_2   = 0x08000000,
    DIRECTION_3   = 0x10000000
  };

  class AsInputBuffer
  {
  private:
    static const int nMaxFrames = 20;      ///< Input buffer length
    static const int nNumberofButtons = 7; ///< Number of input buttons (A,B,C,D,E,F and S)

    unsigned int nInputLUT[256];		  ///< Input lookup table, used when setting the key config

    long* nInput;   		    ///< A buffer of input directions (circular array)
    int   nInputLocation;	  //input array index location 

    //online config
    int nDelay;				      ///< Number of frames to delay the input (based on the ping time)
    int nFrame;             ///< Number of frames we compile to, will keep this the same as the delay value for now

  public:

    //structors
    AsInputBuffer();
    ~AsInputBuffer();

    void pushInput(bool _input[256]);
    long popInput();
    void SetTable(int _location, int _value);
    void SetTable(int _InputLUT[]);
    char* Compile();
    void Decompile(char[]);
    int  ParseInput(int _currentInput, bool _input[256]);
  };
}

#endif
