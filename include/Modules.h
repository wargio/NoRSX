#ifndef __NORSX_MODULE__
#define __NORSX_MODULE__

#include <sysmodule/sysmodule.h>
#include <ppu-types.h>
#include <stdlib.h>

class Module{
public:

	Module();
	~Module();
	static void Load();
	static void Unload();

	static s32 ModulesError;


protected:
	static u32 module_flag;
};

#endif
