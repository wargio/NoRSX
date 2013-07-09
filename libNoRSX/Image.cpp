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

#include <NoRSX/Image.h>

static u32 n, m, a, OxFF_A;
static u32 *scr;
static u32 *png;
static u32 *jpg;
static int NumPixels0 = 0;
static int IntPart0 = 0;
static int FractPart0 = 0;
static int E0 = 0;
static int NumPixels1 = 0;
static int IntPart1 = 0;
static int FractPart1 = 0;
static int E1 = 0;
static int height=0, width=0, stop_x = 0, stop_y = 0;

static int error_x, error_y;

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
		u32 *scr = (u32 *)G->buffer;
		u32 *png = (u32 *)png1->bmp_out;


		if(x<0){
			png = png-x;
			error_x=-x;
			x=0;
		}else
			error_x=0;
			
		if(y<0){
			error_y=-y;
			png = png + y*png1->width;
			y=0;
		}else
			error_y=0;
		
		scr += y*G->width+x;
		int height = png1->height;
		if((y+height) >= (u32)G->height)
			height = G->height-1-y;

		int width = png1->width;
		if((x+width) >= (u32)G->width)
			width = G->width-x-1;

		width-=error_x;
		height-=error_y;
		
		if(width>0)
		while(height>0){
			memcpy(scr,png,width*sizeof(u32));
			png+=png1->pitch>>2;
			scr+=G->width;
			height--;
		}
	}
}

void Image::DrawIMG(int x, int y, jpgData *jpg1){
	if(jpg1->bmp_out){
		u32 *scr = (u32 *)G->buffer;
		u32 *jpg = (u32 *)(void *)jpg1->bmp_out;


		if(x<0){
			jpg = jpg-x;
			error_x=-x;
			x=0;
		}else
			error_x=0;
		if(y<0){
			error_y=-y;
			jpg = jpg + y*jpg1->width;
			y=0;
		}else
			error_y=0;

		scr += y*G->width+x;
		int height = jpg1->height;
		if((y+height) >= (u32)G->height)
			height = G->height-1-y;

		int width = jpg1->width;
		if((x+width) >= (u32)G->width)
			width = G->width-1-x;

		width-=error_x;
		height-=error_y;
		if(width>0)
		while(height>0){
			memcpy(scr,jpg,width*sizeof(u32));
			jpg+=jpg1->pitch>>2;
			scr+=G->width;
			height--;
		}
	}
}

void Image::AlphaDrawIMG(int x, int y, pngData *png1){
	if(png1->bmp_out){
		u32 *scr = (u32 *)G->buffer;
		u32 *png = (u32 *)(void *)png1->bmp_out;
		unsigned int m;

		if(x<0){
			png = png-x;
			error_x=-x;
			x=0;
		}else
			error_x=0;
		if(y<0){
			error_y=-y;
			png = png + y*png1->width;
			y=0;
		}else
			error_y=0;

		
		scr += y*G->width+x;
		int height = png1->height;
		if((y+height) >= (u32)G->height)
			height = G->height-1-y;

		int width = png1->width;
		if((x+width) >= (u32)G->width)
			width = G->width-1-x;

		width-=error_x;
		height-=error_y;
		
		u32 a, OxFF_A;
		
		if(width>0)
		while(height>0){
			for(m=0;m < (u32)width;m++){
				a = png[m] >> 24;	 // alpha 
				if (a == 0xff)
					scr[m] = png[m];
				else if (a != 0){
					OxFF_A = 0xff - a;
					scr[m] = (png[m] & 0xff000000) | ( (((((png[m] & 0x00ff00ff) * a) + ((scr[m] & 0x00ff00ff) *
						 (OxFF_A))) & 0xff00ff00) | ((((png[m] & 0x0000ff00) * a) + ((scr[m] & 0x0000ff00) *
						 (OxFF_A))) & 0x00ff0000)) >> 8);
				}
			}
			png+=png1->pitch>>2;
			scr+=G->width;
			height--;
		}
	}
}

