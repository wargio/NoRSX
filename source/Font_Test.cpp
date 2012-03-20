#include "Font_Test.h"
#include <string.h>
#include <cstdarg>
#include <stdio.h>


const char Alphabet[]={  'A','B','C','D','E','F','G','H','I','J','K','L','M'	//12
			,'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'	//13 (25)
			,',','.',';','!','?',' '				//6  (31)
			,'1','2','3','4','5','6','7','8','9','0'};		//10 (41)

Font::Font(Minimum *g):Image(g){
	LoadPNG_Buf(Font_Test_bin,Font_Test_bin_size,&P);
}

void Font::Print(u32 x, u32 y, const char *txt, unsigned int Color){
	unsigned int k,H,K;
	if (x>=0&&y>=0){
		for(unsigned int i=0; i<strlen(txt); i++){
			H=0; K=0;
			for(k=0; k < strlen(Alphabet) ; k++)
				if(txt[i]==Alphabet[k]) break;
			 if(k<=12){
				K=k;
			}else if(k>12){
				H=1;
				if(k>25){
					H=2;
					if(k>31){
						H=3;
						K=k-32;
					}else{
					 	K=k-26;
					}
				}else{
					K=k-13;
				}
			}
			
			DrawPartialImage(x+(i*24), y, K*24, H*20, 24, 20, 0xffffffff, Color,&P);
		}
	}
}

void Font::Printf(u32 x, u32 y, unsigned int Color ,const char *a, ...){
	char msg[1024];
	va_list va;
	va_start(va, a);
	vsnprintf(msg, sizeof msg, a, va);
	Print(x,y, msg, Color);

}
