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


#ifndef __NORSX_MAIN_H__
#define __NORSX_MAIN_H__

#include <NoRSX/Image.h>
#include <NoRSX/Background.h>
#include <NoRSX/Objects.h>
#include <NoRSX/Font.h>
#include <NoRSX/Msg.h>
#include <NoRSX/Bitmap.h>
#include <NoRSX/EventHandler.h>
#include <NoRSX/Animation.h>
#include <NoRSX/Errors.h>
#include <NoRSX/Spu.h>

#include <NoRSX/Printf.h>

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <NoRSX/NoRSXutil.h>

#define RESOLUTION_1920x1080		1
#define RESOLUTION_1280x720		2
#define RESOLUTION_720x576		5
#define RESOLUTION_720x480		4


class NoRSX : public Minimum, public EventHandler{
public:

	 NoRSX();
	 NoRSX(int id_type);
	~NoRSX();
	
	void Flip();
	void NoRSX_Exit();

protected:
	void *host_addr;
	int id_scr;
};

#endif

