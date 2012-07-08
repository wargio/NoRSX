#include <NoRSX/Bitmap.h>


void Bitmap::GenerateBitmap(NoRSX_Bitmap *a){
	a->bitmap = new uint32_t[(sizeof(u32) * G->width * G->height)];
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
		delete [] a->bitmap;
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
