/// Input Buffer
/** 
 * - Input Delay
 * - Input Buffer
 * - Parses the buffer for the last command input
 */
class AsInputBuffer{

  private:
    //since there is 2 possible inputs per frame, a direction and a button we create 2 lists of input
    int nInputLUT[256];		 ///< Input lookup table, used when setting the key config

    int nDirection[20];		///< A buffer of input directions 
    int nAction[20];		///< A buffer of input buttons

    int nDirectionLocation;	//direction array index location
    int nActionLocation;	//action array index location

    //online config
    int nDelay;				///< Number of frames to delay the input (based on the ping time)

  public:

    //structors
    AsInputBuffer();
    ~AsInputBuffer();

    void pushInput(bool _input[256]);
    void SetTable(int _location, int _value);
    void SetTable(int _InputLUT[]);
};
