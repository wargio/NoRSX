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

#ifndef __NORSX_OBJ_H__
#define __NORSX_OBJ_H__
#include "Min.h"
#include "Colors.h"
#include "Bitmap.h"

class Object{
public:
	 Object(Minimum *g);
	~Object(){}
	
	void Rectangle(u32 X, u32 Y, u32 width, u32 height, u32 Color);
	void Circle(u32 X, u32 Y, u32 r, u32 Color);
	void Line(u32 X, u32 Y, u32 X1, u32 Y1, u32 Color);
	void Pixel4(u32 X, u32 Y, u32 Color);

	void RectangleToBitmap(u32 X, u32 Y, u32 width, u32 height, u32 Color, NoRSX_Bitmap *a);
	void CircleToBitmap(u32 X, u32 Y, u32 r, u32 Color, NoRSX_Bitmap *a);
	
	
private:
	Minimum *G;
	int Pixel(u32 X, u32 Y, u32 Color);
	int PixelToBuffer(u32 X, u32 Y, u32 Color, NoRSX_Bitmap *a);
};

#endif
