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

#include <NoRSX/Font.h>

#define COLOR_TO_ARGB(alpha, red, green, blue) (((alpha) << 24) | ((red) << 16) | ((green) << 8) | (blue))
#define COLOR_TO_RGB(red, green, blue) (((red) << 16) | ((green) << 8) | (blue))

#define VALUE_TO_ARGB(value) (((value) << 24) | ((value) << 16) | ((value) << 8) | (value))
#define VALUE_TO_RGB(value) (((value) << 16) | ((value) << 8) | (value))

#define A(argb)  (((argb) >> 24) & 0xFF)
#define R(argb)  (((argb) >> 16) & 0xFF)
#define G(argb)  (((argb) >>  8) & 0xFF)
#define B(argb) ((argb)        & 0xFF)



Font::Font(u32 Color, u32 Size,const void *MemFont, u32 MemFont_size, Minimum *min){
	FontColor = Color;
	FontSize = Size;
	Pointer = (FT_Byte*)MemFont;
	Lenght = MemFont_size;
	m = min;

	FT_Init_FreeType(&library);
	FT_New_Memory_Face(library,Pointer,Lenght,0,&face);
	FT_Stroker_New(library,&stroker);
	Kerning = FT_HAS_KERNING(face);
	FT_Set_Pixel_Sizes(face,0,FontSize);
	
	font=0;
}

Font::Font(u32 Color, u32 Size, const char *Font_Path, Minimum *min){
	FontColor = Color;
	FontSize = Size;
	Lenght = 0;
	m = min;
	FT_Init_FreeType(&library);
	FT_New_Face(library,Font_Path,0,&face);
	FT_Stroker_New(library,&stroker);
	Kerning = FT_HAS_KERNING(face);
	FT_Set_Pixel_Sizes(face,0,FontSize);
	font=0;
}

Font::Font(u32 Size,const void *MemFont, u32 MemFont_size, Minimum *min){
	FontColor = COLOR_BLACK;
	FontSize = Size;
	Pointer = (FT_Byte*)MemFont;
	Lenght = MemFont_size;
	m = min;

	FT_Init_FreeType(&library);
	FT_New_Memory_Face(library,Pointer,Lenght,0,&face);
	FT_Stroker_New(library,&stroker);
	Kerning = FT_HAS_KERNING(face);
	FT_Set_Pixel_Sizes(face,0,FontSize);
	
	font=0;
}

Font::Font(u32 Size, const char *Font_Path, Minimum *min){
	FontColor = COLOR_BLACK;
	FontSize = Size;
	Lenght = 0;
	m = min;
	FT_Init_FreeType(&library);
	FT_New_Face(library,Font_Path,0,&face);
	FT_Stroker_New(library,&stroker);
	Kerning = FT_HAS_KERNING(face);
	FT_Set_Pixel_Sizes(face,0,FontSize);
	font=0;
}

Font::Font(const void *MemFont, u32 MemFont_size, Minimum *min){
	FontColor = COLOR_BLACK;
	FontSize = DEFAULT_FONT_SIZE;
	Pointer = (FT_Byte*)MemFont;
	Lenght = MemFont_size;
	m = min;

	FT_Init_FreeType(&library);
	FT_New_Memory_Face(library,Pointer,Lenght,0,&face);
	FT_Stroker_New(library,&stroker);
	Kerning = FT_HAS_KERNING(face);
	FT_Set_Pixel_Sizes(face,0,FontSize);
	
	font=0;
}

Font::Font(const char *Font_Path, Minimum *min){
	FontColor = COLOR_BLACK;
	FontSize = DEFAULT_FONT_SIZE;
	Lenght = 0;
	m = min;
	FT_Init_FreeType(&library);
	FT_New_Face(library,Font_Path,0,&face);
	FT_Stroker_New(library,&stroker);
	Kerning = FT_HAS_KERNING(face);
	FT_Set_Pixel_Sizes(face,0,FontSize);
	font=0;
}

