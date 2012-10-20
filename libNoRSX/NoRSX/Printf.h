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

#ifndef __NORSX_PRINTF__
#define __NORSX_PRINTF__
#include <fstream>

/*
 * 
 * This will allow to write a debug message into a file
 * as the first thing, you will need to call init_print(filename);
 * then you can use print(...)
 * before closing the homebrew, call end_print()
 * 
 */

class Printf{
public:
	 Printf(const char* filename);
	~Printf();
	int printf(const char *a, ...);
protected:
	std::fstream f;
	int can_print;
};
#endif
