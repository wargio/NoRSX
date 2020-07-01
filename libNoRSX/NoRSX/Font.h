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

#ifndef __NORSX__FONT_H__
#define __NORSX__FONT_H__

#include <ft2build.h>

#include <NoRSX/Min.h>
#include <NoRSX/Colors.h>
#include <NoRSX/Bitmap.h>
#include <NoRSX/NoRSXutil.h>

#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_SYNTHESIS_H
#include FT_STROKER_H

#define CHROMAKEY          0x00000000
#define DEFAULT_FONT_SIZE  40

#define LATIN2  0
#define JPN     1
#define KOR     2
#define CGB     3
#define KANA    4

class Font{
public:
	Font(u32 Color, u32 Size, const void *MemFont, u32 MemFont_size, Minimum *min);
	Font(u32 Color, u32 Size, const char *Font_Path, Minimum *min);
	Font(u32 Size, const void *MemFont, u32 MemFont_size, Minimum *min);
	Font(u32 Size, const char *Font_Path, Minimum *min);
	Font(const void *MemFont, u32 MemFont_size, Minimum *min);
	Font(const char *Font_Path, Minimum *min);
	Font(const int system_font, Minimum *min);
	~Font();

	void ChangeFontColor(u32 color);
	void ChangeFontSize(u32 size);


	void Printf(u32 x, u32 y, const char *a, ...);
	void Printf(u32 x, u32 y, u32 Color, const char *a, ...);
	void Printf(u32 x, u32 y, u32 Color, u32 Size, const char *a, ...);
	void Disable_Fonts();

	void PrintfToBitmap(u32 x, u32 y, NoRSX_Bitmap* bmap, const char *a, ...);
	void PrintfToBitmap(u32 x, u32 y, NoRSX_Bitmap* bmap, u32 Color, const char *a, ...);
	void PrintfToBitmap(u32 x, u32 y, NoRSX_Bitmap* bmap, u32 Color, u32 Size, const char *a, ...);

protected:
	bool Kerning;
	FT_Byte *Pointer;
	const void *RPointer;
	s32 Lenght;
	FT_Library library;
	FT_Glyph glyph;
	FT_Stroker stroker;
	FT_Face face;
	FT_Bitmap *bitmap;
	FT_Vector vec;

	u32 FontColor;
	u32 FontSize;
	s32 width;
	s32 height;

	u32 color_depth;
	u32 color_pitch;
	u32 color_offset;
	
	int font;
	Minimum *m;

	void FontDrawBitmap(FT_Bitmap *bitmap, s32 offset, s32 top);
	void FontDrawBitmapToBitmap(FT_Bitmap *bitmap, NoRSX_Bitmap* bmap, s32 offset, s32 top);

};

#endif
