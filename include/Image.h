#ifndef __NORSX_IMAGE_H__
#define __NORSX_IMAGE_H__

#include <pngdec/pngdec.h>
#include <jpgdec/jpgdec.h>
#include <sysutil/sysutil.h>
#include <sysmodule/sysmodule.h>
#include "Min.h"


class Image{
public:
	Image(Minimum *g){
		G=g;
		sysModuleLoad(SYSMODULE_FS);
		sysModuleLoad(SYSMODULE_PNGDEC);
		sysModuleLoad(SYSMODULE_JPGDEC);
	}
	~Image(){
		sysModuleUnload(SYSMODULE_FS);
		sysModuleUnload(SYSMODULE_PNGDEC);
		sysModuleUnload(SYSMODULE_JPGDEC);
	}
	void LoadPNG(const char* filename, pngData *png);
	void LoadJPG(const char* filename, jpgData *jpg);
//	void LoadPNG_Buf(const void* name, pngData *png);
//	void LoadJPG_Buf(const void* name, jpgData *jpg);.

	void DrawIMG(int x, int y, pngData *png1);
	void DrawIMG(int x, int y, jpgData *jpg1);

private:
	Minimum *G;

};


#endif
