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

#define RESOLUTION_AUTO			0
#define RESOLUTION_1920x1080		1
#define RESOLUTION_1280x720		2
#define RESOLUTION_720x576		5
#define RESOLUTION_720x480		4
#define RESOLUTION_AUTO_LOWER_1080p	6
#define RESOLUTION_AUTO_LOWER_720p	7
#define RESOLUTION_AUTO_LOWER_576p	8


class NoRSX : public Minimum, public EventHandler{
public:

	 NoRSX();
	 NoRSX(int id_type);
	 NoRSX(int real_screen_type, int buffer_screen_type);
	~NoRSX();
	
	void Flip();
	void RescaleFlip();
	void NoRSX_Exit();

protected:
	void *host_addr;
	int  screen_type;
	int  buffer_type;
	void ScaleLine(u32 *Target, u32 *Source, u32 SrcWidth, u32 TgtWidth);
	void ResizeBuffer();
};

#endif

