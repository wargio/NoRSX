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



