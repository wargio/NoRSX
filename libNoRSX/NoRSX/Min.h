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

#ifndef __NORSX_MIN_H__
#define __NORSX_MIN_H__
#include <NoRSX/NoRSXutil.h>
#include <ppu-types.h>
#include <ppu_intrinsics.h>
#include <cstring>


class Minimum{
public:
	u16 width;
	u16 height;

	rsxBuffer buffers[2];
	gcmContextData *context;
	int currentBuffer;
};

#endif


