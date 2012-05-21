#include "Font.h"

#define COLOR_TO_ARGB(alpha, red, green, blue) (((alpha) << 24) | ((red) << 16) | ((green) << 8) | (blue))
#define COLOR_TO_RGB(red, green, blue) (((red) << 16) | ((green) << 8) | (blue))

#define VALUE_TO_ARGB(value) (((value) << 24) | ((value) << 16) | ((value) << 8) | (value))
#define VALUE_TO_RGB(value) (((value) << 16) | ((value) << 8) | (value))

#define A(argb)  (((argb) >> 24) & 0xFF)
#define R(argb)  (((argb) >> 16) & 0xFF)
#define G(argb)  (((argb) >>  8) & 0xFF)
#define B(argb)  ( (argb)        & 0xFF)


Fonts::Fonts(u32 Color, u32 Size,const void *MemFont, u32 MemFont_size, Minimum *min){
//	BackGroundColor = BackGround;
	FontColor = Color;
	FontSize = Size;
//	FontPath;
	Pointer = (FT_Byte*)MemFont;
	Lenght = MemFont_size;
	m = min;

	FT_Init_FreeType(&library);
	FT_New_Memory_Face(library,Pointer,Lenght,0,&face);
	FT_Stroker_New(library,&stroker);
	Kerning = FT_HAS_KERNING(face);
	FT_Set_Pixel_Sizes(face,0,FontSize);
	
	rsxAddressToOffset(m->buffers[m->currentBuffer].ptr, &color_offset);
	disabled_font=0;
}

Fonts::~Fonts(){
	if(disabled_font==0)
		Disable_Fonts();
}

void Fonts::Printf(u32 x, u32 y,const char *a, ...){
	size_t len = strlen(a);
	if(len>0){
		char text[len+1];
		va_list va;
		va_start(va, a);
		vsnprintf(text, sizeof text, a, va);

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
				vec.x += delta.x >> 6 ;
			}
			FT_Load_Glyph(face, glyph_index,FT_LOAD_RENDER);
			FT_Get_Glyph(face->glyph, &glyph);
			FT_Glyph_StrokeBorder(&glyph,stroker,0,0);
			FontDrawBitmap(&slot->bitmap,vec.x + slot->bitmap_left + x, (vec.y - slot->bitmap_top + y -FontSize));
			previous_glyph = glyph_index ;
			vec.x += slot->advance.x >> 6;
			vec.y += slot->advance.y >> 6;
		}
		
	}
}


void Fonts::FontDrawBitmap(FT_Bitmap *bitmap, s32 offset, s32 top){
	static s32 color, a, r, g, b ;
	FT_Int x, y, i, j ;
	FT_Int x_max = offset + bitmap->width ;
	FT_Int y_max = top + bitmap->rows ;

	s32 fgA = A(FontColor) ;
	s32 fgR = R(FontColor) ;
	s32 fgG = G(FontColor) ;
	s32 fgB = B(FontColor) ;

	u32 M_width = m->width;
	u32 M_height = m->height;

	for ( x = offset, i = 0 ; x < x_max ; x++, i++ ){
		if ( x >= (s32)M_width ) break ;
		for ( y = top, j = 0 ; y < y_max ; y++, j++ ){
			if ( y >= (s32)M_height ) break ;
			color = bitmap->buffer[bitmap->width * j + i] ;
			a = ( ( fgA * color + 255 ) >> 8 ) ;
			r = ( ( fgR * color + 255 ) >> 8 ) ;
			g = ( ( fgG * color + 255 ) >> 8 ) ;
			b = ( ( fgB * color + 255 ) >> 8 ) ;
			*(m->buffers[m->currentBuffer].ptr + m->width * y + x ) = COLOR_TO_ARGB(a, r, g, b);
		}
	}
}

void Fonts::DrawFont(){
	color_depth = sizeof(u32) ;
	color_pitch = width*color_depth;
	gcmTransferScale xferscale ;
	memset ( &xferscale, 0, sizeof ( xferscale ) ) ;

	gcmTransferSurface xfersurface ;
	memset ( &xfersurface, 0, sizeof ( xfersurface ) ) ;

	/* configure transfer scale */
	xferscale.conversion = GCM_TRANSFER_CONVERSION_TRUNCATE ;
	xferscale.format = GCM_TRANSFER_SCALE_FORMAT_A8R8G8B8 ;
	xferscale.operation = GCM_TRANSFER_OPERATION_SRCCOPY_AND ;
	xferscale.clipX = 0 ;
	xferscale.clipY = 0 ;
	xferscale.clipW = m->width ;
	xferscale.clipH = m->height ;
	xferscale.outX = 0 ;
	xferscale.outY = 0 ;
	xferscale.outW = m->width;
	xferscale.outH = m->height;
	xferscale.inW = width;
	xferscale.inH = height;

	xferscale.ratioX = rsxGetFixedSint32 ( (float)xferscale.inW / (float)xferscale.outW ) ;
	xferscale.ratioY = rsxGetFixedSint32 ( (float)xferscale.inH / (float)xferscale.outH ) ;

	xferscale.pitch = color_pitch;
	xferscale.origin = GCM_TRANSFER_ORIGIN_CORNER ;
	xferscale.interp = GCM_TRANSFER_INTERPOLATOR_NEAREST ;
	xferscale.offset = color_offset;

	xferscale.inX = rsxGetFixedUint16 ( 1.0f ) ;
	xferscale.inY = rsxGetFixedUint16 ( 1.0f ) ;

	/* configure destination surface for transfer */
	xfersurface.format = GCM_TRANSFER_SURFACE_FORMAT_A8R8G8B8 ;
	xfersurface.pitch = color_pitch ;
	xfersurface.offset = color_offset ;

	/* blit font buffer */
	rsxSetTransferScaleMode(m->context, GCM_TRANSFER_LOCAL_TO_LOCAL, GCM_TRANSFER_SURFACE);
	rsxSetTransferScaleSurface(m->context, &xferscale, &xfersurface);
}

void Fonts::Disable_Fonts(){
	FT_Done_FreeType(library);
	FT_Stroker_Done(stroker);
	FT_Done_Glyph(glyph);
	free(Pointer);
	disabled_font=1;
}
