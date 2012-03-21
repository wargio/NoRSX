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
#include "NoRSX_Image_bin.h"
#include <time.h>

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

msgType MSG_OK = (msgType)(MSG_DIALOG_NORMAL | MSG_DIALOG_BTN_TYPE_OK | MSG_DIALOG_DISABLE_CANCEL_ON);

s32 main(s32 argc, const char* argv[])
{
	padInfo padinfo ;
	padData paddata ;
	int i;
	sysUtilRegisterCallback(SYSUTIL_EVENT_SLOT0, eventHandler, NULL);

	ioPadInit(7);

	pngData png;
	
	NoRSX *GFX = new NoRSX();
	Image IMG(GFX);
	Background BG(GFX);
	Object OBJ(GFX);
	Font F(GFX);
	

	IMG.LoadPNG_Buf(NoRSX_Image_bin,NoRSX_Image_bin_size, &png);
	u32 imgX =(GFX->width/2)-(png.width/2), imgY = (GFX->height/2)-(png.height/2);
	exitapp = 1;
	int frame=0;
	while(exitapp){
		static time_t starttime = 0;
		double fps = 0;
		if (starttime == 0) starttime = time (NULL);
		else fps = frame / difftime (time (NULL), starttime);
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
		OBJ.Circle(400,900,100,COLOR_YELLOW);
		OBJ.Rectangle(500,400,200,500,COLOR_ORANGE);
		IMG.DrawIMG(imgX,imgY,&png);
		F.Printf(150,200,COLOR_BLACK,"SCREEN %d X %d",GFX->width,GFX->height);
		F.Print(150,250,COLOR_YELLOW,"PRESS X TO EXIT");
		F.Printf(150,100,COLOR_GREEN,"FPS %f", fps);
		GFX->Flip();
		frame ++;
		sysUtilCheckCallback();
	}
	GFX->NoRSX_Exit();
	ioPadEnd();
	return 0;
}

