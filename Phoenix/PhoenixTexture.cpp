#include "PhoenixGlobal.h"
#include "PhoenixTexture.h"
#include "PhoenixConsole.h"
#include <tchar.h>
#include <atlconv.h>

using namespace std;
namespace PhoenixCore{

  /*int PhTextureManager::LoadTextureTGA(const std::string &_filename, PhTexture *_pTexture)
  {

  FILE *pFile = NULL;

  if(!_filename.compare(""))
  return false;

  std::string path = "data\\textures\\";
  path.append(_filename);

  pFile = fopen(path.c_str(),"rb");

  if( !pFile )
  {
  PhConsole::C()->Line("Could not open texture %s",C_WARNING,_filename.c_str());
  return false;
  }

  // Uncompressed TGA Header
  char uTGAcompare[12] = {0,0, 2,0,0,0,0,0,0,0,0,0};
  // Compressed TGA Header
  char cTGAcompare[12] = {0,0,10,0,0,0,0,0,0,0,0,0};

  char tgaHeader[12] = {0};
  char header[6];

  if (fread(&tgaHeader, sizeof(tgaHeader), 1, pFile) == 0){
  PhConsole::C()->Line("Could not read texture %s",C_WARNING,_filename.c_str());
  return false;
  }

  if (memcmp(uTGAcompare, tgaHeader, sizeof(tgaHeader)) == 0){
  //load uncompressed TGA

  // Attempt To Read Next 6 Bytes
  if(fread(header, sizeof(header), 1, pFile) == 0)
  {										
  PhConsole::C()->Line("Could not read texture %s",C_WARNING,_filename.c_str());
  return false;				// Return False
  }
  _pTexture->m_width = header[1] * 256 + header[0];
  _pTexture->m_height = header[3] * 256 + header[2];
  _pTexture->m_bpp = header[4];

  if (!  ((_pTexture->m_bpp == 24 || _pTexture->m_bpp == 32) && _pTexture->m_width > 0 && _pTexture->m_height > 0)){
  PhConsole::C()->Line("Invalid Texture %s",C_WARNING,_filename.c_str());
  return false;				// Return False
  }

  if(_pTexture->m_bpp == 24)				// Is It A 24bpp Image?
  _pTexture->m_type	= 0x1907;		// If So, Set Type To GL_RGB
  else									// If It's Not 24, It Must Be 32
  _pTexture->m_type	= 0x1908;		// So Set The Type To GL_RGBA

  int	bytesPerPixel = _pTexture->m_bpp / 8;
  int	imageSize = bytesPerPixel * _pTexture->m_height * _pTexture->m_width;

  _pTexture->m_data = new char[imageSize];

  if (_pTexture->m_data == NULL){
  PhConsole::C()->Line("Out Of Memory %s",C_ERROR,_filename.c_str());
  return false;				// Return False
  }

  if (fread(_pTexture->m_data, 1, imageSize, pFile) != imageSize){
  PhConsole::C()->Line("Could not read texture %s",C_WARNING,_filename.c_str());
  return false;				// Return False
  }	

  //Switch the 1st and 3rd byte to make it RGB instead of BGR
  for(int cswap = 0; cswap < (int)imageSize; cswap += bytesPerPixel)
  {
  // 1st Byte XOR 3rd Byte XOR 1st Byte XOR 3rd Byte
  _pTexture->m_data[cswap] ^= _pTexture->m_data[cswap+2] ^=
  _pTexture->m_data[cswap] ^= _pTexture->m_data[cswap+2];
  }


  }else if (memcmp(cTGAcompare, tgaHeader, sizeof(tgaHeader)) == 0){ //FUCK COMPRESSED TGA, FUCK IT ALL TO HELL
  //load compressed TGA
  /*
  // Attempt To Read Next 6 Bytes
  if(fread(header, sizeof(header), 1, pFile) == 0)
  {										
  PhConsole::C()->Line("Could not read texture %s",C_WARNING,_filename.c_str());
  return false;				// Return False
  }
  _pTexture->m_width = header[1] * 256 + header[0];
  _pTexture->m_height = header[3] * 256 + header[2];
  _pTexture->m_bpp = header[4];

  if (!  ((_pTexture->m_bpp == 24 || _pTexture->m_bpp == 32) && _pTexture->m_width > 0 && _pTexture->m_height > 0)){
  PhConsole::C()->Line("Invalid Texture %s",C_WARNING,_filename.c_str());
  return false;				// Return False
  }

  if(_pTexture->m_bpp == 24)				// Is It A 24bpp Image?
  _pTexture->m_type	= 0x1907;		// If So, Set Type To GL_RGB
  else									// If It's Not 24, It Must Be 32
  _pTexture->m_type	= 0x1908;		// So Set The Type To GL_RGBA

  int	bytesPerPixel = _pTexture->m_bpp / 8;
  int	imageSize = bytesPerPixel * _pTexture->m_height * _pTexture->m_width;

  _pTexture->m_data = new char[imageSize];

  if (_pTexture->m_data == NULL){
  PhConsole::C()->Line("Out Of Memory %s",C_ERROR,_filename.c_str());
  return false;				// Return False
  }

  int pixelcount = _pTexture->m_height * _pTexture->m_width;
  int currentpixel = 0;
  int currentbyte = 0;

  //alloc some room for each pixel as we uncompress it
  int* colorbuffer = malloc(bytesPerPixel);


  do{ //uncompressing fun (i don't understand wtf im doing eather)
  int chunkheader = 0;
  if (fread(&chunkheader,sizeof(int), 1, pFile) == 0){
  PhConsole::C()->Line("Could not read texture %s",C_WARNING,_filename.c_str());
  return false;				// Return False
  }
  if (chunkheader < 128){
  chunkheader ++;

  for (short i = 0; i < chunkheader; i++){
  if (fread(colorbuffer, 1, bytesPerPixel, pFile) != bytesPerPixel){
  PhConsole::C()->Line("Could not read texture %s",C_WARNING,_filename.c_str());
  return false;				// Return False
  }
  _pTexture->m_data[currentbyte] = colorbuffer[2]; // R
  _pTexture->m_data[currentbyte + 1] = colorbuffer[1]; //G
  _pTexture->m_data[currentbyte + 2] = colorbuffer[0]; //B
  if (bytesPerPixel == 4) //A
  _pTexture->m_data[currentbyte + 3] = colorbuffer[3]; //A

  currentbyte += bytesPerPixel;
  currentpixel++;

  }
  }else{
  chunkheader -= 127;
  //if its RLE type
  ....

  }while(....

  */
  /*
  return false; //we don't load these yet :|
  }


  //init the texture with OGL
  pRenderer->BindTexture(_pTexture);

  return true;
  }
  */

