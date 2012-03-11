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
	Background BG(GFX);
	Object OBJ(GFX);
	
	IMG.LoadPNG_Buf((void*)psl1ght_png_bin, psl1ght_png_bin_size, &png);
	u32 x=(GFX->width/2)-(png.width/2),y=(GFX->height/2)-(png.height/2);
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
		BG.Mono(COLOR_GREY);
		OBJ.Rectangle(260,100,570,100,COLOR_BLUE);
		OBJ.Rectangle(300,150,200,400,COLOR_GREEN);
		OBJ.Rectangle(20,650,58,90,COLOR_YELLOW);
		OBJ.Rectangle(1060,600,300,300,COLOR_CYAN);
		IMG.DrawIMG(x,y,&png);
		GFX->Flip();

		sysUtilCheckCallback(); // check user attention span
	}

	ioPadEnd();
	return 0;
}

