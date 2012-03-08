#include <io/pad.h>
#include "NoRSX.h"
#include "psl1ght_png_bin.h" // png in memory

#define PNG_FILE "/dev_usb/psl1ght_png.bin"

static int exitapp, xmbopen;

static inline void eventHandler(u64 status, u64 param, void * userdata)
{
	switch(status)
	{
		case SYSUTIL_EXIT_GAME:
			exitapp = 0;
			break;
		case SYSUTIL_MENU_OPEN:
			xmbopen = 1;
			break;
		case SYSUTIL_MENU_CLOSE:
			xmbopen = 0;
			break;
	}
}


s32 main(s32 argc, const char* argv[])
{
	padInfo padinfo ;
	padData paddata ;
	int i;
	sysUtilRegisterCallback(SYSUTIL_EVENT_SLOT0, eventHandler, NULL);

	ioPadInit(7) ;

	pngData png;
	
	NoRSX *GFX = new NoRSX();
	Image IMG(GFX);
//	LoadPNG_Buf(psl1ght_png_bin,&png);
	pngLoadFromBuffer((void*)psl1ght_png_bin, psl1ght_png_bin_size, &png);
	
	exitapp = 1;
	while(exitapp)
	{
		/* Check the pads. */
		ioPadGetInfo(&padinfo);
		for(i=0; i<MAX_PADS; i++){
			if(padinfo.status[i]){
				ioPadGetData(i, &paddata);

				if(paddata.BTN_CROSS){
					exitapp = 0;
				}
			}
		}
		IMG.DrawIMG(300,300,&png);
		GFX->Flip();

		sysUtilCheckCallback(); // check user attention span
	}

	ioPadEnd();
	return 0;
}

