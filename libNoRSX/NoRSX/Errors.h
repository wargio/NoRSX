/*
 * Copyright (c) 2013, Giovanni Dante Grazioli (deroad)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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
