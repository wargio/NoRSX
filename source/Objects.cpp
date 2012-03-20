#include "Objects.h"

Object::Object(Minimum *g){
	G=g;
}

//Object::
void Object::Rectangle(u32 X, u32 Y, u32 width, u32 height, s32 Color){
	s32 i, j;
	for(i = Y; i < (height+Y); i++) {
		for(j = X; j < (width+X); j++)
			G->buffers[G->currentBuffer].ptr[i* G->buffers[G->currentBuffer].width + j] = Color;
	}
}

/*
void Object::Circle(u32 X, u32 Y, u32 r, s32 Color){
	s32 i, j;
	for(i = 0; i < G->buffers[G->currentBuffer].height; i++) {
		for(j = 0; j < G->buffers[G->currentBuffer].width; j++)
			G->buffers[G->currentBuffer].ptr[i* G->buffers[G->currentBuffer].width + j] = Color;
	}
}
*/

void Object::Pixel4(u32 X, u32 Y, u32 Color){
	Pixel(X,Y,Color);
	Pixel(X+1,Y,Color);
	Pixel(X,Y+1,Color);
	Pixel(X+1,Y+1,Color);
}


int Object::Pixel(u32 X, u32 Y, u32 Color){
	if(Y>=(unsigned int)G->buffers[G->currentBuffer].height || Y<(unsigned int)0) return -1;
	if(X>=(unsigned int)G->buffers[G->currentBuffer].width  || X<(unsigned int)0) return -1;
	G->buffers[G->currentBuffer].ptr[Y* G->buffers[G->currentBuffer].width + X] = Color;
	return 1;
}

