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

#ifndef __NORSX_BITMAP_H__
#define __NORSX_BITMAP_H__

#include "Min.h"

typedef struct {
	uint32_t *bitmap;
	int load;
} NoRSX_Bitmap;

class Bitmap{
public:
	Bitmap(Minimum *g){
		G=g;
	}

	Bitmap(){

	}	

	void GenerateBitmap(NoRSX_Bitmap *a);
	void ClearBitmap(NoRSX_Bitmap *a);
	void RegenBitmap(NoRSX_Bitmap *a);
	void DrawBitmap(NoRSX_Bitmap *a);

	

private:
	Minimum *G;
};

#endif
