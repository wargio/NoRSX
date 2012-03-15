#include "Image.h"
void Image::LoadPNG(const char* filename, pngData *png){
	pngLoadFromFile(filename, png);
}

void Image::LoadJPG(const char* filename, jpgData *jpg){
	jpgLoadFromFile(filename, jpg);
}

void Image::LoadPNG_Buf(const void* name, u32 name_size, pngData *png){
	pngLoadFromBuffer(name, name_size, png);
}

void Image::LoadJPG_Buf(const void* name, u32 name_size, jpgData *jpg){
	jpgLoadFromBuffer(name, name_size, jpg);
}

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


void Image::DrawPartialImage(int x, int y, unsigned int s_width, unsigned int s_height, unsigned int e_width, unsigned int e_height, unsigned int bg, unsigned int color, pngData *png1){
	if(png1->bmp_out){
		u32 *scr = (u32 *)G->buffers[G->currentBuffer].ptr;
		u32 *png= (u32 *)(void *)png1->bmp_out;
		unsigned int n, m;

		scr += y*G->buffers[G->currentBuffer].width+x;
		if(s_height>0) for(unsigned int i=0;i<s_height;i++) png+=png1->pitch>>2;
		for(n=s_height;n<e_height+s_height;n++){
			if((y+n)>=G->buffers[G->currentBuffer].height) break;
			for(m=s_width;m<e_width+s_width;m++){
				if((x+m)>=G->buffers[G->currentBuffer].width) break;
				if(png[m]!=bg) scr[m-s_width]=color;
			}
			png+=png1->pitch>>2;
			scr+=G->buffers[G->currentBuffer].width;
		}
	}
}

void Image::DrawPartialImage(int x, int y, unsigned int s_width, unsigned int s_height, unsigned int e_width, unsigned int e_height, unsigned int bg, unsigned int color, jpgData *jpg1){
	if(jpg1->bmp_out){
		u32 *scr = (u32 *)G->buffers[G->currentBuffer].ptr;
		u32 *jpg= (u32 *)(void *)jpg1->bmp_out;
		unsigned int n, m;

		scr += y*G->buffers[G->currentBuffer].width+x;
		if(s_height>0) for(unsigned int i=0;i<s_height;i++) jpg+=jpg1->pitch>>2;
		for(n=s_height;n<e_height+s_height;n++){
			if((y+n)>=G->buffers[G->currentBuffer].height) break;
			for(m=s_width;m<e_width+s_width;m++){
				if((x+m)>=G->buffers[G->currentBuffer].width) break;
				if(jpg[m]!=bg) scr[m-s_width]=color;
			}
			jpg+=jpg1->pitch>>2;
			scr+=G->buffers[G->currentBuffer].width;
		}
	}
}



/* alpha blend routine */
unsigned int AlphaBlend(const unsigned int bg, const unsigned int src){
   unsigned int a = src >> 24;    /* alpha */

   /* If source pixel is transparent, just return the background */
   if (0 == a) 
      return bg;

   /* alpha blending the source and background colors */
   unsigned int rb = (((src & 0x00ff00ff) * a) +  
      ((bg & 0x00ff00ff) * (0xff - a))) & 0xff00ff00;
   unsigned int    g  = (((src & 0x0000ff00) * a) + 
      ((bg & 0x0000ff00) * (0xff - a))) & 0x00ff0000;

    return (src & 0xff000000) | ((rb | g) >> 8);
}
