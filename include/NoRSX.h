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

HOW TO USE NoRSX

First init the lib as an object, by calling

NoRSX name();

then load all the lib function as objects; an example:

Image img(name);


LOADING AN IMAGE

Image(Minimum *g);
LoadPNG(const char* filename, pngData *png);
LoadJPG(const char* filename, jpgData *jpg);
LoadPNG_Buf(const void* name, u32 name_size, pngData *png);
LoadJPG_Buf(const void* name, u32 name_size, jpgData *jpg);
void DrawIMG(int x, int y, pngData *png1);
void DrawIMG(int x, int y, jpgData *jpg1);

COLORS AVAILABLES

COLOR_WHITE	
COLOR_BLACK	
COLOR_BLUE
COLOR_GREEN
COLOR_RED
COLOR_YELLOW
COLOR_CYAN
COLOR_GREY

colors use hexadecimal format; an example: COLOR_GREEN = 0x00FF00

GENERATE AN OBJECT
Object(Minimum *g);
Rectangle(u32 X, u32 Y, u32 width, u32 height, s32 Color);

USE A COLOURED BACKGROUND (NO GRADIENT FOR NOW)

Background(Minimum *g);
Mono(s32 Color);

*/


#ifndef __NORSX_MAIN_H__
#define __NORSX_MAIN_H__

#include "Image.h"
#include "Background.h"
#include "Objects.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "rsxutil.h"

class NoRSX : public Minimum{
public:

	 NoRSX();
	~NoRSX();
	
	void Flip();
	
protected:
	void *host_addr;

};

#endif

