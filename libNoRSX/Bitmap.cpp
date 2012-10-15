
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

#include <NoRSX/Bitmap.h>
#include <NoRSX/NoRSXutil.h>
void Bitmap::GenerateBitmap(NoRSX_Bitmap *a){
	a->bitmap = new uint32_t[G->width * G->height];
	a->height = G->height;
	a->width  = G->width;
	a->load = 1;
}

void Bitmap::GenerateCustomBitmap(uint32_t width, uint32_t height, NoRSX_Bitmap *a){
	a->bitmap = new uint32_t[width*height];

	a->height = height;
	a->width  = width;

	a->load = 1;
}

void Bitmap::ClearBitmap(NoRSX_Bitmap *a){
	if(a->load==1){
		free(a->bitmap);
		a->load = 0;
	}
}

void Bitmap::RegenBitmap(NoRSX_Bitmap *a){
	if(a->load==1){
		free(a->bitmap);
		a->bitmap = new uint32_t[(sizeof(u32) * G->width * G->height)];
	}else{
		a->bitmap = new uint32_t[(sizeof(u32) * G->width * G->height)];
		a->load = 1;
	}
}

void Bitmap::DrawBitmap(NoRSX_Bitmap *a){
	if(a->load==1){
		s32 size = G->buffers[G->currentBuffer].height * G->buffers[G->currentBuffer].width;
		for(s32 i = 0; i < size; i++) {
			G->buffers[G->currentBuffer].ptr[i] = a->bitmap[i];
		}
	}
}

void Bitmap::DrawCustomBitmap(uint32_t start_width, uint32_t start_height, uint32_t end_width, uint32_t end_height, NoRSX_Bitmap *a){
	if(a->load==1){
		s32 size = G->buffers[G->currentBuffer].height * G->buffers[G->currentBuffer].width;
		u32 pos = start_height*a->width+start_width;
		for(s32 i = 0; i < size; i++) {
			G->buffers[G->currentBuffer].ptr[i] = a->bitmap[pos+i];
		}
	}
}
