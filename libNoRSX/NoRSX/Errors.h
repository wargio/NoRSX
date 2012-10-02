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

#ifndef __NORSX_ERROR_LIST_H__
#define __NORSX_ERROR_LIST_H__

#define NORSX_OK			0

/*  NoRSX Main Errors*/
/*
#define NORSX_NO_ERROR			0xFF0E0000
#define NORSX_NOT_STARTED		0xFF0EDEAD
#define NORSX_ALREADY_STARTED		0xFF0EFAAD
#define NORSX_STARTED			0xFF0EFEED
*/


/*  SPU Errors  */
#define SPU_NO_ERROR			0xDEA00000
#define SPU_NOT_STARTED			0xDEA0DEAD
#define SPU_ALREADY_STARTED		0xDEA0FAAD
#define SPU_STARTED			0xDEA0FEED
#define SPU_ERROR_INIT			0xDEA00E0F
#define SPU_CANNOT_IMPORT_IMAGE		0xDEA0AE0F
#define SPU_CANNOT_OPEN_IMAGE		0xDEA0BE0F
#define SPU_CANNOT_LOAD_IMAGE		0xDEA0CE0F
#define SPU_CANNOT_CREATE_RAW		0xDEA0DE0F
#define SPU_CANNOT_DESTROY_RAW		0xDEA0EE0F
#define SPU_CANNOT_CLOSE_IMAGE		0xDEA0FE0F






#endif
