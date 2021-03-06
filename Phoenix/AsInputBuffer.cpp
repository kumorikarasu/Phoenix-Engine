#include <cstdlib>
#include <cstring>

#include "AsInputBuffer.h"


namespace PhoenixFight{

/**
 * @param _input a bool array of input 256 values, corrosponding with the ascii value
 *
 * takes the input and adds it to the buffer
 */
void AsInputBuffer::pushInput(bool _input[256])
{
  nInput[nInputLocation] = ParseInput(DIRECTION_5, _input);
  //nInput[0] = ParseInput(DIRECTION_5, _input);

  //increment the counters
  nInputLocation ++;

  //if the counters overflowed, reset them to 0
  if (nInputLocation >= this->nMaxFrames - 1)
    nInputLocation = 0;
}

/**
 * @param input a bool array of input 256 values, corrosponding with the ascii value
 * @param value what to set the table value to, by default it is 0
 * 
 * Sets the table to the corosponding value
 */
void AsInputBuffer::SetTable(int _location, int _value = 0)
{
  nInputLUT[_location] = _value;
}

/**
 * @param an array the same size as the default look up table
 *
 * sets the lookup table to a new one
 */
void AsInputBuffer::SetTable(int _InputLUT[])
{
  //nInputLUT = _InputLUT;
}


AsInputBuffer::AsInputBuffer()
{
  nInput = new long[nMaxFrames];
  nInputLocation = 0;
  memset(nInputLUT,0,255 * sizeof(int));
  memset(nInput,0,nMaxFrames * sizeof(long));
  memset(nInputTable, 0, 20 * sizeof(int));
}

AsInputBuffer::~AsInputBuffer()
{
  delete nInput;
}

void AsInputBuffer::Decompile(char* packet){

}

char* AsInputBuffer::Compile(){

  return 0;
}

/** PraseInput
 *
 * @param _currentInput nutral state, so direction 5 normally
 * @param _input[256] The buffer of inputs from windows
 * @return The int with all the input data for that frame
 */
int AsInputBuffer::ParseInput(int _currentInput, bool _input[256]){
  int result = _currentInput;
  for (int i=0;i<32;i++){
    if (_input[nInputTable[i]] == 1){
      if (nInputLUT[i]){
      result = result | nInputLUT[i];
      }
    }
  }

  return result;
}


long AsInputBuffer::popInput()
{
  return nInput[0];
}

};