  //checks if the texture has be loaded already, if it has, it returns it, otherwise it attempts to load it
  PhTexture* PhTextureManager::Texture(TCHAR* _filename)
  {

    //the texture pointer we will return
    PhTexture* pTexture = NULL;

    // check if the texture already exists in the map
    map<wstring,PhTexture*>::iterator p = m_TextureMap.find(wstring(_filename));

    if( p != m_TextureMap.end() )
    {
      // found the texture, now return the reference
      pTexture = p->second;
      pTexture->m_iRefCount++;

      return pTexture;
    }

    //if texture doesn't exist in the map, load it into memory
    pTexture = new PhTexture();

    //create another function to determine what type of texture it is, currently just support uncompressed TGA
    glTexture tex;
    if (! TL->LoadTextureFromDisk(_filename,&tex)){
      PhConsole::Console->Line(_T("Unable to load %s"),C_ERROR,_filename);
      delete pTexture;
      return  NULL;
    }else{
      pTexture->m_bpp = tex.Bpp;
      pTexture->m_height = tex.Height;
      pTexture->m_id = tex.TextureID;
      pTexture->m_type = tex.Type;
      pTexture->m_texType = tex.TexType;
      pTexture->m_width = tex.Width;
    }

    //add texture to map
    m_TextureMap[_filename] = pTexture;

    //return the texture pointer
    return pTexture;

  }

  PhTextureManager::~PhTextureManager()
  {

    //delete all textures that have been loaded
    map<wstring,PhTexture*>::iterator iter = m_TextureMap.begin();
    glTexture tex;

    while(iter != m_TextureMap.end()){
      tex.Bpp = iter->second->GetBpp();
      tex.Height = iter->second->GetHeight();
      tex.TextureID = iter->second->GetTextureId();
      tex.TexType = iter->second->m_texType;
      tex.Type = iter->second->m_type;
      tex.Width = iter->second->GetWidth();
      TL->FreeTexture(&tex);
      iter++;
    }

    //clear the array
    this->m_TextureMap.empty();
    delete TL;
  }

  PhTextureManager::PhTextureManager(PhConsole* _pConsole, PhIRenderer* _pRenderer)
  {
    pRenderer = _pRenderer;

    TL = new TextureLoader();
    TL->SetAlphaMatch(true,0,120,136);
    TL->SetHighQualityTextures(true);
  }

};