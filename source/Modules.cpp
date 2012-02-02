#include "Modules.h"
u32 Module::module_flag;
s32 Module::ModulesError;

Module::Module(){
	Load();
}

Module::~Module(){
	Unload();
}

void Module::Load(){
	if(sysModuleLoad(SYSMODULE_FS) != 0){
		ModulesError=-1;
	}else{
		module_flag |= 1;
		ModulesError=0;
	}
	if(sysModuleLoad(SYSMODULE_PNGDEC) != 0){
		ModulesError=-2;
	}else{
		module_flag |= 2;
		ModulesError=0;
	}
	if(sysModuleLoad(SYSMODULE_JPGDEC) != 0){
		ModulesError=-3;
	}else{
		module_flag |= 3;
		ModulesError=0;
	}

}

void Module::Unload(){
	if(module_flag & 3)
		sysModuleUnload(SYSMODULE_JPGDEC);
	if(module_flag & 2)
		sysModuleUnload(SYSMODULE_PNGDEC);
	if(module_flag & 1)
		sysModuleUnload(SYSMODULE_FS);
}
