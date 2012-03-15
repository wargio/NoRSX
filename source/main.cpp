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

msgType MSG_OK = (msgType)(MSG_DIALOG_NORMAL | MSG_DIALOG_BTN_TYPE_OK | MSG_DIALOG_DISABLE_CANCEL_ON);

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

	ioPadInit(7);

	pngData png;
	
	NoRSX *GFX = new NoRSX();
	Image IMG(GFX);
	Background BG(GFX);
	Object OBJ(GFX);
	Font F(GFX);
	MsgDialog Msg(GFX);
	

	IMG.LoadPNG_Buf((void*)NoRSX_Image_bin, NoRSX_Image_bin_size, &png);
	u32 x=(GFX->width/2)-(png.width/2),y=(GFX->height/2)-(png.height/2);
	exitapp = 1;
	

	while(exitapp){
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
		OBJ.Rectangle(20,650,500,90,COLOR_YELLOW);
		OBJ.Rectangle(1060,600,300,300,COLOR_CYAN);
		IMG.DrawIMG(x,y,&png);
		F.Print(800,300,"DEROAD IS COOL, BUT NORSX IS BETTER!",COLOR_RED);
		F.Print(800,330,"1234567890ABCDEFGHILMNOPQRSTUVZ.,!?",COLOR_BLUE);
		GFX->Flip();

		sysUtilCheckCallback();
	}
	Msg.Dialog(MSG_OK, "This is the power of NoRSX\nThis lib was written by deroad http://devram0.blogspot.com/\n\nPress Cross (X) to exit");
//	Msg.GetResponse(MSG_DIALOG_BTN_OK)
	GFX->NoRSX_Exit();
	ioPadEnd();
	return 0;
}

