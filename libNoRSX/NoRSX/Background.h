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

#ifndef __NORSX_BACKGROUND_H__
#define __NORSX_BACKGROUND_H__
#include "Min.h"
#include "Colors.h"
#include "Bitmap.h"

class Background{
public:
	 Background(Minimum *g);
	~Background(){}

	void Mono(u32 Color);
	void Gradient(u32 Color1, u32 Color2);

	void MonoBitmap(u32 Color, NoRSX_Bitmap *a);
	void GradientBitmap(u32 Color1, u32 Color2, NoRSX_Bitmap *a);


protected:
	int frame;
	Minimum *G;
};

#endif
