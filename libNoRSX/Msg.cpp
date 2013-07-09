/*
 * Copyright (c) 2013, Giovanni Dante Grazioli (deroad)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
*/

#include <NoRSX/Msg.h>

static vs32 dialog_action = 0;

static int i=0;

static void dialog_handler(msgButton button, void *usrdata){
	dialog_action = button;
}

void sysutil_callback(u64 status, u64 param, void *usrdata){
}


MsgDialog::MsgDialog(Minimum *g){
	G=g;
	sysUtilRegisterCallback(SYSUTIL_EVENT_SLOT1, sysutil_callback, NULL);

}

MsgDialog::~MsgDialog(){
	sysUtilUnregisterCallback(SYSUTIL_EVENT_SLOT1);
}

int MsgDialog::GetResponse(vs32 button){
	if(dialog_action == button){
		return 1;
	}
	return -1;
}

void MsgDialog::Dialog(msgType md, const char *message){
	msgDialogOpen2(md, message, dialog_handler, NULL, NULL);
	i=0;
	dialog_action = 0;
	while(dialog_action == 0){
		sysUtilCheckCallback();
		flip(G->context, i);
		waitFlip();
		i = !i;
	}
	
	msgDialogAbort();
}


void MsgDialog::ErrorDialog(u32 errorCode){
	msgDialogOpenErrorCode(errorCode,dialog_handler, NULL, NULL);

	dialog_action = 0;
	while(dialog_action == 0){
		sysUtilCheckCallback();
		flip(G->context, i);
		waitFlip();
		i = !i;
	}
	
	msgDialogAbort();
}

void MsgDialog::TimerDialog(msgType md, const char *message, u32 Milliseconds){
	msgDialogOpen2(md, message, dialog_handler, NULL, NULL);
	msgDialogClose(Milliseconds);
	i=0;
	dialog_action = 0;
	while(dialog_action == 0){
		sysUtilCheckCallback();
		flip(G->context, i);
		waitFlip();
		i = !i;
	}
	
	msgDialogAbort();
}

void MsgDialog::TimerErrorDialog(u32 errorCode, u32 Milliseconds){
	msgDialogOpenErrorCode(errorCode,dialog_handler, NULL, NULL);
	msgDialogClose(Milliseconds);
	i=0;
	dialog_action = 0;
	while(dialog_action == 0){
		sysUtilCheckCallback();
		flip(G->context, i);
		waitFlip();
		i = !i;
	}
	
	msgDialogAbort();
}

void MsgDialog::SingleProgressBarDialog(const char *dialog_message, const char* bar_message){
	msgDialogOpen2((msgType)(MSG_DIALOG_SINGLE_PROGRESSBAR | MSG_DIALOG_DISABLE_CANCEL_ON), dialog_message, dialog_handler, NULL, NULL);
	msgDialogProgressBarSetMsg(MSG_PROGRESSBAR_INDEX0,bar_message);
	msgDialogProgressBarReset(MSG_PROGRESSBAR_INDEX0);
	msgDialogProgressBarInc(MSG_PROGRESSBAR_INDEX0,0);
	i=0;
}


void MsgDialog::SingleProgressBarDialogIncrease(u32 percent){
	msgDialogProgressBarInc(MSG_PROGRESSBAR_INDEX0,percent);
}

void MsgDialog::DoubleProgressBarDialog(const char *dialog_message, const char* bar1_message, const char* bar2_message){
	msgDialogOpen2((msgType)(MSG_DIALOG_DOUBLE_PROGRESSBAR | MSG_DIALOG_DISABLE_CANCEL_ON), dialog_message, dialog_handler, NULL, NULL);
	msgDialogProgressBarSetMsg(MSG_PROGRESSBAR_INDEX0,bar1_message);
	msgDialogProgressBarReset(MSG_PROGRESSBAR_INDEX0);
	msgDialogProgressBarSetMsg(MSG_PROGRESSBAR_INDEX1,bar2_message);
	msgDialogProgressBarReset(MSG_PROGRESSBAR_INDEX1);
	msgDialogProgressBarInc(MSG_PROGRESSBAR_INDEX0,0);
	msgDialogProgressBarInc(MSG_PROGRESSBAR_INDEX1,0);
	i=0;
}

void MsgDialog::SingleProgressBarDialogChangeMessage(const char* bar_message){
	msgDialogProgressBarSetMsg(MSG_PROGRESSBAR_INDEX0,bar_message);
}

void MsgDialog::DoubleProgressBarDialogChangeMessageFirstBar(const char* bar_message){
	msgDialogProgressBarSetMsg(MSG_PROGRESSBAR_INDEX0,bar_message);
}

void MsgDialog::DoubleProgressBarDialogChangeMessageSecondBar(const char* bar_message){
	msgDialogProgressBarSetMsg(MSG_PROGRESSBAR_INDEX1,bar_message);
}

void MsgDialog::DoubleProgressBarDialogIncreaseFirstBar(u32 percent){
	msgDialogProgressBarInc(MSG_PROGRESSBAR_INDEX0,percent);
}

void MsgDialog::DoubleProgressBarDialogResetFirstBar(){
	msgDialogProgressBarReset(MSG_PROGRESSBAR_INDEX0);
}

void MsgDialog::DoubleProgressBarDialogIncreaseSecondBar(u32 percent){
	msgDialogProgressBarInc(MSG_PROGRESSBAR_INDEX1,percent);
}

void MsgDialog::ProgressBarDialogFlip(){
	sysUtilCheckCallback();
	flip(G->context, i);
	waitFlip();
	i = !i;
}

void MsgDialog::ProgressBarDialogAbort(){
	msgDialogAbort();
}

