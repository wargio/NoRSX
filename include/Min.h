#ifndef __NORSX_MIN_H__
#define __NORSX_MIN_H__
#include <rsx/rsx.h>
#include "rsxutil.h"
#include <ppu-types.h>

class Minimum{
public:
	u16 width;
	u16 height;

	rsxBuffer buffers[2];
	gcmContextData *context;
	int currentBuffer;
};

#endif


