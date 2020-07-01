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

typedef struct _timer {
	time_t start;
	u32 frame;
} counter_t;

typedef struct _joypads {
	padInfo padinfo;
	padData paddata;
} joypads_t;

double calculate_fps(counter_t* timer) {
	timer->frame++;
	if (timer->start != 0) {
		return timer->frame / difftime(time(NULL), timer->start);
	}
	timer->start = time(NULL);
	return 1;
}

int handle_pad_event(joypads_t* joypads) {
	ioPadGetInfo(&joypads->padinfo);
	if (joypads->padinfo.status[0]) {
		ioPadGetData(0, &joypads->paddata);
		if (joypads->paddata.BTN_TRIANGLE) {
			return 1;
		}
		if (joypads->paddata.BTN_START) {
			return 2;
		}
	}
	return 0;
}

int test_bitmap(NoRSX* GFX) {
	joypads_t joypads = { 0 };
	counter_t timer = { 0 };

	Font F1(Sans_ttf, Sans_ttf_size, GFX); //Loaded from Memory
	Font F2("/dev_flash/data/font/SCE-PS3-VR-R-LATIN2.TTF", GFX); //Loaded from File!
	Font F3(JPN, GFX); //I'm Using PS3 Original Fonts! These are the available on the ps3: LATIN2 | JPN | KOR | CGB | KANA
	Bitmap BMap(GFX);
	Background BG(GFX);
	Image IMG(GFX);
	Object OBJ(GFX);

	NoRSX_Bitmap Precalculated_Layer;
	pngData* png = new pngData;

	// Loading image from memory
	IMG.LoadPNG_Buf(NoRSX_Image_png, NoRSX_Image_png_size, png);

	pngData* newpng = IMG.ResizeImage(png, 500, 500); //pngData* IMG.ResizeImage(pngData*, new width, new height)

	u32 imgX = (GFX->width / 2) - (newpng->width / 2);
	u32 imgY = (GFX->height / 2) - (newpng->height / 2);

	BMap.GenerateBitmap(&Precalculated_Layer); //Initialize the Bitmap
	BG.MonoBitmap(0xb4e83a, &Precalculated_Layer); //a green hex color (you can use hex colors insted of COLOR_XXXXXXX)

	IMG.DrawIMGtoBitmap(imgX, imgY, newpng, &Precalculated_Layer);

	OBJ.CircleToBitmap(500, 500, 50, COLOR_YELLOW, &Precalculated_Layer);

	F1.PrintfToBitmap(150, 200, &Precalculated_Layer, COLOR_RED, "Screen %d x %d", GFX->width, GFX->height);
	F1.PrintfToBitmap(150, 250, &Precalculated_Layer, COLOR_BLUE, 35, "Press /\\ to exit! (Start to skip Message Dialogs and exit)");
	F2.PrintfToBitmap(150, 300, &Precalculated_Layer, COLOR_GREEN, 60, "FreeType2 with TTF support :)");
	F3.PrintfToBitmap(150, 500, &Precalculated_Layer, "Written by deroad");
	GFX->AppStart();
	while (GFX->GetAppStatus()) {

		double fps = calculate_fps(&timer);

		int event;
		if ((event = handle_pad_event(&joypads))) {
			GFX->AppExit();
			return event;
		}

		BMap.DrawBitmap(&Precalculated_Layer);
		F1.Printf(150, 100, COLOR_RED, 60, "FPS %f", fps);

		GFX->Flip();
	}

	//You need to clean the Bitmap before exit
	BMap.ClearBitmap(&Precalculated_Layer);

	delete newpng;
	delete png;

	return 0;
}

