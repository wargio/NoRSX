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

#include "Animation.h"
#include <stdio.h>
#include <stdint.h>

#define ANIMATION_ALPHA_CHROMAKEY	0x000000ff

static int drawing_width;
static int drawing_height;

void Animation::LoadAnimation (uint32_t Elem_num, uint32_t Elem_w, uint32_t Elem_h, uint32_t ChromaKey, pngData* PNG, NoRSX_Animation *anim){
	if(PNG->bmp_out && anim->load != 1){
		anim->load        = 1;
		anim->bitmap      = new uint32_t[(const int)(PNG->height*PNG->width)];
		anim->elem_num    = Elem_num;
		anim->elem_height = Elem_h;
		anim->elem_width  = Elem_w;
		anim->elem_y      = new u16[(const u32)Elem_num];
		anim->elem_x      = new u16[(const u32)Elem_num];
		anim->chromakey   = ChromaKey;
		anim->bitmap_width= PNG->width;

		memcpy(anim->bitmap,PNG->bmp_out, PNG->height*PNG->width*sizeof(uint32_t));
		
		for(u16 k=0,j=0;k<PNG->height && j<Elem_num;k+=Elem_h){
			for(u16 i=0;i<PNG->width && j<Elem_num;i+=Elem_w, j++){
				anim->elem_x[j] = i;
				anim->elem_y[j] = k;
			}
		}
	}
	return;
}

void Animation::LoadAnimation (uint32_t Elem_num, uint32_t Elem_w, uint32_t Elem_h, pngData* PNG, NoRSX_Animation *anim){
	if(PNG->bmp_out && anim->load != 1){
		anim->load        = 1;
		anim->bitmap      = new uint32_t[(const int)(PNG->height*PNG->width)];
		anim->elem_num    = Elem_num;
		anim->elem_height = Elem_h;
		anim->elem_width  = Elem_w;
		anim->elem_y      = new u16[(const u32)Elem_num];
		anim->elem_x      = new u16[(const u32)Elem_num];
		anim->chromakey   = ANIMATION_ALPHA_CHROMAKEY;
		anim->bitmap_width= PNG->width;

		memcpy(anim->bitmap,PNG->bmp_out, PNG->height*PNG->width*sizeof(uint32_t));
		Elem_num++;
		for(u16 k=0,j=0;k<PNG->height && j<Elem_num;k+=Elem_h){
			for(u16 i=0;i<PNG->width && j<Elem_num;i+=Elem_w, j++){
				anim->elem_x[j] = i;
				anim->elem_y[j] = k;
			}
		}
	}
	return;

}

void Animation::LoadAnimation (uint32_t Elem_num, uint32_t Elem_w, uint32_t Elem_h, uint32_t ChromaKey, jpgData* JPG, NoRSX_Animation *anim){
	if(JPG->bmp_out && anim->load != 1){
		anim->load        = 1;
		anim->bitmap      = new uint32_t[(const int)(JPG->height*JPG->width)];
		anim->elem_num    = Elem_num;
		anim->elem_height = Elem_h;
		anim->elem_width  = Elem_w;
		anim->elem_y      = new u16[(const u32)Elem_num];
		anim->elem_x      = new u16[(const u32)Elem_num];
		anim->chromakey   = ChromaKey;
		anim->bitmap_width= JPG->width;

		memcpy(anim->bitmap,JPG->bmp_out, JPG->height*JPG->width*sizeof(uint32_t));
		Elem_num++;
		for(u16 k=0,j=0;k<JPG->height && j<Elem_num;k+=Elem_h){
			for(u16 i=0;i<JPG->width && j<Elem_num;i+=Elem_w, j++){
				anim->elem_x[j] = i;
				anim->elem_y[j] = k;
			}
		}
	}
	return;

}

void Animation::ClearAnimation(NoRSX_Animation *anim){
	if(anim->load){
		anim->load = 0;
		free(anim->bitmap);
		free(anim->elem_y);
		free(anim->elem_x);
		delete [] anim->bitmap;
	}
	return;
}

void Animation::DrawAnimation (int X, int Y, uint32_t frame, NoRSX_Animation *anim){
	if(anim->load){
		frame = frame%anim->elem_num;

		u32 *screen = (uint32_t *)G->buffer;
		u32 *bitmap = (uint32_t *)anim->bitmap;


		if(Y*G->height+X>=G->height*G->width)
			return;

		screen += Y*G->width+X;
		bitmap += anim->elem_x[frame]+anim->elem_y[frame]*anim->bitmap_width;

		drawing_width  = anim->elem_width;
		drawing_height = anim->elem_height;
		
		if(drawing_width +X>=G->width)
			drawing_width  = G->width -X-1;
		if(drawing_height+Y>=G->height)
			drawing_height = G->height-Y-1;
			
		for(u16 n=0;n<drawing_height;n++){
			for(u16 m=0;m<drawing_width;m++){
				u32 a = bitmap[m];
				if(a!=anim->chromakey)
					screen[m] = a;
			}
			bitmap += anim->bitmap_width;
			screen += G->width;
		}
	}
	return;
}

void Animation::AlphaDrawAnimation (int x, int y, uint32_t frame, NoRSX_Animation *anim){
	if(anim->load){
		frame = frame%anim->elem_num;
		u32 *screen = (u32 *)G->buffer;
		u32 *bitmap = (u32 *)anim->bitmap;


		if(((y*G->height)+x)>=(G->height*G->width))
			return;

		screen += y*G->width+x;
		bitmap += anim->elem_x[frame]+anim->elem_y[frame]*anim->bitmap_width;

		drawing_width  = anim->elem_width;
		drawing_height = anim->elem_height;
		if(drawing_width +x>=G->width)
			drawing_width  = G->width -x-1;
		if(drawing_height+y>=G->height)
			drawing_height = G->height-y-1;

		while(drawing_height>0){
			for(u16 m=0;m < drawing_width;m++){
				u32 a = bitmap[m] >> 24; // alpha 
				u32 OxFF_A = 0xff - a;
				if (0 != a) 
					screen[m] = (bitmap[m] & 0xff000000) | ((((((bitmap[m] & 0x00ff00ff) * a) + ((screen[m] & 0x00ff00ff) *
						    (OxFF_A))) & 0xff00ff00)     | ((((bitmap[m] & 0x0000ff00) * a)   + ((screen[m] & 0x0000ff00) *
						    (OxFF_A))) & 0x00ff0000)) >> 8);
			}
			screen +=G->width;
			bitmap += anim->bitmap_width;
			drawing_height--;
		}
/*
		for(u16 n=0;n<drawing_height;n++){
			for(u16 m=0;m<drawing_width;m++){
				u32 a = bitmap[m] >> 24; // alpha 
				u32 OxFF_A = 0xff - a;
				if (0 != a) 
					screen[m] = (bitmap[m] & 0xff000000) | ((((((bitmap[m] & 0x00ff00ff) * a) + ((screen[m] & 0x00ff00ff) *
						    (OxFF_A))) & 0xff00ff00)     | ((((bitmap[m] & 0x0000ff00) * a)   + ((screen[m] & 0x0000ff00) *
						    (OxFF_A))) & 0x00ff0000)) >> 8);
			}
			bitmap += anim->bitmap_width;
			screen += G->width;
		}
*/
	}
	return;
}


