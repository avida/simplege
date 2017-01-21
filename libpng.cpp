#include "libpng.hpp"
#include <png.h>
#include <string>
#include <stdio.h>
#include "utils/logger.hpp"

LibPng::LibPng(std::string path):m_path(path)
{
}

LibPng::~LibPng()
{
   delete[] row_pointers;
}

int LibPng::Load(const std::string path)
{
   m_path = path;
   return Load();
}

int LibPng::Load()
{
   
   png_structp png_ptr;
   png_infop info_ptr;
   int number_of_passes;

   char header[8];   // 8 is the maximum size that can be checked

   /* open file and test for it being a png */
   gl::Log(boost::format("will be loaded %1%") % m_path);
   FILE *fp = fopen(m_path.c_str(), "rb");
   if (!fp)
   {
       gl::Log(boost::format("[read_png_file] File %1% could not be opened for reading") % m_path);
       return 1;
   }
   fread(header, 1, 8, fp);
   if (png_sig_cmp((png_bytep)header, 0, 8))
   {
         gl::Log(boost::format("[read_png_file] File %1% is not recognized as a PNG file") % m_path);
       return 1;
   }


   /* initialize stuff */
   png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

   if (!png_ptr)
   {
         gl::Log("[read_png_file] png_create_read_struct failed");
       return 1;
   }

   info_ptr = png_create_info_struct(png_ptr);
   if (!info_ptr)
   {
       gl::Log("[read_png_file] png_create_info_struct failed");
       return 1;
   }

   if (setjmp(png_jmpbuf(png_ptr)))
   {
       gl::Log("[read_png_file] Error during init_io");
       return 1;
   }

   png_init_io(png_ptr, fp);
   png_set_sig_bytes(png_ptr, 8);

   png_read_info(png_ptr, info_ptr);

   m_width = png_get_image_width(png_ptr, info_ptr);
   m_height = png_get_image_height(png_ptr, info_ptr);
   color_type = png_get_color_type(png_ptr, info_ptr);
   gl::Log(boost::format("color type is %d  ") % color_type);
   bit_depth = png_get_bit_depth(png_ptr, info_ptr);

   number_of_passes = png_set_interlace_handling(png_ptr);
   png_read_update_info(png_ptr, info_ptr);

   /* read file */
   if (setjmp(png_jmpbuf(png_ptr)))
   {
      gl::Log("[read_png_file] Error during read_image");
      return 1;
   }

   png_bytep *  lRowPtrs = NULL;
   png_int_32 lRowSize = png_get_rowbytes(png_ptr,info_ptr);

   row_pointers = new png_byte[lRowSize * m_height];
   lRowPtrs = new png_bytep[m_height];
   for(int i = 0; i < m_height; ++i)
   {
     lRowPtrs[m_height - (i+1)] = row_pointers+ i * lRowSize;
   }
   png_read_image(png_ptr, lRowPtrs);
   fclose(fp);
   png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
   delete[] lRowPtrs;

   return 0;
}
