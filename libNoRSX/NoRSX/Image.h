/*
 * Copyright (c) 2013, Giovanni Dante Grazioli (deroad)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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
	jpgData *ResizeImage(jpgData *jpg_in, u32 TgtWidth, u32 TgtHeight);

protected:
	Minimum *G;
	void DrawPartialImage(int x, int y, unsigned int s_width, unsigned int s_height, unsigned int e_width, unsigned int e_height, unsigned int bg, unsigned int color, pngData *png1); 
	void DrawPartialImage(int x, int y, unsigned int s_width, unsigned int s_height, unsigned int e_width, unsigned int e_height, unsigned int bg, unsigned int color, jpgData *jpg1); 

	void ScaleLine(u32 *Target, u32 *Source, u32 SrcWidth, u32 TgtWidth);

};

unsigned int AlphaBlend(const unsigned int bg, const unsigned int src);

#endif
