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

msgType MSG_OK = (msgType)(MSG_DIALOG_NORMAL | MSG_DIALOG_BTN_TYPE_OK | MSG_DIALOG_DISABLE_CANCEL_ON);

s32 main(s32 argc, const char* argv[]) {
	padInfo padinfo;
	padData paddata;
	ioPadInit(7);

	int Bx = 0;
	int By = 0;

	pngData* png = new pngData;

	NoRSX* GFX = new NoRSX(RESOLUTION_AUTO, RESOLUTION_1280x720); //set defined screen resolution You can change it to:
	//RESOLUTION_720x480 | RESOLUTION_720x576 | RESOLUTION_1280x720 | RESOLUTION_1920x1080
	Image IMG(GFX);
	Background BG(GFX);
	Object OBJ(GFX);
	Bitmap BMap(GFX);
	MsgDialog Msg(GFX);

	NoRSX_Bitmap Precalculated_Layer;

	BMap.GenerateBitmap(&Precalculated_Layer); //Initialize the Bitmap

	Font F1(Sans_ttf, Sans_ttf_size, GFX); //Loaded from Memory
	Font F2("/dev_flash/data/font/SCE-PS3-VR-R-LATIN2.TTF", GFX); //Loaded from File!
	Font F3(JPN, GFX); //I'm Using PS3 Original Fonts! These are the available on the ps3: LATIN2 | JPN | KOR | CGB | KANA

	IMG.LoadPNG_Buf(NoRSX_Image_png, NoRSX_Image_png_size, png);

	png = IMG.ResizeImage(png, 500, 500); //pngData* IMG.ResizeImage(pngData*, new width, new height)

	u32 imgX = (GFX->width / 2) - (png->width / 2), imgY = (GFX->height / 2) - (png->height / 2);

	BG.MonoBitmap(0xb4e83a, &Precalculated_Layer); //a green hex color (you can use hex colors insted of COLOR_XXXXXXX)

	//	IMG.DrawIMGtoBitmap(imgX,imgY,png,&Precalculated_Layer);

	OBJ.CircleToBitmap(500, 500, 50, COLOR_YELLOW, &Precalculated_Layer);

	F1.PrintfToBitmap(150, 200, &Precalculated_Layer, COLOR_RED, "Screen %d x %d", GFX->width, GFX->height);
	F1.PrintfToBitmap(150, 250, &Precalculated_Layer, COLOR_BLUE, 35, "Press X to exit! (Start to skip Message Dialogs and exit)");
	F2.PrintfToBitmap(150, 300, &Precalculated_Layer, COLOR_GREEN, 60, "FreeType2 with TTF support :)");
	F3.PrintfToBitmap(150, 500, &Precalculated_Layer, "Written by deroad");

	int frame = 0;
	// Bitmap

	GFX->AppStart();
	while (GFX->GetAppStatus()) {
		static time_t starttime = 0;
		double fps = 0;
		if (starttime == 0)
			starttime = time(NULL);
		else
			fps = frame / difftime(time(NULL), starttime);
		ioPadGetInfo(&padinfo);
		if (padinfo.status[0]) {
			ioPadGetData(0, &paddata);
			if (paddata.BTN_TRIANGLE) {
				GFX->AppExit();
				break;
			}
			if (paddata.BTN_START) {
				GFX->AppExit();
				goto end;
			}
		}
		BMap.DrawBitmap(&Precalculated_Layer);
		IMG.DrawIMG(imgX, imgY, png);
		F1.Printf(150, 100, COLOR_RED, 60, "FPS %f", fps);

		GFX->Flip();
		frame++;
	}

	GFX->AppStart();
	while (GFX->GetAppStatus()) {
		static time_t starttime = 0;
		double fps = 0;
		if (starttime == 0)
			starttime = time(NULL);
		else
			fps = frame / difftime(time(NULL), starttime);
		ioPadGetInfo(&padinfo);
		if (padinfo.status[0]) {
			ioPadGetData(0, &paddata);
			if (paddata.BTN_TRIANGLE) {
				GFX->AppExit();
				break;
			}
			if (paddata.BTN_START) {
				GFX->AppExit();
				goto end;
			}
		}
		BG.Mono(0xb4e83a);
		F1.Printf(150, 100, COLOR_RED, 60, "FPS %f", fps);
		F1.Printf(150, 200, COLOR_RED, "Screen %d x %d", GFX->width, GFX->height);
		F1.Printf(150, 250, COLOR_BLUE, 35, "Press /\\ to exit! (Start to skip Message Dialogs and exit)");
		F2.Printf(150, 300, COLOR_GREEN, 60, "FreeType2 with TTF support :)");
		F3.Printf(150, 500, "Written by deroad");
		IMG.DrawIMG(imgX, imgY, png);
		GFX->RescaleFlip();
		frame++;
	}
	if (GFX->ExitSignalStatus()) {
		goto end;
	}

	//You need to clean the Bitmap before exit
	BMap.ClearBitmap(&Precalculated_Layer);

	Msg.TimerErrorDialog(0xdeadbeef, 5000.f);

	Msg.TimerDialog(MSG_OK, "Timer Dialog!", 5000.f);
	Msg.TimerErrorDialog(0xdeadbeef, 5000.f);

	GFX->AppStart();
	frame = 0;
	Msg.SingleProgressBarDialog("Single progress bar!! (start to exit)", "Deroad Bar text");
	while (GFX->GetAppStatus() && Bx < 100) {
		ioPadGetInfo(&padinfo);
		if (padinfo.status[0]) {
			ioPadGetData(0, &paddata);
			if (paddata.BTN_START) {
				GFX->AppExit();
				goto end;
			}
		}
		Msg.ProgressBarDialogFlip();
		frame++;
		if (frame % 55 == 0) {
			Msg.SingleProgressBarDialogIncrease(10);
			Bx += 10;
		}
	}
	Msg.ProgressBarDialogAbort();

	GFX->AppStart();
	Msg.DoubleProgressBarDialog("Double progress bar!! (start to exit)", "Deroad Bar1 text", "Deroad Bar2 text");
	Bx = 0;
	By = 0;
	while (GFX->GetAppStatus() && By <= 100) {
		ioPadGetInfo(&padinfo);
		if (padinfo.status[0]) {
			ioPadGetData(0, &paddata);
			if (paddata.BTN_START) {
				GFX->AppExit();
				goto end;
			}
		}
		Msg.ProgressBarDialogFlip();
		frame++;
		if (frame % 55 == 0) {
			Bx += 10;
			Msg.DoubleProgressBarDialogIncreaseFirstBar(10);
		}

		if (Bx > 100) {
			Bx = 0;
			Msg.DoubleProgressBarDialogResetFirstBar();
			Msg.DoubleProgressBarDialogIncreaseSecondBar(20);
			By += 20;
		}
	}
	Msg.ProgressBarDialogAbort();
end:
	GFX->NoRSX_Exit();
	ioPadEnd();
	return 0;
}
