#include "Image.h"
#ifndef __NORSX_MAIN_H__
#define __NORSX_MAIN_H__

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "rsxutil.h"

class NoRSX : public Minimum{
public:

	 NoRSX();
	~NoRSX();
	
	void Flip();
	
protected:
	void *host_addr;

};

#endif

/*


Image(Minimum *g);
void LoadPNG(const char* filename, pngData *png);
void LoadJPG(const char* filename, jpgData *jpg);
void LoadPNG_Buf(const void* name, pngData *png);
void LoadJPG_Buf(const void* name, jpgData *jpg);
void DrawIMG(int x, int y, pngData *png1);
void DrawIMG(int x, int y, jpgData *jpg1);
*/