Font::Font(const int ID, Minimum *min){
	const char *Font_Path;
	if(ID==JPN)
		Font_Path = "/dev_flash/data/font/SCE-PS3-NR-R-JPN.TTF";
	else if(ID==KOR)	
		Font_Path = "/dev_flash/data/font/SCE-PS3-YG-R-KOR.TTF";
	else if(ID==CGB)
		Font_Path = "/dev_flash/data/font/SCE-PS3-DH-R-CGB.TTF";
	else if(ID==KANA)
		Font_Path =  "/dev_flash/data/font/SCE-PS3-CP-R-KANA.TTF";
	else
		Font_Path = "/dev_flash/data/font/SCE-PS3-VR-R-LATIN2.TTF";

	FontColor = COLOR_BLACK;
	FontSize = DEFAULT_FONT_SIZE;
	Lenght = 0;
	m = min;
	FT_Init_FreeType(&library);
	FT_New_Face(library,Font_Path,0,&face);
	FT_Stroker_New(library,&stroker);
	Kerning = FT_HAS_KERNING(face);
	FT_Set_Pixel_Sizes(face,0,FontSize);
	font=0;
}

Font::~Font(){
	if(font==0)
		Disable_Fonts();
}

void Font::ChangeFontColor(u32 color){
	FontColor = color;
}

void Font::ChangeFontSize(u32 size){
	FontSize = size;
	FT_Set_Pixel_Sizes(face,0,FontSize);
}

void Font::Disable_Fonts(){
	FT_Done_Glyph(glyph);
	FT_Stroker_Done(stroker);
	FT_Done_Face(face);
	FT_Done_FreeType(library);
	font=1;
}

void Font::Printf(u32 x, u32 y,const char *a, ...){
	char text[1024];
	va_list va;
	va_start(va, a);
	vsnprintf(text, sizeof text, a, va);
	va_end(va);
	
	size_t len = strlen(a);
	if(len>0){
		len=strlen(text);
		vec.x = 0;
		vec.y = FontSize;
		FT_GlyphSlot slot = face->glyph;
		FT_UInt glyph_index = 0;
		FT_UInt previous_glyph = 0;
		Kerning = FT_HAS_KERNING(face);

		for(unsigned int i=0;i<len;i++){
			glyph_index = FT_Get_Char_Index(face, text[i]);
			if(Kerning && previous_glyph && glyph_index){
				FT_Vector delta;
				FT_Get_Kerning(face, previous_glyph, glyph_index, FT_KERNING_DEFAULT, &delta);
				vec.x += delta.x >> 6;
			}
			FT_Load_Glyph(face, glyph_index,FT_LOAD_RENDER);
			FT_Get_Glyph(face->glyph, &glyph);
			FT_Glyph_StrokeBorder(&glyph,stroker,0,0);
			FontDrawBitmap(&slot->bitmap,vec.x + slot->bitmap_left + x, (vec.y - slot->bitmap_top + y -FontSize));
			previous_glyph = glyph_index;
			vec.x += slot->advance.x >> 6;
			vec.y += slot->advance.y >> 6;
			FT_Done_Glyph(glyph);
		}
	}
}

void Font::Printf(u32 x, u32 y, u32 Color,const char *a, ...){
	char text[1024];
	va_list va;
	va_start(va, a);
	vsnprintf(text, sizeof text, a, va);
	va_end(va);
	
	size_t len = strlen(a);
	if(len>0){
		u32 C_TMP = FontColor;
		FontColor = Color;
		len=strlen(text);
		vec.x = 0;
		vec.y = FontSize;
		FT_GlyphSlot slot = face->glyph;
		FT_UInt glyph_index = 0;
		FT_UInt previous_glyph = 0;
		Kerning = FT_HAS_KERNING(face);

		for(unsigned int i=0;i<len;i++){
			glyph_index = FT_Get_Char_Index(face, text[i]);
			if(Kerning && previous_glyph && glyph_index){
				FT_Vector delta;
				FT_Get_Kerning(face, previous_glyph, glyph_index, FT_KERNING_DEFAULT, &delta);
				vec.x += delta.x >> 6;
			}
			FT_Load_Glyph(face, glyph_index,FT_LOAD_RENDER);
			FT_Get_Glyph(face->glyph, &glyph);
			FT_Glyph_StrokeBorder(&glyph,stroker,0,0);
			FontDrawBitmap(&slot->bitmap,vec.x + slot->bitmap_left + x, (vec.y - slot->bitmap_top + y -FontSize));
			previous_glyph = glyph_index;
			vec.x += slot->advance.x >> 6;
			vec.y += slot->advance.y >> 6;
			FT_Done_Glyph(glyph);
		}
		FontColor = C_TMP;
	}
}

