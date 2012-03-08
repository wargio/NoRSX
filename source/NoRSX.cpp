#include "NoRSX.h"


NoRSX::NoRSX(){
	currentBuffer = 0;
	host_addr = memalign(1024*1024, HOST_SIZE);
	context = initScreen(host_addr, HOST_SIZE);
	getResolution(&width,&height);
	for(int i=0;i<2;i++)
		makeBuffer(&buffers[i],width,height,i);
	flip(context, 1);
	setRenderTarget(context, &buffers[currentBuffer]);
}

NoRSX::~NoRSX(){
	gcmSetWaitFlip(context);
	for (int i=0;i<2;i++)
		rsxFree (buffers[i].ptr);
	rsxFinish (context, 1);
	free (host_addr);
}

void NoRSX::Flip(){
	flip(context, buffers[currentBuffer].id); // Flip buffer onto screen
	currentBuffer = !currentBuffer;
	setRenderTarget(context, &buffers[currentBuffer]) ;
	waitFlip();
}
