#include "Objects.h"
#include <math.h>

Object::Object(Minimum *g){
	G=g;
}

//Object::
void Object::Rectangle(u32 X, u32 Y, u32 width, u32 height, u32 Color){
	s32 i, j;
	for(i = Y; i < (height+Y); i++) {
		for(j = X; j < (width+X); j++)
			G->buffers[G->currentBuffer].ptr[i* G->buffers[G->currentBuffer].width + j] = Color;
	}
}


void Object::Circle(u32 X, u32 Y, u32 r, u32 Color){
	for(u32 y=0;y<r;y++){
		u32 width=sqrt(r*r-y*y);
		for(u32 x=0;x<width;x++){
			Pixel(X+x, Y+y, Color);
			Pixel(X+x, Y-y, Color);
			Pixel(X-x, Y+y, Color);
			Pixel(X-x, Y-y, Color);
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
	if(Y>=(unsigned int)G->buffers[G->currentBuffer].height || Y<(unsigned int)0) return -1;
	if(X>=(unsigned int)G->buffers[G->currentBuffer].width  || X<(unsigned int)0) return -1;
	G->buffers[G->currentBuffer].ptr[Y* G->buffers[G->currentBuffer].width + X] = Color;
	return 1;
}

