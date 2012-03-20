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
#include "Min.h"
#include <sysutil/msg.h>
#include <sysutil/sysutil.h>


class MsgDialog{
public:
	 MsgDialog(Minimum *g);
	~MsgDialog();

	void Dialog(msgType md, const char *message);
	int  GetResponse(vs32 button);
protected:
	Minimum *G;
};

#endif



