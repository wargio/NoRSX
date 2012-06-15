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
		u32 height = png1->height;
		if((y+height) >= G->buffers[G->currentBuffer].height)
			height = G->buffers[G->currentBuffer].height;

		u32 width = png1->width;
		if((x+width) >=G->buffers[G->currentBuffer].width)
			width = G->buffers[G->currentBuffer].width;

		for(n=0;n < height;n++){
			for(m=0;m < width;m++)
				scr[m]=png[m];
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
		u32 height = jpg1->height;
		if((y+height) >= G->buffers[G->currentBuffer].height)
			height = G->buffers[G->currentBuffer].height;

		u32 width = jpg1->width;
		if((x+width) >=G->buffers[G->currentBuffer].width)
			width = G->buffers[G->currentBuffer].width;

		for(n=0;n < height;n++){
			for(m=0;m < width;m++)
				scr[m]=jpg[m];
			jpg+=jpg1->pitch>>2;
			scr+=G->buffers[G->currentBuffer].width;
		}
	}
}

void Image::AlphaDrawIMG(int x, int y, pngData *png1){
	if(png1->bmp_out){
		u32 *scr = (u32 *)G->buffers[G->currentBuffer].ptr;
		u32 *png= (u32 *)(void *)png1->bmp_out;
		unsigned int n, m;

		scr += y*G->buffers[G->currentBuffer].width+x;
		u32 height = png1->height;
		if((y+height) >= G->buffers[G->currentBuffer].height)
			height = G->buffers[G->currentBuffer].height;

		u32 width = png1->width;
		if((x+width) >=G->buffers[G->currentBuffer].width)
			width = G->buffers[G->currentBuffer].width;

		for(n=0;n < height;n++){
			for(m=0;m < width;m++){
				unsigned int a = png[m] >> 24;	 // alpha 
				u32 OxFF_A = 0xff - a;
				if (0 != a) 
					scr[m] = (png[m] & 0xff000000) | ( (((((png[m] & 0x00ff00ff) * a) + ((scr[m] & 0x00ff00ff) *
						 (OxFF_A))) & 0xff00ff00) | ((((png[m] & 0x0000ff00) * a) + ((scr[m] & 0x0000ff00) *
						 (OxFF_A))) & 0x00ff0000)) >> 8);
			}
			png+=png1->pitch>>2;
			scr+=G->buffers[G->currentBuffer].width;
		}
/*
		scr += y*G->buffers[G->currentBuffer].width+x;
		for(n=0;n<png1->height;n++){
			if((y+n)>=G->buffers[G->currentBuffer].height) break;
			for(m=0;m<png1->width;m++){
				if((x+m)>=G->buffers[G->currentBuffer].width) break;
				unsigned int a = png[m] >> 24;	 // alpha 
				u32 OxFF_A = 0xff - a;
				if (0 != a) 
					scr[m] = (png[m] & 0xff000000) | ( (((((png[m] & 0x00ff00ff) * a) + ((scr[m] & 0x00ff00ff) *
						 (OxFF_A))) & 0xff00ff00) | ((((png[m] & 0x0000ff00) * a) + ((scr[m] & 0x0000ff00) *
						 (OxFF_A))) & 0x00ff0000)) >> 8);
			}
			png+=png1->pitch>>2;
			scr+=G->buffers[G->currentBuffer].width;
		}
*/
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

void Image::DrawIMGtoBitmap(int x, int y, pngData *png1, NoRSX_Bitmap *a){
	if(png1->bmp_out){
		u32 *scr = (u32 *)a->bitmap;
		u32 *png= (u32 *)(void *)png1->bmp_out;
		unsigned int n, m;

		scr += y*G->buffers[G->currentBuffer].width+x;
		u32 height = png1->height;
		if((y+height) >= G->buffers[G->currentBuffer].height)
			height = G->buffers[G->currentBuffer].height;

		u32 width = png1->width;
		if((x+width) >=G->buffers[G->currentBuffer].width)
			width = G->buffers[G->currentBuffer].width;

		for(n=0;n < height;n++){
			for(m=0;m < width;m++)
				scr[m]=png[m];
			png+=png1->pitch>>2;
			scr+=G->buffers[G->currentBuffer].width;
		}
	}
}


void Image::DrawIMGtoBitmap(int x, int y, jpgData *jpg1, NoRSX_Bitmap *a){
	if(jpg1->bmp_out){
		u32 *scr = (u32 *)a->bitmap;
		u32 *jpg= (u32 *)(void *)jpg1->bmp_out;
		unsigned int n, m;

		scr += y*G->buffers[G->currentBuffer].width+x;
		u32 height = jpg1->height;
		if((y+height) >= G->buffers[G->currentBuffer].height)
			height = G->buffers[G->currentBuffer].height;

		u32 width = jpg1->width;
		if((x+width) >=G->buffers[G->currentBuffer].width)
			width = G->buffers[G->currentBuffer].width;

		for(n=0;n < height;n++){
			for(m=0;m < width;m++)
				scr[m]=jpg[m];
			jpg+=jpg1->pitch>>2;
			scr+=G->buffers[G->currentBuffer].width;
		}
	}
}


void Image::AlphaDrawIMGtoBitmap(int x, int y, pngData *png1, NoRSX_Bitmap *a){
	if(png1->bmp_out){
		u32 *scr = (u32 *)a->bitmap;
		u32 *png= (u32 *)(void *)png1->bmp_out;
		unsigned int n, m;

		scr += y*G->buffers[G->currentBuffer].width+x;
		u32 height = png1->height;
		if((y+height) >= G->buffers[G->currentBuffer].height)
			height = G->buffers[G->currentBuffer].height;

		u32 width = png1->width;
		if((x+width) >=G->buffers[G->currentBuffer].width)
			width = G->buffers[G->currentBuffer].width;

		for(n=0;n < height;n++){
			for(m=0;m < width;m++){
				unsigned int a = png[m] >> 24;	 // alpha 
				u32 OxFF_A = 0xff - a;
				if (0 != a) 
					scr[m] = (png[m] & 0xff000000) | ( (((((png[m] & 0x00ff00ff) * a) + ((scr[m] & 0x00ff00ff) *
						 (OxFF_A))) & 0xff00ff00) | ((((png[m] & 0x0000ff00) * a) + ((scr[m] & 0x0000ff00) *
						 (OxFF_A))) & 0x00ff0000)) >> 8);
			}
			png+=png1->pitch>>2;
			scr+=G->buffers[G->currentBuffer].width;
		}
	}
}