int test_generic(NoRSX* GFX) {
	joypads_t joypads = { 0 };
	counter_t timer = { 0 };

	Font F1(Sans_ttf, Sans_ttf_size, GFX); //Loaded from Memory
	Font F2("/dev_flash/data/font/SCE-PS3-VR-R-LATIN2.TTF", GFX); //Loaded from File!
	Font F3(JPN, GFX); //I'm Using PS3 Original Fonts! These are the available on the ps3: LATIN2 | JPN | KOR | CGB | KANA
	Image IMG(GFX);
	Background BG(GFX);

	pngData* png = new pngData;
	// Loading image from memory
	IMG.LoadPNG_Buf(NoRSX_Image_png, NoRSX_Image_png_size, png);

	GFX->AppStart();
	while (GFX->GetAppStatus()) {

		double fps = calculate_fps(&timer);

		int event;
		if ((event = handle_pad_event(&joypads))) {
			GFX->AppExit();
			return event;
		}

		BG.Mono(0xb4e83a);
		F1.Printf(150, 100, COLOR_RED, 60, "FPS %f", fps);
		F1.Printf(150, 200, COLOR_RED, "Screen %d x %d", GFX->width, GFX->height);
		F1.Printf(150, 250, COLOR_BLUE, 35, "Press /\\ to exit! (Start to skip Message Dialogs and exit)");
		F2.Printf(150, 300, COLOR_GREEN, 60, "FreeType2 with TTF support :)");
		F3.Printf(150, 500, "Written by deroad");
		IMG.DrawIMG(1000, 250, png);
		GFX->RescaleFlip();
	}

	delete png;

	return 0;
}

int test_error_dialog(NoRSX* GFX) {
	const msgType MSG_OK = (msgType)(MSG_DIALOG_NORMAL | MSG_DIALOG_BTN_TYPE_OK | MSG_DIALOG_DISABLE_CANCEL_ON);

	MsgDialog Msg(GFX);

	Msg.TimerErrorDialog(0xdeadbeef, 5000.f);
	Msg.TimerDialog(MSG_OK, "Timer Dialog!", 5000.f);
	Msg.TimerErrorDialog(0xdeadbeef, 5000.f);

	return 0;
}

int test_single_bar(NoRSX* GFX) {

	joypads_t joypads = { 0 };
	int frame = 0;

	MsgDialog Msg(GFX);

	int Bx = 0;
	GFX->AppStart();

	Msg.SingleProgressBarDialog("Single progress bar!! (start to exit)", "Deroad Bar text");
	while (GFX->GetAppStatus() && Bx < 100) {
		frame++;
		if (handle_pad_event(&joypads) == 2) {
			GFX->AppExit();
			return 2;
		}

		Msg.ProgressBarDialogFlip();
		if (frame % 55 == 0) {
			Msg.SingleProgressBarDialogIncrease(10);
			Bx += 10;
		}
	}
	Msg.ProgressBarDialogAbort();

	return 0;
}

int test_double_bar(NoRSX* GFX) {
	joypads_t joypads = { 0 };
	int frame = 0;

	MsgDialog Msg(GFX);

	Msg.DoubleProgressBarDialog("Double progress bar!! (start to exit)", "Deroad Bar1 text", "Deroad Bar2 text");
	int Bx = 0;
	int By = 0;

	GFX->AppStart();
	while (GFX->GetAppStatus() && By <= 100) {
		frame++;
		if (handle_pad_event(&joypads) == 2) {
			GFX->AppExit();
			return 2;
		}

		Msg.ProgressBarDialogFlip();
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

	return 0;
}

s32 main(s32 argc, const char* argv[]) {
	ioPadInit(7);

	NoRSX* GFX = new NoRSX(RESOLUTION_AUTO, RESOLUTION_1280x720); //set defined screen resolution You can change it to:
	//RESOLUTION_720x480 | RESOLUTION_720x576 | RESOLUTION_1280x720 | RESOLUTION_1920x1080

	if (test_bitmap(GFX) == 2 || GFX->ExitSignalStatus()) {
		goto end;
	}

	//if (test_generic(GFX) == 2 || GFX->ExitSignalStatus()) {
	//	goto end;
	//}

	//if (test_error_dialog(GFX) == 2 || GFX->ExitSignalStatus()) {
	//	goto end;
	//}

	//if (test_single_bar(GFX) == 2 || GFX->ExitSignalStatus()) {
	//	goto end;
	//}

	//if (test_double_bar(GFX) == 2 || GFX->ExitSignalStatus()) {
	//	goto end;
	//}

end:
	GFX->NoRSX_Exit();
	ioPadEnd();

	delete GFX;
	return 0;
}
