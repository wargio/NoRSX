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

#define CHROMAKEY		0x00ffffff
#define LINE_INDENT		40
#define LINE_SIZE		40

class Fonts{
public:
	Fonts(u32 Color, u32 Size,const void *MemFont, u32 MemFont_size, Minimum *min);
//	Fonts(u32 BackGround, u32 Color, u32 Size, char *Font_Path, Min *min);
	~Fonts();
	u32 BackGroundColor;
	u32 FontColor;
	u32 FontSize;
//	char* FontPath;
	s32 width;
	s32 height;
	void Printf(u32 x, u32 y,const char *a, ...);
	u32 color_depth;
	u32 color_pitch;
	u32 color_offset;
	void DrawFont();
	void Disable_Fonts();
protected:
	bool Kerning;
	FT_Byte *Pointer;
	s32 Lenght;
	FT_Library library;
	FT_Glyph glyph;
	FT_Stroker stroker;
	FT_Face face;
	FT_Bitmap *bitmap;
	FT_Vector vec;
	
	int disabled_font;
	Minimum *m;

	void FontDrawBitmap(FT_Bitmap *bitmap, s32 offset, s32 top);
	void Draw(FT_Bitmap *bitmap, s32 offset, s32 top);

};

#endif
