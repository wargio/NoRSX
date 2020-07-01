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

#include <NoRSX/Image.h>

void Image::LoadPNG(const char* filename, pngData* png) {
	pngLoadFromFile(filename, png);
}

void Image::LoadJPG(const char* filename, jpgData* jpg) {
	jpgLoadFromFile(filename, jpg);
}

void Image::LoadPNG_Buf(const void* name, u32 name_size, pngData* png) {
	pngLoadFromBuffer(name, name_size, png);
}

void Image::LoadJPG_Buf(const void* name, u32 name_size, jpgData* jpg) {
	jpgLoadFromBuffer(name, name_size, jpg);
}

inline void draw_image(s32 x, s32 y, u32* scr, u32 scr_width, u32 src_height, u32* img, u32 img_width, u32 img_height, u32 img_pitch) {
	s32 error_x, error_y;
	if (img) {
		if (x < 0) {
			img = img - x;
			error_x = -x;
			x = 0;
		}
		else {
			error_x = 0;
		}

		if (y < 0) {
			error_y = -y;
			img = img + y * img_width;
			y = 0;
		}
		else {
			error_y = 0;
		}

		scr += y * scr_width + x;
		s32 height = img_height;
		if ((y + height) >= (s32)scr_height) {
			height = scr_height - 1 - y;
		}

		s32 width = img_width;
		if ((x + width) >= (s32)scr_width) {
			width = scr_width - 1 - x;
		}

		width -= error_x;
		height -= error_y;
		while (width > 0 && height > 0) {
			memcpy(scr, img, width * sizeof(u32));
			img += img_pitch >> 2;
			scr += scr_width;
			height--;
		}
	}
}

inline void draw_image_alpha(s32 x, s32 y, u32* scr, u32 scr_width, u32 src_height, u32* img, u32 img_width, u32 img_height, u32 img_pitch) {
	s32 error_x, error_y;
	u32 m, a, OxFF_A;
	if (img) {
		if (x < 0) {
			png = png - x;
			error_x = -x;
			x = 0;
		} else {
			error_x = 0;
		}

		if (y < 0) {
			error_y = -y;
			png = png + y * img_width;
			y = 0;
		} else {
			error_y = 0;
		}

		scr += y * scr_width + x;
		s32 height = img_height;
		if ((y + height) >= (s32)scr_height) {
			height = scr_height - 1 - y;
		}

		s32 width = img_width;
		if ((x + width) >= (s32)scr_width) {
			width = scr_width - 1 - x;
		}

		width -= error_x;
		height -= error_y;

		while (width > 0 && height > 0) {
			for (m = 0; m < (u32)width; m++) {
				a = png[m] >> 24; // alpha
				if (a == 0xff) {
					scr[m] = png[m];
				} else if (a != 0) {
					OxFF_A = 0xff - a;
					scr[m] = (png[m] & 0xff000000) | 
						((((((png[m] & 0x00ff00ff) * a) + ((scr[m] & 0x00ff00ff) * (OxFF_A))) & 0xff00ff00) |
						((((png[m] & 0x0000ff00) * a) + ((scr[m] & 0x0000ff00) * (OxFF_A))) & 0x00ff0000)) >> 8);
				}
			}
			png += img_pitch >> 2;
			scr += scr_width;
			height--;
		}
	}
}

inline void draw_image_partial(s32 x, s32 y, u32 s_width, u32 s_height, u32 e_width, u32 e_height, u32 bg, u32 color, u32* scr, u32 scr_width, u32* img, u32 img_pitch) {
	u32 n, m;
	if (img) {
		scr += y * scr_width + x;
		if (s_height > 0) {
			for (u32 i = 0; i < s_height; i++) {
				png += img_pitch >> 2;
			}
		}
		for (n = s_height; n < e_height + s_height; n++) {
			if ((y + n) >= (u32)scr_height) {
				break;
			}
			for (m = s_width; m < e_width + s_width; m++) {
				if ((x + m) >= (u32)scr_width) {
					break;
				}
				if (png[m] != bg) {
					scr[m - s_width] = color;
				}
			}
			png += img_pitch >> 2;
			scr += scr_width;
		}
	}
}

