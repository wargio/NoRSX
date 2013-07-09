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

#ifndef __NORSX_BITMAP_H__
#define __NORSX_BITMAP_H__

#include "Min.h"

typedef struct {
	uint32_t *bitmap;
	uint32_t width;
	uint32_t height;

	int load;
} NoRSX_Bitmap;

class Bitmap{
public:
	Bitmap(Minimum *g){
		G=g;
	}

	Bitmap(){

	}	

	void GenerateBitmap(NoRSX_Bitmap *a);
	void GenerateCustomBitmap(uint32_t width, uint32_t height, NoRSX_Bitmap *a);
	void ClearBitmap(NoRSX_Bitmap *a);
	void RegenBitmap(NoRSX_Bitmap *a);
	void DrawCustomBitmap(uint32_t start_width, uint32_t start_height, uint32_t end_width, uint32_t end_height, NoRSX_Bitmap *a);
	void DrawBitmap(NoRSX_Bitmap *a);

	

private:
	Minimum *G;
};

#endif
