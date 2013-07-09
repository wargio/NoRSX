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

#ifndef __NORSX_MSG_DIALOG_H__
#define __NORSX_MSG_DIALOG_H__
#include <NoRSX/Min.h>
#include <sysutil/msg.h>
#include <sysutil/sysutil.h>


class MsgDialog{
public:
	 MsgDialog(Minimum *g);
	~MsgDialog();

	int  GetResponse(vs32 button);
	void Dialog(msgType md, const char *message);

	void ErrorDialog(u32 errorCode);
	void TimerDialog(msgType md, const char *message, u32 Milliseconds);
	void TimerErrorDialog(u32 errorCode, u32 Milliseconds);

	void SingleProgressBarDialog(const char *dialog_message, const char* bar_message);
	void SingleProgressBarDialogIncrease(u32 percent);
	void SingleProgressBarDialogChangeMessage(const char* bar_message);

	void DoubleProgressBarDialog(const char *dialog_message, const char* bar1_message, const char* bar2_message);
	void DoubleProgressBarDialogChangeMessageFirstBar(const char* bar_message);
	void DoubleProgressBarDialogChangeMessageSecondBar(const char* bar_message);
	void DoubleProgressBarDialogIncreaseFirstBar(u32 percent);
	void DoubleProgressBarDialogResetFirstBar();
	void DoubleProgressBarDialogIncreaseSecondBar(u32 percent);

	void ProgressBarDialogFlip();  /*This is needed for both progress bar type*/
	void ProgressBarDialogAbort(); /*This is needed for both progress bar type*/

protected:
	Minimum *G;
};

#endif



