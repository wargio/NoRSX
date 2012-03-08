#include "Image.h"
void Image::LoadPNG(const char* filename, pngData *png){
	pngLoadFromFile(filename, png);
}

void Image::LoadJPG(const char* filename, jpgData *jpg){
	jpgLoadFromFile(filename, jpg);
}
/*
void Image::LoadPNG_Buf(const void* name, pngData *png){
	pngLoadFromBuffer(name, name_size, png);
}

void Image::LoadJPG_Buf(const void* name, jpgData *jpg){
	jpgLoadFromBuffer(name, name_size, jpg);
}
*/
void Image::DrawIMG(int x, int y, pngData *png1){
	if(png1->bmp_out){
		u32 *scr = (u32 *)G->buffers[G->currentBuffer].ptr;
		u32 *png= (u32 *)(void *)png1->bmp_out;
		unsigned int n, m;

		scr += y*G->buffers[G->currentBuffer].width+x;
		for(n=0;n<png1->height;n++){
			if((y+n)>=G->buffers[G->currentBuffer].height) break;
			for(m=0;m<png1->width;m++){
				if((x+m)>=G->buffers[G->currentBuffer].width) break;
				scr[m]=png[m];
			}
			png+=png1->pitch>>2;
			scr+=G->buffers[G->currentBuffer].width;
		}
	}
}

void Image::DrawIMG(int x, int y, jpgData *jpg1){
	if(jpg1->bmp_out){
		u32 *scr = (u32 *)G->buffers[G->currentBuffer].ptr;
		u32 *jpg= (u32 *)(void *)jpg1->bmp_out;
		unsigned int n, m;

		scr += y*G->buffers[G->currentBuffer].width+x;
		for(n=0;n<jpg1->height;n++){
			if((y+n)>=G->buffers[G->currentBuffer].height) break;
			for(m=0;m<jpg1->width;m++){
				if((x+m)>=G->buffers[G->currentBuffer].width) break;
				scr[m]=jpg[m];
			}
			jpg+=jpg1->pitch>>2;
			scr+=G->buffers[G->currentBuffer].width;
		}
	}
}

