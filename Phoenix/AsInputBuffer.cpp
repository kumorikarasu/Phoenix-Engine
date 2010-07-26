#include "PhoenixModules.h"
#include "AsInputBuffer.h"

using namespace PhoenixFight;

/**
 * @param _input a bool array of input 256 values, corrosponding with the ascii value
 *
 * takes the input and adds it to the buffer
 */
void AsInputBuffer::pushInput(bool _input[256])
{
  nDirection[nDirectionLocation] = 5; //set the input to 5 (nuetral stick

  for (int i=0;i<256;i++){ //go throught every single possible input
    if (_input[i] == 1){ //check if that input is set
      if (nInputLUT[i] > 10){ //check if that input is a button press
        //SetTable(nAction[nActionLocation], nInputLUT[i]);
        nAction[nActionLocation] = nInputLUT[i];

      }else if (nInputLUT[i] > 0){ //check if that input is a directional input
        nDirection[nDirectionLocation] = nInputLUT[i];

      }
    }
  }

  nActionLocation ++; //increment the counters
  nDirectionLocation ++;

  //if the counters overflowed, reset them to 0
  if (nDirectionLocation == 20)
    nDirectionLocation = 0;
  if (nActionLocation == 20)
    nActionLocation = 0;
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
  nInputLUT = _InputLUT;
}


AsInputBuffer::AsInputBuffer()
{


}

AsInputBuffer::~AsInputBuffer()
{

}

AsInputBuffer::Decompile(char* packet){

}

char* AsInputBuffer::Compile(){

}