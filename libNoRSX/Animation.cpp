#include "Animation.h"
#include <stdio.h>
#include <stdint.h>

void Animation::LoadAnimation (uint32_t Elem_num, uint32_t Elem_w, uint32_t Elem_h, uint32_t ChromaKey, pngData* PNG, NoRSX_Animation *anim){
	if(PNG->bmp_out && anim->load != 0){
		anim->load = 0;
		anim->bitmap = new uint32_t[(const int)(PNG->height*PNG->width)];
		anim->bitmap_height = PNG->height;
		anim->bitmap_width = PNG->width;
		anim->elem_num = Elem_num;
		anim->elem_height = Elem_h;
		anim->elem_width = Elem_w;
		anim->elem_y=0;
		anim->elem_x=0;
		anim->chromakey = ChromaKey;

		uint32_t *png = (uint32_t *)(void *)PNG->bmp_out;

		for(uint32_t y=0, i=0; y<PNG->height; y+=Elem_h){
			if(i>anim->elem_num)
				break;

			anim->elem_x=0;
			for(uint32_t x=0; x<PNG->width;i++,x+=Elem_w){
				if(i>anim->elem_num)
					break;

				anim->elem_x++;
			}
			anim->elem_y++;
		}
		for(u32 n=0, i=0;n < PNG->height;n++,i+=anim->bitmap_width){
			for(u32 m=0;m < PNG->width;m++)
				anim->bitmap[i+m]=png[m];
			png+=PNG->pitch>>2;
		}
	}
}


void Animation::LoadAnimation (uint32_t Elem_num, uint32_t Elem_w, uint32_t Elem_h, pngData* PNG, NoRSX_Animation *anim){
	if(PNG->bmp_out && anim->load != 0){
		anim->load = 0;
		anim->bitmap = new uint32_t[(const int)(PNG->height*PNG->width)];
		anim->bitmap_height = PNG->height;
		anim->bitmap_width = PNG->width;
		anim->elem_num = Elem_num;
		anim->elem_height = Elem_h;
		anim->elem_width = Elem_w;
		anim->elem_y=0;
		anim->elem_x=0;
		anim->chromakey = ANIMATION_ALPHA_CHROMAKEY;

		uint32_t *png = (uint32_t *)(void *)PNG->bmp_out;

		for(uint32_t y=0, i=0; y<PNG->height; y+=Elem_h){
			if(i>anim->elem_num)
				break;

			anim->elem_x=0;
			for(uint32_t x=0; x<PNG->width;i++,x+=Elem_w){
				if(i>anim->elem_num)
					break;

				anim->elem_x++;
			}
			anim->elem_y++;
		}
		for(u32 n=0, i=0;n < PNG->height;n++,i+=anim->bitmap_width){
			for(u32 m=0;m < PNG->width;m++)
				anim->bitmap[i+m]=png[m];
			png+=PNG->pitch>>2;
		}
	}
}

void Animation::LoadAnimation (uint32_t Elem_num, uint32_t Elem_w, uint32_t Elem_h, uint32_t ChromaKey, jpgData* JPG, NoRSX_Animation *anim){
	if(JPG->bmp_out && anim->load != 0){
		anim->load = 0;
		anim->bitmap = new uint32_t[(const int)(JPG->height*JPG->width)];
		anim->bitmap_height = JPG->height;
		anim->bitmap_width = JPG->width;
		anim->elem_num = Elem_num;
		anim->elem_height = Elem_h;
		anim->elem_width = Elem_w;
		anim->elem_y=0;
		anim->elem_x=0;
		anim->chromakey = ChromaKey;
		for(uint32_t y=0, i=0; y<JPG->height || i<=anim->elem_num; y+=Elem_h,i++){
			for(uint32_t x=0; x<JPG->width || i<=anim->elem_num; x+=Elem_w,i++){
				anim->elem_x++;
			}
			anim->elem_y++;
		}
		uint32_t *jpg = (uint32_t *)(void *)JPG->bmp_out;
		for(u32 n=0;n < JPG->height;n++){
			for(u32 m=0;m < JPG->width;m++)
				anim->bitmap[m]=jpg[m];
			jpg+=JPG->pitch>>2;
			anim->bitmap+=anim->bitmap_width;
		}
	}
}

void Animation::CleanAnimation(NoRSX_Animation *anim){
	if(anim->load){
		anim->load = 1;
		free(anim->bitmap);
		delete [] anim->bitmap;
	}
}

void Animation::DrawAnimation (uint32_t X, uint32_t Y, uint32_t frame, NoRSX_Animation *anim){
	if(anim->load==0 && !(frame < 0)){
		uint32_t size = G->height*G->width, scr = Y*G->height+X, y_pos = 0;
		if(scr>=size)
			scr = size;

		if(frame > anim->elem_num)
			frame = anim->elem_num;

		while(frame >= anim->elem_x){
			frame -=anim->elem_x;
			y_pos++;
		}

		u32 *screen = (uint32_t *)G->buffers[G->currentBuffer].ptr;
		u32 *bitmap = (uint32_t *)anim->bitmap;
		uint32_t n, m,j, pos = 0;

		screen += Y*G->width+X;
		pos = (frame*anim->elem_width)+(y_pos*anim->bitmap_height*anim->elem_width);
		for(n=0;n<anim->elem_height;n++){
			for(m=0,j=0;m<anim->elem_width;m++,j++){
				if(bitmap[pos+m]!=anim->chromakey)
					screen[j]=bitmap[pos+m];
			}
			pos += anim->bitmap_width;
			screen+=G->width;
		}

	}
}

void Animation::AlphaDrawAnimation (uint32_t X, uint32_t Y, uint32_t frame, NoRSX_Animation *anim){
	if(anim->load==0 && !(frame < 0)){
		uint32_t size = G->height*G->width, scr = Y*G->height+X, y_pos = 0;
		if(scr>=size)
			scr = size;

		if(frame > anim->elem_num)
			frame = anim->elem_num;

		while(frame >= anim->elem_x){
			frame -=anim->elem_x;
			y_pos++;
		}

		u32 *screen = (uint32_t *)G->buffers[G->currentBuffer].ptr;
		u32 *bitmap = (uint32_t *)anim->bitmap;
		uint32_t n, m, j, pos = 0;

		screen += Y*G->width+X;
		pos = y_pos*(anim->bitmap_height*anim->elem_width)+(frame*anim->elem_width);
		for(n=0;n<anim->elem_height;n++){
			for(m=0,j=0;m<anim->elem_width;m++,j++){
				unsigned int a = bitmap[pos+m] >> 24; // alpha 
				u32 OxFF_A = 0xff - a;
				if (0 != a) 
					screen[j] = (bitmap[pos+m] & 0xff000000) | ((((((bitmap[pos+m] & 0x00ff00ff) * a) + ((screen[j] & 0x00ff00ff) *
						    (OxFF_A))) & 0xff00ff00)     | ((((bitmap[pos+m] & 0x0000ff00) * a)   + ((screen[j] & 0x0000ff00) *
						    (OxFF_A))) & 0x00ff0000)) >> 8);

			}
			pos += anim->bitmap_width;
			screen+=G->width;
		}

	}
}