void Image::DrawPartialImage(int x, int y, unsigned int s_width, unsigned int s_height, unsigned int e_width, unsigned int e_height, unsigned int bg, unsigned int color, pngData *png1){
	if(png1->bmp_out){
		u32 *scr = (u32 *)G->buffer;
		u32 *png = (u32 *)(void *)png1->bmp_out;
		unsigned int n, m;

		scr += y*G->width+x;
		if(s_height>0) for(unsigned int i=0;i<s_height;i++) png+=png1->pitch>>2;
		for(n=s_height;n<e_height+s_height;n++){
			if((y+n)>=(u32)G->height) break;
			for(m=s_width;m<e_width+s_width;m++){
				if((x+m)>=(u32)G->width) break;
				if(png[m]!=bg) scr[m-s_width]=color;
			}
			png+=png1->pitch>>2;
			scr+=G->width;
		}
	}
}

void Image::DrawPartialImage(int x, int y, unsigned int s_width, unsigned int s_height, unsigned int e_width, unsigned int e_height, unsigned int bg, unsigned int color, jpgData *jpg1){
	if(jpg1->bmp_out){
		u32 *scr = (u32 *)G->buffer;
		u32 *jpg = (u32 *)(void *)jpg1->bmp_out;
		unsigned int n, m;

		scr += y*G->width+x;
		if(s_height>0) for(unsigned int i=0;i<s_height;i++) jpg+=jpg1->pitch>>2;
		for(n=s_height;n<e_height+s_height;n++){
			if((y+n)>=(u32)G->height) break;
			for(m=s_width;m<e_width+s_width;m++){
				if((x+m)>=(u32)G->width) break;
				if(jpg[m]!=bg) scr[m-s_width]=color;
			}
			jpg+=jpg1->pitch>>2;
			scr+=G->width;
		}
	}
}

void Image::DrawIMGtoBitmap(int x, int y, pngData *png1, NoRSX_Bitmap *a){
	if(png1->bmp_out){
		u32 *scr = (u32 *)a->bitmap;
		u32 *png = (u32 *)(void *)png1->bmp_out;

		if(x<0){
			png = png-x;
			error_x=-x;
			x=0;
		}else
			error_x=0;
			
		if(y<0){
			error_y=-y;
			png = png + y*png1->width;
			y=0;
		}else
			error_y=0;
		
		scr += y*G->width+x;
		int height = png1->height;
		if((y+height) >= (u32)G->height)
			height = G->height-1-y;

		int width = png1->width;
		if((x+width) >= (u32)G->width)
			width = G->width-x-1;

		width-=error_x;
		height-=error_y;

		if(width>0)
		while(height>0){
			memcpy(scr,png,width*sizeof(u32));
			png+=png1->pitch>>2;
			scr+=G->width;
			height--;
		}
	}
}


void Image::DrawIMGtoBitmap(int x, int y, jpgData *jpg1, NoRSX_Bitmap *a){
	if(jpg1->bmp_out){
		u32 *scr = (u32 *)a->bitmap;
		u32 *jpg = (u32 *)(void *)jpg1->bmp_out;

		if(x<0){
			jpg = jpg-x;
			error_x=-x;
			x=0;
		}else
			error_x=0;
			
		if(y<0){
			error_y=-y;
			jpg = jpg + y*jpg1->width;
			y=0;
		}else
			error_y=0;
		
		scr += y*G->width+x;
		int height = jpg1->height;
		if((y+height) >= (u32)G->height)
			height = G->height-1-y;

		int width = jpg1->width;
		if((x+width) >= (u32)G->width)
			width = G->width-1-x;
			
			
		width-=error_x;
		height-=error_y;

		if(width>0)
		while(height>0){
			memcpy(scr,jpg,width*sizeof(u32));
			jpg+=jpg1->pitch>>2;
			scr+=G->width;
			height--;
		}
	}
}


void Image::AlphaDrawIMGtoBitmap(int x, int y, pngData *png1, NoRSX_Bitmap *a){
	if(png1->bmp_out){
		u32 *scr = (u32 *)a->bitmap;
		u32 *png= (u32 *)(void *)png1->bmp_out;

		if(x<0){
			png = png-x;
			error_x=-x;
			x=0;
		}else
			error_x=0;
			
		if(y<0){
			error_y=-y;
			png = png + y*png1->width;
			y=0;
		}else
			error_y=0;

		scr += y*G->width+x;
		int height = png1->height;
		if((y+height) >= (u32)G->height)
			height = G->height-1-y;

		int width = png1->width;
		if((x+width) >= (u32)G->width)
			width = G->width-1-x;

		width-=error_x;
		height-=error_y;

		u32 a, OxFF_A;

		if(width>0)
		for(n=0;n < (u32)height;n++){
			for(m=0;m < (u32)width;m++){
				a = png[m] >> 24;	 // alpha 
				if (a == 0xff)
					scr[m] = png[m];
				else if (0 != a){
					OxFF_A = 0xff - a;
					scr[m] = (png[m] & 0xff000000)  | ((((((png[m] & 0x00ff00ff) * a) + ((scr[m] & 0x00ff00ff) *
						 OxFF_A)) & 0xff00ff00) | ((((png[m] & 0x0000ff00) * a) + ((scr[m] & 0x0000ff00) *
						 OxFF_A)) & 0x00ff0000)) >> 8);
				}
			}
			png+=png1->pitch>>2;
			scr+=G->width;
		}
	}
}


