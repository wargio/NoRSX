/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 This program was created by Grazioli Giovanni Dante <wargio@libero.it>.

*/

#include <NoRSX/Image.h>

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
		u32 *png = (u32 *)(void *)png1->bmp_out;

		scr += y*G->width+x;
		u32 height = png1->height;
		if((y+height) >= (u32)G->height)
			height = G->height;

		u32 width = png1->width;
		if((x+width) >= (u32)G->width)
			width = G->width;

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
		u32 *scr = (u32 *)G->buffers[G->currentBuffer].ptr;
		u32 *jpg = (u32 *)(void *)jpg1->bmp_out;

		scr += y*G->width+x;
		u32 height = jpg1->height;
		if((y+height) >= (u32)G->height)
			height = G->height;

		u32 width = jpg1->width;
		if((x+width) >= (u32)G->width)
			width = G->width;

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
		u32 *scr = (u32 *)G->buffers[G->currentBuffer].ptr;
		u32 *png = (u32 *)(void *)png1->bmp_out;
		unsigned int m;

		scr += y*G->width+x;
		u32 height = png1->height;
		if((y+height) >= (u32)G->height)
			height = G->height;

		u32 width = png1->width;
		if((x+width) >= (u32)G->width)
			width = G->width;

		while(height>0){
			for(m=0;m < (u32)width;m++){
				unsigned int a = png[m] >> 24;	 // alpha 
				u32 OxFF_A = 0xff - a;
				if (0 != a) 
					scr[m] = (png[m] & 0xff000000) | ( (((((png[m] & 0x00ff00ff) * a) + ((scr[m] & 0x00ff00ff) *
						 (OxFF_A))) & 0xff00ff00) | ((((png[m] & 0x0000ff00) * a) + ((scr[m] & 0x0000ff00) *
						 (OxFF_A))) & 0x00ff0000)) >> 8);
			}
			png+=png1->pitch>>2;
			scr+=G->width;
			height--;
		}
	}
}

void Image::DrawPartialImage(int x, int y, unsigned int s_width, unsigned int s_height, unsigned int e_width, unsigned int e_height, unsigned int bg, unsigned int color, pngData *png1){
	if(png1->bmp_out){
		u32 *scr = (u32 *)G->buffers[G->currentBuffer].ptr;
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
		u32 *scr = (u32 *)G->buffers[G->currentBuffer].ptr;
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

		scr += y*G->width+x;
		u32 height = png1->height;
		if((y+height) >= (u32)G->height)
			height = G->height;

		u32 width = png1->width;
		if((x+width) >= (u32)G->width)
			width = G->width;

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

		scr += y*G->width+x;
		u32 height = jpg1->height;
		if((y+height) >= (u32)G->height)
			height = G->height;

		u32 width = jpg1->width;
		if((x+width) >= (u32)G->width)
			width = G->width;

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
		unsigned int n, m;

		scr += y*G->width+x;
		u32 height = png1->height;
		if((y+height) >= (u32)G->height)
			height = G->height;

		u32 width = png1->width;
		if((x+width) >= (u32)G->width)
			width = G->width;

		for(n=0;n < (u32)height;n++){
			for(m=0;m < (u32)width;m++){
				unsigned int a = png[m] >> 24;	 // alpha 
				u32 OxFF_A = 0xff - a;
				if (0 != a) 
					scr[m] = (png[m] & 0xff000000) | ( (((((png[m] & 0x00ff00ff) * a) + ((scr[m] & 0x00ff00ff) *
						 (OxFF_A))) & 0xff00ff00) | ((((png[m] & 0x0000ff00) * a) + ((scr[m] & 0x0000ff00) *
						 (OxFF_A))) & 0x00ff0000)) >> 8);
			}
			png+=png1->pitch>>2;
			scr+=G->width;
		}
	}
}

void Image::ScaleLine(u32 *Target, u32 *Source, u32 SrcWidth, u32 TgtWidth){
 //Thanks to: http://www.compuphase.com/graphic/scale.htm
	int NumPixels = TgtWidth;
	int IntPart = SrcWidth / TgtWidth;
	int FractPart = SrcWidth % TgtWidth;
	int E = 0;

	while (NumPixels-- > 0) {
		*Target++ = *Source;
		Source += IntPart;
		E += FractPart;
		if (E >= (int)TgtWidth) {
			E -= TgtWidth;
			Source++;
		} /* if */
	} /* while */
}

pngData * Image::ResizeImage(pngData *png_in, u32 TgtWidth, u32 TgtHeight){
 //Thanks to: http://www.compuphase.com/graphic/scale.htm
	if(png_in->bmp_out){
		pngData *png_out = new pngData;
		png_out->bmp_out = (u32 *) malloc(TgtHeight*TgtWidth*sizeof(u32));
		u32 *Source = (u32 *)(void *)png_in->bmp_out;
		u32 *Target = (u32 *)(void *)png_out->bmp_out;

		png_out->height = TgtHeight;
		png_out->width  = TgtWidth;
		png_out->pitch  = TgtWidth*4;

		int NumPixels = TgtHeight;
		int IntPart = (png_in->height / TgtHeight) * png_in->width;
		int FractPart = png_in->height % TgtHeight;
		int E = 0;
		u32 *PrevSource = NULL;

		while (NumPixels-- > 0) {
			if (Source == PrevSource) {
				memcpy(Target, Target-TgtWidth, TgtWidth*sizeof(*Target));
			} else {
				ScaleLine(Target, Source, png_in->width, TgtWidth);
				PrevSource = Source;
			}
			Target += TgtWidth;
			Source += IntPart;
			E += FractPart;
			if (E >= (int)TgtHeight) {
				E -= TgtHeight;
				Source += png_in->width;
			}
		}
		return png_out;
	}
	return NULL;
}