void Font::Printf(u32 x, u32 y, u32 Color, u32 Size,const char *a, ...){
	char text[1024];
	va_list va;
	va_start(va, a);
	vsnprintf(text, sizeof text, a, va);
	va_end(va);
	
	size_t len = strlen(a);
	if(len>0){
		u32 C_TMP = FontColor;
		FontColor = Color;
		len=strlen(text);
		FT_Set_Pixel_Sizes(face,0,Size);
		vec.x = 0;
		vec.y = Size;
		FT_GlyphSlot slot = face->glyph;
		FT_UInt glyph_index = 0;
		FT_UInt previous_glyph = 0;
		Kerning = FT_HAS_KERNING(face);

		for(unsigned int i=0;i<len;i++){
			glyph_index = FT_Get_Char_Index(face, text[i]);
			if(Kerning && previous_glyph && glyph_index){
				FT_Vector delta;
				FT_Get_Kerning(face, previous_glyph, glyph_index, FT_KERNING_DEFAULT, &delta);
				vec.x += delta.x >> 6;
			}
			FT_Load_Glyph(face, glyph_index,FT_LOAD_RENDER);
			FT_Get_Glyph(face->glyph, &glyph);
			FT_Glyph_StrokeBorder(&glyph,stroker,0,0);
			FontDrawBitmap(&slot->bitmap,vec.x + slot->bitmap_left + x, (vec.y - slot->bitmap_top + y -Size));
			previous_glyph = glyph_index;
			vec.x += slot->advance.x >> 6;
			vec.y += slot->advance.y >> 6;
			FT_Done_Glyph(glyph);
		}
		FontColor = C_TMP;
		FT_Set_Pixel_Sizes(face,0,FontSize);

	}
}

void Font::PrintfToBitmap(u32 x, u32 y,NoRSX_Bitmap* bmap,const char *a, ...){
	char text[1024];
	va_list va;
	va_start(va, a);
	vsnprintf(text, sizeof text, a, va);
	va_end(va);
	
	size_t len = strlen(a);
	if(len>0){
		len=strlen(text);
		vec.x = 0;
		vec.y = FontSize;
		FT_GlyphSlot slot = face->glyph;
		FT_UInt glyph_index = 0;
		FT_UInt previous_glyph = 0;
		Kerning = FT_HAS_KERNING(face);

		for(unsigned int i=0;i<len;i++){
			glyph_index = FT_Get_Char_Index(face, text[i]);
			if(Kerning && previous_glyph && glyph_index){
				FT_Vector delta;
				FT_Get_Kerning(face, previous_glyph, glyph_index, FT_KERNING_DEFAULT, &delta);
				vec.x += delta.x >> 6;
			}
			FT_Load_Glyph(face, glyph_index,FT_LOAD_RENDER);
			FT_Get_Glyph(face->glyph, &glyph);
			FT_Glyph_StrokeBorder(&glyph,stroker,0,0);
			FontDrawBitmapToBitmap(&slot->bitmap,bmap,vec.x + slot->bitmap_left + x, (vec.y - slot->bitmap_top + y -FontSize));
			previous_glyph = glyph_index;
			vec.x += slot->advance.x >> 6;
			vec.y += slot->advance.y >> 6;
			FT_Done_Glyph(glyph);
		}
	}
}

void Font::PrintfToBitmap(u32 x, u32 y, NoRSX_Bitmap* bmap, u32 Color,const char *a, ...){
	char text[1024];
	va_list va;
	va_start(va, a);
	vsnprintf(text, sizeof text, a, va);
	va_end(va);
	
	size_t len = strlen(a);
	if(len>0){
		u32 C_TMP = FontColor;
		FontColor = Color;
		len=strlen(text);
		vec.x = 0;
		vec.y = FontSize;
		FT_GlyphSlot slot = face->glyph;
		FT_UInt glyph_index = 0;
		FT_UInt previous_glyph = 0;
		Kerning = FT_HAS_KERNING(face);

		for(unsigned int i=0;i<len;i++){
			glyph_index = FT_Get_Char_Index(face, text[i]);
			if(Kerning && previous_glyph && glyph_index){
				FT_Vector delta;
				FT_Get_Kerning(face, previous_glyph, glyph_index, FT_KERNING_DEFAULT, &delta);
				vec.x += delta.x >> 6;
			}
			FT_Load_Glyph(face, glyph_index,FT_LOAD_RENDER);
			FT_Get_Glyph(face->glyph, &glyph);
			FT_Glyph_StrokeBorder(&glyph,stroker,0,0);
			FontDrawBitmapToBitmap(&slot->bitmap,bmap,vec.x + slot->bitmap_left + x, (vec.y - slot->bitmap_top + y -FontSize));
			previous_glyph = glyph_index;
			vec.x += slot->advance.x >> 6;
			vec.y += slot->advance.y >> 6;
			FT_Done_Glyph(glyph);
		}
		FontColor = C_TMP;
	}
}

