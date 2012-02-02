#include "NoRSX.h"
#include "memory.h"

NoRSX::NoRSX(){
	host_addr = memalign(1024*1024,HOST_SIZE);
//	main_addr = (void*)((u64)host_addr + CB_SIZE);

	init_spu();
	init_screen(host_addr,HOST_SIZE);

	signal_spu_ppu();
	signal_spu_rsx();

	setRenderTarget(curr_fb);
	rsxFinish(context,0);

	EventH();
	atexit(ExitCallBack);
	Image();
}

NoRSX::~NoRSX(){
	ExitCallBack();
}

void NoRSX::ExitCallBack(){
	gcmSetWaitFlip(context);
	rsxFinish(context,1);

	shutdown_spu();
	Unload();
}

/*
void drawFrame()
{

	wait_signal_spu();


	clear_signal_spu();
	signal_spu_rsx();

}

*/