void Image::ScaleLine(u32 *Target, u32 *Source, u32 SrcWidth, u32 TgtWidth){
 //Thanks to: http://www.compuphase.com/graphic/scale.htm
	NumPixels1 = TgtWidth;
	IntPart1 = SrcWidth / TgtWidth;
	FractPart1 = SrcWidth % TgtWidth;
	E1 = 0;

	while (NumPixels1-- > 0) {
		*Target++ = *Source;
		Source += IntPart1;
		E1 += FractPart1;
		if (E1 >= TgtWidth) {
			E1 -= TgtWidth;
			Source++;
		} /* if */
	} /* while */
	return;
}


pngData * Image::ResizeImage(pngData *png_in, u32 TgtWidth, u32 TgtHeight){
 //Thanks to: http://www.compuphase.com/graphic/scale.htm
	if(png_in->bmp_out){
		pngData *png_out = new pngData;
		png_out->bmp_out = (u32 *) malloc(TgtHeight*TgtWidth*sizeof(u32));
		static u32 *Source = (u32 *)(void *)png_in->bmp_out;
		static u32 *Target = (u32 *)(void *)png_out->bmp_out;

		png_out->height = TgtHeight;
		png_out->width  = TgtWidth;
		png_out->pitch  = TgtWidth*4;

		NumPixels0 = TgtHeight;
		IntPart0 = (png_in->height / TgtHeight) * png_in->width;
		FractPart0 = png_in->height % TgtHeight;
		E0 = 0;
		static u32 *PrevSource = NULL;

		while (NumPixels0-- > 0) {
			if (Source == PrevSource) {
				memcpy(Target, Target-TgtWidth, TgtWidth*sizeof(*Target));
			} else {
				ScaleLine(Target, Source, png_in->width, TgtWidth);
				PrevSource = Source;
			}
			Target += TgtWidth;
			Source += IntPart0;
			E0 += FractPart0;
			if (E0 >= TgtHeight) {
				E0 -= TgtHeight;
				Source += png_in->width;
			}
		}
		return png_out;
	}
	return NULL;
}

jpgData * Image::ResizeImage(jpgData *jpg_in, u32 TgtWidth, u32 TgtHeight){
 //Thanks to: http://www.compuphase.com/graphic/scale.htm
	if(jpg_in->bmp_out){
		jpgData *jpg_out = new jpgData;
		jpg_out->bmp_out = (u32 *) malloc(TgtHeight*TgtWidth*sizeof(u32));
		static u32 *Source = (u32 *)(void *)jpg_in->bmp_out;
		static u32 *Target = (u32 *)(void *)jpg_out->bmp_out;

		jpg_out->height = TgtHeight;
		jpg_out->width  = TgtWidth;
		jpg_out->pitch  = TgtWidth*4;

		NumPixels0 = TgtHeight;
		IntPart0 = (jpg_in->height / TgtHeight) * jpg_in->width;
		FractPart0 = jpg_in->height % TgtHeight;
		E0 = 0;
		static u32 *PrevSource = NULL;

		while (NumPixels0-- > 0) {
			if (Source == PrevSource) {
				memcpy(Target, Target-TgtWidth, TgtWidth*sizeof(*Target));
			} else {
				ScaleLine(Target, Source, jpg_in->width, TgtWidth);
				PrevSource = Source;
			}
			Target += TgtWidth;
			Source += IntPart0;
			E0 += FractPart0;
			if (E0 >= TgtHeight) {
				E0 -= TgtHeight;
				Source += jpg_in->width;
			}
		}
		return jpg_out;
	}
	return NULL;
}



