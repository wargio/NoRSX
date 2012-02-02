#include <pngdec/pngdec.h>
#include <jpgdec/jpgdec.h>


#ifndef __NORSX_IMAGE__
#define __NORSX_IMAGE__

#include <ppu-types.h>
#include "rsxutil.h"
#include "Modules.h"

class Image : public Module{
public:
	Image();
	~Image();

	jpgData LoadFromFile_JPG  (const char *Path);
	jpgData LoadFromBuffer_JPG(void *BIN, u32 Size);

	pngData LoadFromFile_PNG  (const char *Path);
	pngData LoadFromBuffer_PNG(void *BIN, u32 Size);


	int DrawPNG(int x, int y, pngData png_image);
	int DrawJPG(int x, int y, jpgData jpg_image);
};

#endif
