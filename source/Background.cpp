#include "Background.h"

Background::Background(Minimum *g){
	G=g;
	frame=0;
}

void Background::Mono(s32 Color){
	s32 i, j;
	for(i = 0; i < G->buffers[G->currentBuffer].height; i++) {
		for(j = 0; j < G->buffers[G->currentBuffer].width; j++)
			G->buffers[G->currentBuffer].ptr[i* G->buffers[G->currentBuffer].width + j] = Color;
	}
}
/*
void Background::DoubleGradient(s32 Color1, s32 Color2){
	s32 i, j;
	for(i = 0; i < G->buffers[G->currentBuffer].height; i++) {
		s32 color = (s32)(double(Color1)-double((Color2*i)/G->buffers[G->currentBuffer].height));
		for(j = 0; j < G->buffers[G->currentBuffer].width; j++)
			G->buffers[G->currentBuffer].ptr[i* G->buffers[G->currentBuffer].width + j] = color;
	}
}
*/


