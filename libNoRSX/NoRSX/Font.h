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

#ifndef __NORSX__FONT_H__
#define __NORSX__FONT_H__

#include <ft2build.h>
//#include <freetype2/freetype/freetype.h>
#include <NoRSX/Min.h>
#include <NoRSX/Colors.h>
#include <NoRSX/Bitmap.h>
#include <NoRSX/NoRSXutil.h>


#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_SYNTHESIS_H
#include FT_STROKER_H

#define CHROMAKEY		0x00000000
#define DEFAULT_FONT_SIZE	40

#define LATIN2			0
#define JPN			1
#define KOR			2
#define CGB			3
#define KANA			4

class Font{
public:
	Font(u32 Color, u32 Size, const void *MemFont, u32 MemFont_size, Minimum *min);
	Font(u32 Color, u32 Size, const char *Font_Path, Minimum *min);
	Font(u32 Size, const void *MemFont, u32 MemFont_size, Minimum *min);
	Font(u32 Size, const char *Font_Path, Minimum *min);
	Font(const void *MemFont, u32 MemFont_size, Minimum *min);
	Font(const char *Font_Path, Minimum *min);
	Font(const int ID, Minimum *min);
	~Font();

	void ChangeFontColor(u32 color);
	void ChangeFontSize(u32 size);


	void Printf(u32 x, u32 y,const char *a, ...);
	void Printf(u32 x, u32 y, u32 Color,const char *a, ...);
	void Printf(u32 x, u32 y, u32 Color, u32 Size,const char *a, ...);
	void Disable_Fonts();

	void PrintfToBitmap(u32 x, u32 y, NoRSX_Bitmap* bmap,const char *a, ...);
	void PrintfToBitmap(u32 x, u32 y, NoRSX_Bitmap* bmap, u32 Color,const char *a, ...);
	void PrintfToBitmap(u32 x, u32 y, NoRSX_Bitmap* bmap, u32 Color, u32 Size,const char *a, ...);

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
