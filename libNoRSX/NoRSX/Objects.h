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

#ifndef __NORSX_OBJ_H__
#define __NORSX_OBJ_H__
#include "Min.h"
#include "Colors.h"
#include "Bitmap.h"

class Object{
public:
	 Object(Minimum *g);
	~Object(){}
	
	void Rectangle(u32 X, u32 Y, u32 width, u32 height, u32 Color);
	void Circle(u32 X, u32 Y, u32 r, u32 Color);
	void Line(u32 X, u32 Y, u32 X1, u32 Y1, u32 Color);
	void Pixel4(u32 X, u32 Y, u32 Color);

	void RectangleToBitmap(u32 X, u32 Y, u32 width, u32 height, u32 Color, NoRSX_Bitmap *a);
	void CircleToBitmap(u32 X, u32 Y, u32 r, u32 Color, NoRSX_Bitmap *a);
	
	
private:
	Minimum *G;
	int Pixel(u32 X, u32 Y, u32 Color);
	int PixelToBuffer(u32 X, u32 Y, u32 Color, NoRSX_Bitmap *a);
};

#endif
