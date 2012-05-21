#ifndef __NORSX__FONT_H__
#define __NORSX__FONT_H__

#include <ft2build.h>
//#include <freetype2/freetype/freetype.h>
#include "Min.h"
#include "Colors.h"
#include "rsxutil.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_SYNTHESIS_H
#include FT_STROKER_H

#define CHROMAKEY		0x000000ff
#define LINE_INDENT		40
#define LINE_SIZE		40

class Font{
public:
	Font(u32 Color, u32 Size, const void *MemFont, u32 MemFont_size, Minimum *min);
	Font(u32 Color, u32 Size, const char *Font_Path, Minimum *min);
	~Font();
	u32 FontColor;
	u32 FontSize;
	s32 width;
	s32 height;
	void Printf(u32 x, u32 y,const char *a, ...);
	u32 color_depth;
	u32 color_pitch;
	u32 color_offset;
	void Disable_Fonts();
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
	
	int font;
	Minimum *m;

	void FontDrawBitmap(FT_Bitmap *bitmap, s32 offset, s32 top);
	void Draw(FT_Bitmap *bitmap, s32 offset, s32 top);

};

#endif
