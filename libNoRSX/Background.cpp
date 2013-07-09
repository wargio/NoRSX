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
		G->buffer[i] = Color;
	}
}

void Background::MonoBitmap(u32 Color, NoRSX_Bitmap *a){
	s32 size = G->height * G->width;
	for(s32 i = 0; i < size; i++) {
		a->bitmap[i] = Color;
	}
}


void Background::Gradient(u32 Color1, u32 Color2){ //G->buffer[i]
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

		G->buffer[i] = COLOR_TO_RGB(red,green,blue);
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


