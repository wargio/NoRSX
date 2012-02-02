#include "Image.h"
#include "rsxutil.h"
Image::Image() : Module(){}
Image::~Image(){
	
}

pngData Image::LoadFromFile_PNG  (const char *Path){
	pngData png_image;
	pngLoadFromFile(Path, &png_image);
	return png_image;
}
pngData Image::LoadFromBuffer_PNG(void *BIN, u32 Size){
	pngData png_image;
	pngLoadFromBuffer(BIN, Size, &png_image);
	return png_image;
}

int Image::DrawPNG(int x_png, int y_png, pngData png_image){
	if(png_image.bmp_out){
		static int x=0,y=0 ;
		u32 *scr = color_buffer[curr_fb];
		u32 *png =  (u32 *) png_image.bmp_out;
		int n, m;
		x+=x_png; y+=y_png;
		scr+=y*display_width+x;
		for(n=0;n<png_image.height;n++) {
			if((y+n)>=display_height) break;
			for(m=0;m<png_image.width;m++) {
				if((x+m)>=display_width) break;
				scr[m]=png[m];
			}
			png+=png_image.pitch>>2;
			scr+=display_width;
			x = 0;
			y = 0;
		}
		return 0;
	}else{
		return -1;
	}
}


jpgData Image::LoadFromFile_JPG  (const char *Path){
	jpgData jpg_image;
	jpgLoadFromFile(Path, &jpg_image);
	return jpg_image;
}
jpgData Image::LoadFromBuffer_JPG(void *BIN, u32 Size){
	jpgData jpg_image;
	jpgLoadFromBuffer(BIN, Size, &jpg_image);
	return jpg_image;
}

int Image::DrawJPG(int x_jpg, int y_jpg, jpgData jpg_image){
	if(jpg_image.bmp_out){
		static int x=0,y=0 ;
		u32 *scr = color_buffer[curr_fb];
		u32 *jpg =  (u32 *) jpg_image.bmp_out;
		int n, m;
		x+=x_jpg; y+=y_jpg;
		scr+=y*display_width+x;
		for(n=0;n<jpg_image.height;n++) {
			if((y+n)>=display_height) break;
			for(m=0;m<jpg_image.width;m++) {
				if((x+m)>=display_width) break;
				scr[m]=jpg[m];
			}
			jpg+=jpg_image.pitch>>2;
			scr+=display_width;
			x = 0;
			y = 0;
		}
		return 0;
	}else{
		return -1;
	}
}
