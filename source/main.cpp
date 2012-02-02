#include <io/pad.h>
#include "NoRSX.h"
#include "png_bin.h"


int main(int argc,const char *argv[])
{
	padInfo padinfo;
	padData paddata;
	NoRSX *rsx = new NoRSX();
	pngData a=rsx->LoadFromBuffer_PNG((void *)png_bin, png_bin_size);
	ioPadInit(7);

	while(rsx->Exit()) {
		rsx->CheckEvent();

		ioPadGetInfo(&padinfo);
		for(s32 i=0; i<MAX_PADS; i++){
			if(padinfo.status[i]){
				ioPadGetData(i, &paddata);

				if(paddata.BTN_CROSS){
					return 0;
				}
			}

		}
		rsx->DrawPNG(100,200,a);
		rsx->Flip();
	}
		
	return 0;
}
