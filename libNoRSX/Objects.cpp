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

#include <NoRSX/Objects.h>
#include <math.h>

Object::Object(Minimum *g){
	G=g;
}

//Object::
void Object::Rectangle(u32 X, u32 Y, u32 width, u32 height, u32 Color){
	u32 i, j;
	for(i = Y; i < (height+Y); i++) {
		for(j = X; j < (width+X); j++)
			G->buffer[i* G->width + j] = Color;
	}
}


void Object::Circle(u32 X, u32 Y, u32 r, u32 Color){
	u32 rr = r*r;
	for(u32 y=0;y<r;y++){
		u32 width=sqrt(rr-y*y);
		for(u32 x=0;x<width;x++){
			Pixel(X+x, Y+y, Color);
			Pixel(X+x, Y-y, Color);
			Pixel(X-x, Y+y, Color);
			Pixel(X-x, Y-y, Color);
		}
	}
}

void Object::RectangleToBitmap(u32 X, u32 Y, u32 width, u32 height, u32 Color, NoRSX_Bitmap *a){
	u32 i, j;
	for(i = Y; i < (height+Y); i++) {
		for(j = X; j < (width+X); j++)
			PixelToBuffer(X, Y, Color, a);
	}
}


void Object::CircleToBitmap(u32 X, u32 Y, u32 r, u32 Color, NoRSX_Bitmap *a){
	u32 rr = r*r;
	for(u32 y=0;y<r;y++){
		u32 width=sqrt(rr-y*y);
		for(u32 x=0;x<width;x++){
			PixelToBuffer(X+x, Y+y, Color,a);
			PixelToBuffer(X+x, Y-y, Color,a);
			PixelToBuffer(X-x, Y+y, Color,a);
			PixelToBuffer(X-x, Y-y, Color,a);
		}
	}
}

void Object::Line(u32 X, u32 Y, u32 X1, u32 Y1, u32 Color){
	int t, distance;
	int xerr=0, yerr=0, delta_x, delta_y;
	int incx, incy;

	delta_x=X1-X;
	delta_y=Y1-Y;

	if(delta_x>0) incx=1;
	else if(delta_x==0) incx=0;
	else incx=-1;

	if(delta_y>0) incy=1;
	else if(delta_y==0) incy=0;
	else incy=-1;

	delta_x=abs(delta_x);
	delta_y=abs(delta_y);
	if(delta_x>delta_y) distance=delta_x;
	else distance=delta_y;

	/* draw the line */
	for(t=0; t<=distance+1; t++) {
		Pixel4(X, Y, Color);
		
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance) {
			xerr-=distance;
			X+=incx;
		}
		if(yerr>distance) {
			yerr-=distance;
			Y+=incy;
		}
	}
}

void Object::Pixel4(u32 X, u32 Y, u32 Color){
	Pixel(X  ,Y  ,Color);
	Pixel(X+1,Y  ,Color);
	Pixel(X  ,Y+1,Color);
	Pixel(X+1,Y+1,Color);
}


int Object::Pixel(u32 X, u32 Y, u32 Color){
	if(Y>=(unsigned int)G->height || Y<(unsigned int)0) return -1;
	if(X>=(unsigned int)G->width  || X<(unsigned int)0) return -1;
	G->buffer[Y* G->width + X] = Color;
	return 1;
}

int Object::PixelToBuffer(u32 X, u32 Y, u32 Color, NoRSX_Bitmap *a){
	if(Y>=(unsigned int)G->height || Y<(unsigned int)0) return -1;
	if(X>=(unsigned int)G->width  || X<(unsigned int)0) return -1;
	a->bitmap[Y* G->width + X] = Color;
	return 1;
}
