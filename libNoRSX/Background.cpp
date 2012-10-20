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

#include <NoRSX/Background.h>

#define COLOR_TO_ARGB(alpha, red, green, blue) (((alpha) << 24) | ((red) << 16) | ((green) << 8) | (blue))
#define COLOR_TO_RGB(red, green, blue) (((red) << 16) | ((green) << 8) | (blue))

#define VALUE_TO_ARGB(value) (((value) << 24) | ((value) << 16) | ((value) << 8) | (value))
#define VALUE_TO_RGB(value) (((value) << 16) | ((value) << 8) | (value))

#define A(argb)  (((argb) >> 24) & 0xFF)
#define R(argb)  (((argb) >> 16) & 0xFF)
#define G(argb)  (((argb) >>  8) & 0xFF)
#define B(argb)  ((argb)         & 0xFF)

Background::Background(Minimum *g){
	G=g;
	frame=0;
}

void Background::Mono(u32 Color){
	s32 size = G->height * G->width;
	for(s32 i = 0; i < size; i++) {
	G->buffers[G->currentBuffer].ptr[i] = Color;
	}
}

void Background::MonoBitmap(u32 Color, NoRSX_Bitmap *a){
	s32 size = G->height * G->width;
	for(s32 i = 0; i < size; i++) {
		a->bitmap[i] = Color;
	}
}


void Background::Gradient(u32 Color1, u32 Color2){ //G->buffers[G->currentBuffer].ptr[i]
	s32 size = G->height * G->width;
	u8 Color_Red   = R(Color2);
	u8 Color_Blue  = B(Color2);
	u8 Color_Green = G(Color2);

	u8 Color1_Red   = R(Color1);
	u8 Color1_Blue  = B(Color1);
	u8 Color1_Green = G(Color1);
	int percent_old = 0;
	for(s32 i = 0; i < size; i++){
		int percent = (i*100)/size;
		u8 red   = (Color1_Red  *(100-percent)/100) + (Color_Red  *percent/100);
		u8 blue  = (Color1_Blue *(100-percent)/100) + (Color_Blue *percent/100);
		u8 green = (Color1_Green*(100-percent)/100) + (Color_Green*percent/100);

		G->buffers[G->currentBuffer].ptr[i] = COLOR_TO_RGB(red,green,blue);
		if(percent_old!=percent){
			percent_old = percent;
		}
	}
}

void Background::GradientBitmap(u32 Color1, u32 Color2, NoRSX_Bitmap *a){
	u32 size = G->height * G->width;
	u8 Color_Red   = R(Color2);
	u8 Color_Blue  = B(Color2);
	u8 Color_Green = G(Color2);

	u8 Color1_Red   = R(Color1);
	u8 Color1_Blue  = B(Color1);
	u8 Color1_Green = G(Color1);
	int percent_old = 0;
	for(u32 i = 0; i < size; i++){
		int percent = (i*100)/size;
		u8 red   = (Color1_Red  *(100-percent)/100) + (Color_Red  *percent/100);
		u8 blue  = (Color1_Blue *(100-percent)/100) + (Color_Blue *percent/100);
		u8 green = (Color1_Green*(100-percent)/100) + (Color_Green*percent/100);

		a->bitmap[i] = COLOR_TO_RGB(red,green,blue);
		if(percent_old!=percent){
			percent_old = percent;
		}
	}
}


