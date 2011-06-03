#include <vector>
#include "PhoenixDataFactory.h"

namespace PhoenixCore
{

  IRenderer* DataFactory::GD = NULL;

  bool DataFactory::loadPngImage(const wchar_t *name, int &outWidth, int &outHeight, int &outBpp, bool &outHasAlpha, unsigned char **outData) {
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE *fp;

    if ((fp = _wfopen(name, L"rb")) == NULL)
      return false;

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
      NULL, NULL, NULL);

    if (png_ptr == NULL) {
      fclose(fp);
      return false;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
      fclose(fp);
      png_destroy_read_struct(&png_ptr, NULL, NULL);
      return false;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
      png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
      fclose(fp);
      return false;
    }

    png_init_io(png_ptr, fp);

    png_set_sig_bytes(png_ptr, sig_read);

    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

    outWidth = png_get_image_width(png_ptr, info_ptr);
    outHeight = png_get_image_height(png_ptr, info_ptr);
    outBpp = png_get_bit_depth(png_ptr, info_ptr) / 2;
    switch (png_get_color_type(png_ptr, info_ptr)) {
    case PNG_COLOR_TYPE_RGBA:
      outHasAlpha = true;
      break;
    case PNG_COLOR_TYPE_RGB:
      outHasAlpha = false;
      break;
    default:
      png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
      fclose(fp);
      return false;
    }
    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    *outData = (unsigned char*) malloc(row_bytes * outHeight);

    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    for (int i = 0; i < outHeight; i++) {
      memcpy(*outData+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    fclose(fp);

    return true;
  }
  /*
  {
  std::string str = path.substr(path.find_last_of("."));
  if (str.compare("png") || str.compare("jpg") || str.compare("gif") || str.compare("tga") || str.compare("bmp"))
  {
  LoadResource<Texture>(key);
  }
  }

  template<> void* Resource::LoadResource<Texture>(std::string path)
  {
  return NULL;
  }
  */
  bool DataFactory::loadObjModel(const wchar_t *name, std::vector<V3>& vertex, std::vector<VI3>& indexes)
  {
    char buffer[257]; //if a line is bigger then this, then we crash, :D
    FILE* fp = _wfopen(name, L"rb");
    if (fp != NULL){
      while (1){
        if (fgets(buffer, 256, fp) == NULL)
          break;
        char* buffers = buffer;
        char* num1, *num2, *num3;
        switch (*buffer){
        case 'v':
          V3 v;
          num1 = buffer + 2;
          num2 = num1;
          while(*num2 != 32) num2++; //move to space
          *num2 = 0; num2++; //set space to null, move up
          num3 = num2;
          while(*num3 != 32) num3++; //move to space
          *num3 = 0; num3++; //set space to null, move up
          float c;
          v.x = atof(num1);
          v.y = atof(num2);
          v.z = atof(num3);
          vertex.push_back(v);
          break;
        case 'f':
          VI3 vi;
          num1 = buffer + 2;
          num2 = num1;
          while(*num2 != 32) num2++; //move to space
          *num2 = 0; num2++; //set space to null, move up
          num3 = num2;
          while(*num3 != 32) num3++; //move to space
          *num3 = 0; num3++; //set space to null, move up
          vi.x = atoi(num1);
          vi.y = atoi(num2);
          vi.z = atoi(num3);
          indexes.push_back(vi);
        }
      }
      return true;
    }

    fclose(fp);
    return false;
  }


};

    /*
      png_struct* png;
      png_info* png_info;
      unsigned int sig_read = 0;
      char header[8];

      png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
      if (!png){
        fclose(fp);
        return NULL;
      }

      png_info = png_create_info_struct(png);
      if (!png){
        fclose(fp);
        png_destroy_read_struct(&png, NULL, NULL);
        return NULL;
      }

      if (setjmp(png_jmpbuf(png))){
        fclose(fp);
        png_destroy_read_struct(&png, NULL, NULL);
        return NULL;
      }

      png_init_io(png, fp);
      png_set_sig_bytes(png, sig_read);
      png_read_png(png, png_info, PNG_TRANSFORM_STRIP_16 |
        PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

      tex = new Texture<imagetype>();
      if (!tex)
        return NULL;

      tex->width = png_get_image_width(png, png_info);
      tex->height = png_get_image_height(png, png_info);
      int c = png_get_color_type(png, png_info);
      tex->bpp = png_get_bit_depth(png, png_info);
    }

    /*
    png_init(0,0);
    png_t* png = (png_t*) malloc(sizeof(png_t));
    if (png_open_file_read(png, path.c_str()) != ::PNG_NO_ERROR){
    return NULL;
    }


    Texture<imagetype>* tex = new Texture<imagetype>();
    tex->width = png->width;
    tex->height = png->height;
    tex->bpp = png->bpp;

    imagetype* dat = (imagetype*)malloc(sizeof(imagetype) * tex->width * tex->height * tex->bpp);
    memcpy(dat, png->png_data, png->png_datalen);
    tex->data = dat;
    /*
    CImg<imagetype> image = CImg<imagetype>(path.c_str());
    tex->width = image.width();
    tex->height = image.height();
    tex->bpp = image.spectrum();
    tex->data = image.data();

    int sizeperblock = (tex->width * tex->height / tex->bpp);
    imagetype* dat = (imagetype*)malloc(sizeof(imagetype) * tex->width * tex->height * tex->bpp);
    imagetype* sdat = dat;
    if (tex->bpp == 3)
    for(int x = 0;x < sizeperblock; x++){
    *dat++ = *(tex->data + x);
    *dat++ = *(tex->data + sizeperblock + x);
    *dat++ = *(tex->data + sizeperblock * 2 + x);
    }
    else if (tex->bpp == 4){
    for(int x = 0;x < sizeperblock; x++){
    *dat++ = *(tex->data + x);
    *dat++ = *(tex->data + sizeperblock + x);
    *dat++ = *(tex->data + sizeperblock * 2 + x);
    *dat++ = *(tex->data + sizeperblock * 3 + x);
    }
    }

    tex->data = image.data();//sdat;
    GD->BuildTexture(tex);

    //free(sdat);
    //*/
    //free(png);
    // return tex;