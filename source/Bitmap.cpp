#include "Bitmap.h"


void Bitmap::GenerateBitmap(NoRSX_Bitmap *a){
	a->bitmap = new uint32_t[(sizeof(u32) * G->width * G->height)];
}

void Bitmap::ClearBitmap(NoRSX_Bitmap *a){
	free(a->bitmap);
}

void Bitmap::RegenBitmap(NoRSX_Bitmap *a){
	delete [] a->bitmap;
	a->bitmap = new uint32_t[(sizeof(u32) * G->width * G->height)];
}

void Bitmap::DrawBitmap(NoRSX_Bitmap *a){
	s32 i, j;
	for(i = 0; i < G->buffers[G->currentBuffer].height; i++) {
		for(j = 0; j < G->buffers[G->currentBuffer].width; j++)
			G->buffers[G->currentBuffer].ptr[i* G->buffers[G->currentBuffer].width + j] = a->bitmap[i* G->buffers[G->currentBuffer].width + j];
	}
}