void Font::PrintfToBitmap(u32 x, u32 y, NoRSX_Bitmap* bmap, u32 Color, u32 Size,const char *a, ...){
	char text[1024];
	va_list va;
	va_start(va, a);
	vsnprintf(text, sizeof text, a, va);
	va_end(va);
	
	size_t len = strlen(a);
	if(len>0){
		u32 C_TMP = FontColor;
		FontColor = Color;
		len=strlen(text);
		FT_Set_Pixel_Sizes(face,0,Size);
		vec.x = 0;
		vec.y = Size;
		FT_GlyphSlot slot = face->glyph;
		FT_UInt glyph_index = 0;
		FT_UInt previous_glyph = 0;
		Kerning = FT_HAS_KERNING(face);

		for(unsigned int i=0;i<len;i++){
			glyph_index = FT_Get_Char_Index(face, text[i]);
			if(Kerning && previous_glyph && glyph_index){
				FT_Vector delta;
				FT_Get_Kerning(face, previous_glyph, glyph_index, FT_KERNING_DEFAULT, &delta);
				vec.x += delta.x >> 6;
			}
			FT_Load_Glyph(face, glyph_index,FT_LOAD_RENDER);
			FT_Get_Glyph(face->glyph, &glyph);
			FT_Glyph_StrokeBorder(&glyph,stroker,0,0);
			FontDrawBitmapToBitmap(&slot->bitmap,bmap,vec.x + slot->bitmap_left + x, (vec.y - slot->bitmap_top + y -Size));
			previous_glyph = glyph_index;
			vec.x += slot->advance.x >> 6;
			vec.y += slot->advance.y >> 6;
			FT_Done_Glyph(glyph);
		}
		FontColor = C_TMP;
		FT_Set_Pixel_Sizes(face,0,FontSize);
	}
}

void Font::FontDrawBitmap(FT_Bitmap *bitmap, s32 offset, s32 top){

	FT_Int x, y, i, j;
	FT_Int x_max = offset + bitmap->width;
	FT_Int y_max = top + bitmap->rows;
	u32 M_width = m->width;
	u32 M_height = m->height;

	u32 *ptr = m->buffer;


	if(y_max >= (s32)M_height)
		y_max = M_height;
	if(x_max >= (s32)M_width)
		x_max = M_width;

	for(x = offset, i = 0;x < x_max;x++, i++ ){
		for(y = top, j = 0;y < y_max;y++, j++ ){
			u32 color = bitmap->buffer[bitmap->width * j + i];
			if(color>0)
				ptr[m->width * y + x] = ((color)*0x01010101)&FontColor;
		}
	}
	
	return;
}


void Font::FontDrawBitmapToBitmap(FT_Bitmap *bitmap, NoRSX_Bitmap* bmap, s32 offset, s32 top){

	FT_Int x, y, i, j;
	FT_Int x_max = offset + bitmap->width;
	FT_Int y_max = top + bitmap->rows;

	u32 *ptr = bmap->bitmap;
	
	u32 M_width = m->width;
	u32 M_height = m->height;
	if(y_max >= (s32)M_height)
		y_max = M_height;
	if(x_max >= (s32)M_width)
		x_max = M_width;

	for(x = offset, i = 0;x < x_max;x++, i++ ){
		for(y = top, j = 0;y < y_max;y++, j++ ){
			u32 color = bitmap->buffer[bitmap->width * j + i];
			if(color>0)
				ptr[m->width * y + x] = ((color)*0x01010101)&FontColor;
		}
	}
	return;
}