void Image::DrawIMG(s32 x, s32 y, pngData* img) {
	if (!img->bmp_out) {
		return;
	}
	u32* scr        = (u32*)G->buffer;
	u32  scr_width  = G->width;
	u32  scr_height = G->height;
	u32* img        = (u32*)img->bmp_out;
	u32  img_width  = img->width;
	u32  img_height = img->height;
	u32  img_pitch  = img->pitch;
	draw_image(x, y, scr, scr_width, scr_height, img, img_width, img_height, img_pitch);
}

void Image::DrawIMG(s32 x, s32 y, jpgData* img) {
	if (!img->bmp_out) {
		return;
	}
	u32* scr        = (u32*)G->buffer;
	u32  scr_width  = G->width;
	u32  scr_height = G->height;
	u32* img        = (u32*)img->bmp_out;
	u32  img_width  = img->width;
	u32  img_height = img->height;
	u32  img_pitch  = img->pitch;
	draw_image(x, y, scr, scr_width, scr_height, img, img_width, img_height, img_pitch);
}

void Image::AlphaDrawIMG(s32 x, s32 y, pngData* img) {
	if (!img->bmp_out) {
		return;
	}
	u32* scr        = (u32*)G->buffer;
	u32  scr_width  = G->width;
	u32  scr_height = G->height;
	u32* img        = (u32*)img->bmp_out;
	u32  img_width  = img->width;
	u32  img_height = img->height;
	u32  img_pitch  = img->pitch;
	draw_image_alpha(x, y, scr, scr_width, scr_height, img, img_width, img_height, img_pitch);
}

void Image::DrawPartialImage(s32 x, s32 y, u32 s_width, u32 s_height, u32 e_width, u32 e_height, u32 bg, u32 color, pngData* img) {
	if (!img->bmp_out) {
		return;
	}

	u32* scr        = (u32*)G->buffer;
	u32  scr_width  = G->width;
	u32* img        = (u32*)img->bmp_out;
	u32  img_pitch  = img->pitch;
	draw_image_partial(x, y, s_width, s_height, e_width, e_height, bg, color, scr, scr_width, u32* img, u32 img_pitch);
}

void Image::DrawPartialImage(s32 x, s32 y, u32 s_width, u32 s_height, u32 e_width, u32 e_height, u32 bg, u32 color, jpgData* img) {
	if (!img->bmp_out) {
		return;
	}

	u32* scr        = (u32*)G->buffer;
	u32  scr_width  = G->width;
	u32* img        = (u32*)img->bmp_out;
	u32  img_pitch  = img->pitch;
	draw_image_partial(x, y, s_width, s_height, e_width, e_height, bg, color, scr, scr_width, u32* img, u32 img_pitch);
}

void Image::DrawIMGtoBitmap(s32 x, s32 y, pngData* img, NoRSX_Bitmap* bm) {
	if (!img->bmp_out) {
		return;
	}
	u32* scr        = (u32*)bm->bitmap;
	u32  scr_width  = bm->width;
	u32  scr_height = bm->height;
	u32* img        = (u32*)img->bmp_out;
	u32  img_width  = img->width;
	u32  img_height = img->height;
	u32  img_pitch  = img->pitch;
	draw_image(x, y, scr, scr_width, scr_height, img, img_width, img_height, img_pitch);
}

void Image::DrawIMGtoBitmap(s32 x, s32 y, jpgData* img, NoRSX_Bitmap* bm) {
	if (!img->bmp_out) {
		return;
	}
	u32* scr        = (u32*)bm->bitmap;
	u32  scr_width  = bm->width;
	u32  scr_height = bm->height;
	u32* img        = (u32*)img->bmp_out;
	u32  img_width  = img->width;
	u32  img_height = img->height;
	u32  img_pitch  = img->pitch;
	draw_image(x, y, scr, scr_width, scr_height, img, img_width, img_height, img_pitch);
}

