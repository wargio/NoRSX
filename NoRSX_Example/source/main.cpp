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

#include <NoRSX.h> //This is the new HEADER!!! Now it's a real new lib!!

#include "NoRSX_Image_png.h"
#include "Sans_ttf.h"
#include <time.h>


//msgType MSG_OK = (msgType)(MSG_DIALOG_NORMAL | MSG_DIALOG_BTN_TYPE_OK | MSG_DIALOG_DISABLE_CANCEL_ON);

s32 main(s32 argc, const char* argv[])
{
	padInfo padinfo;
	padData paddata;

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
	Font F3(JPN ,GFX);  //I'm Using PS3 Original Fonts! These are the available on the ps3: LATIN2 | JPN | KOR | CGB | KANA
	

	IMG.LoadPNG_Buf(NoRSX_Image_png,NoRSX_Image_png_size, &png);
	u32 imgX =(GFX->width/2)-(png.width/2), imgY = (GFX->height/2)-(png.height/2);

	BG.GradientBitmap(0xb4e83a,COLOR_RED,&Precalculated_Layer); //a green hex color (you can use hex colors insted of COLOR_XXXXXXX)

	IMG.DrawIMGtoBitmap(imgX,imgY,&png,&Precalculated_Layer);

	OBJ.CircleToBitmap(500,500,50,COLOR_YELLOW,&Precalculated_Layer);


	F1.PrintfToBitmap(150,200,&Precalculated_Layer,COLOR_RED,"Screen %d x %d",GFX->width,GFX->height);
	F1.PrintfToBitmap(150,250,&Precalculated_Layer,COLOR_BLUE, 35,"Press X to exit!");
	F2.PrintfToBitmap(150,300,&Precalculated_Layer,COLOR_GREEN,60,"FreeType2 with TTF support :)");
	F3.PrintfToBitmap(150,500,&Precalculated_Layer,"Written by deroad");

	GFX->AppStart();
	int frame=0;
	while(GFX->GetAppStatus()){
		static time_t starttime = 0;
		double fps = 0;
		if (starttime == 0) starttime = time (NULL);
		else fps = frame / difftime (time (NULL), starttime);
		ioPadGetInfo(&padinfo);
		if(padinfo.status[0]){
			ioPadGetData(0, &paddata);
			if(paddata.BTN_CROSS){
				GFX->AppExit();
			}
		}


		BMap.DrawBitmap(&Precalculated_Layer);
		F1.Printf(150,100,"FPS %f", fps);

		GFX->Flip();
		frame ++;
	}

	//You need to clean the Bitmap before exit
	BMap.ClearBitmap(&Precalculated_Layer);

	GFX->NoRSX_Exit();
	ioPadEnd();
	return 0;
}

