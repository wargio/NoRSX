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

#include "Image.h"
#include "Background.h"
#include "Objects.h"
#include "Font.h"
#include "Msg.h"
#include "Bitmap.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "rsxutil.h"

#define RESOLUTION_1920x1080		1
#define RESOLUTION_1280x720		2
#define RESOLUTION_720x576		5
#define RESOLUTION_720x480		4


class NoRSX : public Minimum{
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

