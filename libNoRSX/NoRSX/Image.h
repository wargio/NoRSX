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

	void DrawIMG(s32 x, s32 y, pngData *png);
	void DrawIMG(s32 x, s32 y, jpgData *jpg);
	void AlphaDrawIMG(s32 x, s32 y, pngData *png);

	void DrawIMGtoBitmap(s32 x, s32 y, pngData *png, NoRSX_Bitmap *bmap);
	void DrawIMGtoBitmap(s32 x, s32 y, jpgData *jpg, NoRSX_Bitmap *bmap);
	void AlphaDrawIMGtoBitmap(s32 x, s32 y, pngData *png, NoRSX_Bitmap *bmap);

	pngData *ResizeImage(pngData *png_in, u32 tgt_width, u32 tgt_height);
	jpgData *ResizeImage(jpgData *jpg_in, u32 tgt_width, u32 tgt_height);

protected:
	Minimum *G;
	void DrawPartialImage(s32 x, s32 y, u32 s_width, u32 s_height, u32 e_width, u32 e_height, u32 bg, u32 color, pngData *png); 
	void DrawPartialImage(s32 x, s32 y, u32 s_width, u32 s_height, u32 e_width, u32 e_height, u32 bg, u32 color, jpgData *jpg); 

};

#endif