void Image::AlphaDrawIMGtoBitmap(s32 x, s32 y, pngData* img, NoRSX_Bitmap* a) {
	if (!img->bmp_out) {
		return;
	}
	u32* scr        = (u32*)bm->bitmap;
	u32  scr_width  = bm->width;
	u32  scr_height = bm->height;
	u32* img        = (u32*)img->bmp_out;
	u32  img_width  = img->width;
	u32  img_height = img->height;
	u32  img_pitch  = img->pitch;
	draw_image_alpha(x, y, scr, scr_width, scr_height, img, img_width, img_height, img_pitch);
}

inline void scaleline(u32* target, u32* source, u32 src_width, u32 tgt_width) {
	s32 num_pixels1 = 0;
	s32 int_part1 = 0;
	s32 fract_part1 = 0;
	s32 e1 = 0;
	//Thanks to: http://www.compuphase.com/graphic/scale.htm
	num_pixels1 = tgt_width;
	int_part1 = src_width / tgt_width;
	fract_part1 = src_width % tgt_width;
	e1 = 0;

	while (num_pixels1-- > 0) {
		*target++ = *source;
		source += int_part1;
		e1 += fract_part1;
		if (e1 >= tgt_width) {
			e1 -= tgt_width;
			source++;
		}
	}
	return;
}

inline resize_image(u32* source, u32* target, u32 in_width, u32 in_height, u32 tgt_width, u32 tgt_height) {
	s32 e0 = 0;
	s32 num_pixels0 = tgt_height;
	s32 int_part0 = (in_height / tgt_height) * in_width;
	s32 fract_part0 = in_height % tgt_height;
	u32* prev_source = NULL;

	while (num_pixels0-- > 0) {
		if (source == prev_source) {
			memcpy(target, target - tgt_width, tgt_width * sizeof(u32));
		} else {
			scaleline(target, source, in_width, tgt_width);
			prev_source = source;
		}
		target += tgt_width;
		source += int_part0;
		e0 += fract_part0;
		if (e0 >= tgt_height) {
			e0 -= tgt_height;
			source += in_width;
		}
	}
}

pngData* Image::ResizeImage(pngData* png_in, u32 tgt_width, u32 tgt_height) {
	//Thanks to: http://www.compuphase.com/graphic/scale.htm
	if (png_in->bmp_out) {
		pngData* png_out = new pngData;
		png_out->bmp_out = (u32*)malloc(tgt_height * tgt_width * sizeof(u32));
		u32* source = (u32*)png_in->bmp_out;
		u32* target = (u32*)png_out->bmp_out;

		png_out->height = tgt_height;
		png_out->width = tgt_width;
		png_out->pitch = tgt_width * 4;

		resize_image(source, target, png_in->width, png_in->height, tgt_width, tgt_height);
		return png_out;
	}
	return NULL;
}

jpgData* Image::ResizeImage(jpgData* jpg_in, u32 tgt_width, u32 tgt_height) {
	//Thanks to: http://www.compuphase.com/graphic/scale.htm
	if (jpg_in->bmp_out) {
		jpgData* jpg_out = new jpgData;
		jpg_out->bmp_out = (u32*)malloc(tgt_height * tgt_width * sizeof(u32));
		u32* source = (u32*)jpg_in->bmp_out;
		u32* target = (u32*)jpg_out->bmp_out;

		jpg_out->height = tgt_height;
		jpg_out->width = tgt_width;
		jpg_out->pitch = tgt_width * 4;

		resize_image(source, target, jpg_in->width, jpg_in->height, tgt_width, tgt_height);
		return jpg_out;
	}
	return NULL;
}
