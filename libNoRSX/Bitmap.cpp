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

#include <NoRSX/Bitmap.h>
#include <NoRSX/NoRSXutil.h>

void Bitmap::GenerateBitmap(NoRSX_Bitmap *a){
	a->bitmap = (u32*) rsxMalloc(G->width * G->height*sizeof(u32));
	a->height = G->height;
	a->width  = G->width;
	a->load = 1;
}

void Bitmap::GenerateCustomBitmap(uint32_t width, uint32_t height, NoRSX_Bitmap *a){
	a->bitmap = (u32*)rsxMalloc(width*height*sizeof(u32));

	a->height = height;
	a->width  = width;

	a->load = 1;
}

void Bitmap::ClearBitmap(NoRSX_Bitmap *a){
	if(a->load==1){
		rsxFree(a->bitmap);
		a->load = 0;
	}
}

void Bitmap::RegenBitmap(NoRSX_Bitmap *a){
	if(a->load==1){
		rsxFree(a->bitmap);
		a->bitmap = (u32*)rsxMalloc(G->width * G->height*sizeof(u32));
	}else{
		a->bitmap = (u32*)rsxMalloc(G->width * G->height*sizeof(u32));
		a->load = 1;
	}
}

void Bitmap::DrawBitmap(NoRSX_Bitmap *a){
	if(a->load==1){
		s32 size = G->height * G->width * sizeof(u32);
		memcpy(G->buffer,a->bitmap,size);
	}
}

void Bitmap::DrawCustomBitmap(uint32_t start_width, uint32_t start_height, uint32_t end_width, uint32_t end_height, NoRSX_Bitmap *a){
	if(a->load==1){
		s32 size = G->height * G->width;
		u32 pos = start_height*a->width+start_width;
		for(s32 i = 0; i < size; i++) {
			G->buffer[i] = a->bitmap[pos+i];
		}
	}
}
