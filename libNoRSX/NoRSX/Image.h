/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 This program was created by Grazioli Giovanni Dante <wargio@libero.it>.
*/

#ifndef __NORSX_IMAGE_H__
#define __NORSX_IMAGE_H__

#include <pngdec/pngdec.h>
#include <jpgdec/jpgdec.h>
#include <sysutil/sysutil.h>
#include <sysmodule/sysmodule.h>
#include "Min.h"
#include "Bitmap.h"

//#define CROMAKEY	0xffbcbc222

class Image{
public:
	Image(Minimum *g){
		G=g;
		sysModuleLoad(SYSMODULE_FS);
		sysModuleLoad(SYSMODULE_PNGDEC);
		sysModuleLoad(SYSMODULE_JPGDEC);
	}
	~Image(){
		sysModuleUnload(SYSMODULE_FS);
		sysModuleUnload(SYSMODULE_PNGDEC);
		sysModuleUnload(SYSMODULE_JPGDEC);
	}
	void LoadPNG(const char* filename, pngData *png);
	void LoadJPG(const char* filename, jpgData *jpg);
	void LoadPNG_Buf(const void* name, u32 name_size, pngData *png);
	void LoadJPG_Buf(const void* name, u32 name_size, jpgData *jpg);

	void DrawIMG(int x, int y, pngData *png1);
	void DrawIMG(int x, int y, jpgData *jpg1);
	void AlphaDrawIMG(int x, int y, pngData *png1);

	void DrawIMGtoBitmap(int x, int y, pngData *png1, NoRSX_Bitmap *a);
	void DrawIMGtoBitmap(int x, int y, jpgData *jpg1, NoRSX_Bitmap *a);
	void AlphaDrawIMGtoBitmap(int x, int y, pngData *png1, NoRSX_Bitmap *a);

	pngData *ResizeImage(pngData *png_in, u32 TgtWidth, u32 TgtHeight);

protected:
	Minimum *G;
	void DrawPartialImage(int x, int y, unsigned int s_width, unsigned int s_height, unsigned int e_width, unsigned int e_height, unsigned int bg, unsigned int color, pngData *png1); 
	void DrawPartialImage(int x, int y, unsigned int s_width, unsigned int s_height, unsigned int e_width, unsigned int e_height, unsigned int bg, unsigned int color, jpgData *jpg1); 

	void ScaleLine(u32 *Target, u32 *Source, u32 SrcWidth, u32 TgtWidth);

};

unsigned int AlphaBlend(const unsigned int bg, const unsigned int src);

#endif
