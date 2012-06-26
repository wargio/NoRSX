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
#include "NoRSX_Image_png.h"
#include "Sans_ttf.h"
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

//msgType MSG_OK = (msgType)(MSG_DIALOG_NORMAL | MSG_DIALOG_BTN_TYPE_OK | MSG_DIALOG_DISABLE_CANCEL_ON);

s32 main(s32 argc, const char* argv[])
{
	padInfo padinfo;
	padData paddata;
	sysUtilRegisterCallback(SYSUTIL_EVENT_SLOT0, eventHandler, NULL);

	ioPadInit(7);

	pngData png;
	
	NoRSX *GFX = new NoRSX(RESOLUTION_1280x720); //set defined screen resolution You can change it to: RESOLUTION_720x480 | RESOLUTION_720x576 | RESOLUTION_1280x720 | RESOLUTION_1920x1080
	Image IMG(GFX);
	Background BG(GFX);
	Object OBJ(GFX);
	Bitmap BMap(GFX);

	NoRSX_Bitmap Precalculated_Layer;	
	
	BMap.GenerateBitmap(&Precalculated_Layer); //Initialize the Bitmap
	
	Font F1(Sans_ttf,Sans_ttf_size ,GFX);   //Loaded from Memory
	Font F2("/dev_flash/data/font/SCE-PS3-VR-R-LATIN2.TTF" ,GFX);  //Loaded from File!
	

	IMG.LoadPNG_Buf(NoRSX_Image_png,NoRSX_Image_png_size, &png);
	u32 imgX =(GFX->width/2)-(png.width/2), imgY = (GFX->height/2)-(png.height/2);

	BG.MonoBitmap(0xb4e83a,&Precalculated_Layer); //a green hex color (you can use hex colors insted of COLOR_XXXXXXX)

	IMG.DrawIMGtoBitmap(imgX,imgY,&png,&Precalculated_Layer);

	OBJ.CircleToBitmap(500,500,50,COLOR_YELLOW,&Precalculated_Layer);


	F1.PrintfToBitmap(150,200,&Precalculated_Layer,COLOR_RED,"Screen %d x %d",GFX->width,GFX->height);
	F1.PrintfToBitmap(150,250,&Precalculated_Layer,COLOR_BLUE, 35,"Press X to exit!");
	F2.PrintfToBitmap(150,300,&Precalculated_Layer,COLOR_GREEN,20,"FreeType2 with TTF support :)");

	exitapp = 1;
	int frame=0;
	while(exitapp){
		static time_t starttime = 0;
		double fps = 0;
		if (starttime == 0) starttime = time (NULL);
		else fps = frame / difftime (time (NULL), starttime);
		ioPadGetInfo(&padinfo);
		if(padinfo.status[0]){
			ioPadGetData(0, &paddata);
			if(paddata.BTN_CROSS){
				exitapp = 0;
			}
		}


		BMap.DrawBitmap(&Precalculated_Layer);
/*		BG.Mono(0xb4e83a); //a green hex color (you can use hex colors insted of COLOR_XXXXXXX)
		IMG.DrawIMG(imgX,imgY,&png);
		OBJ.Circle(500,500,50,COLOR_YELLOW);

		F1.Printf(150,200,COLOR_RED,"Screen %d x %d",GFX->width,GFX->height);
		F1.Printf(150,250,COLOR_BLUE, 35,"Press X to exit!");
		F1.Printf(150,100,"FPS %f", fps);
		F2.Printf(150,300,COLOR_GREEN,20,"FreeType2 with TTF support :)");
*/
		F1.Printf(150,100,"FPS %f", fps);

		GFX->Flip();
		frame ++;
		sysUtilCheckCallback();
	}

	//You need to clean the Bitmap before exit
	BMap.ClearBitmap(&Precalculated_Layer);

	GFX->NoRSX_Exit();
	ioPadEnd();
	return 0;
}

