/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 This program was created by Grazioli Giovanni Dante <wargio@libero.it>.

*/

#include <NoRSX.h>
#include <sys/process.h>

/* Allocate 1MB stack to avoid overflows */
SYS_PROCESS_PARAM(1001, 0x100000);

static int already_done=0;

NoRSX::NoRSX() : EventHandler(){
	currentBuffer = 0;
	host_addr = memalign(1024*1024, HOST_SIZE);
	getResolution(&width,&height);
	context = initScreen(host_addr, HOST_SIZE,0, width, height);
	for(int i=0;i<2;i++)
		makeBuffer(&buffers[i],width,height,i);
	flip(context, 1);
	setRenderTarget(context, &buffers[currentBuffer]);
	RegisterCallBack(EVENT_SLOT0);
}

NoRSX::NoRSX(int id_type) : EventHandler(){
	id_scr=id_type;
	currentBuffer = 0;
	host_addr = memalign(1024*1024, HOST_SIZE);
	
	if(id_type==RESOLUTION_1920x1080){
		width=1920;height=1080;
		buffers[0].width=1920;buffers[0].height=1080;
		buffers[1].width=1920;buffers[1].height=1080;
	}else if(id_type==RESOLUTION_1280x720){
		width=1280;height=720;
		buffers[0].width=1280;buffers[0].height=720;
		buffers[1].width=1280;buffers[1].height=720;
	}else if(id_type==RESOLUTION_720x576){
		width=720;height=576;
		buffers[0].width=720;buffers[0].height=576;
		buffers[1].width=720;buffers[1].height=576;
	}else if(id_type==RESOLUTION_720x480){
		width=720;height=480;
		buffers[0].width=720;buffers[0].height=480;
		buffers[1].width=720;buffers[1].height=480;
	}else{
		getResolution(&width,&height);
	}
	context = initScreen(host_addr, HOST_SIZE, id_type, width, height);

	for(int i=0;i<2;i++)
		makeBuffer(&buffers[i],width,height,i);
	flip(context, 1);
	setRenderTarget(context, &buffers[currentBuffer]);
	RegisterCallBack(EVENT_SLOT0);
}

NoRSX::~NoRSX(){
	if(already_done!=0)
		NoRSX_Exit();
}

void NoRSX::Flip(){
	if(GetXMBStatus() == XMB_OPEN){
		flip(context, buffers[!currentBuffer].id);
	}else{
		flip(context, buffers[currentBuffer].id); // Flip buffer onto screen
		currentBuffer = !currentBuffer;
	}
	setRenderTarget(context, &buffers[currentBuffer]);
	sysUtilCheckCallback();
	waitFlip();
}

void NoRSX::NoRSX_Exit(){
	gcmSetWaitFlip(context);
	for (int i=0;i<2;i++)
		rsxFree (buffers[i].ptr);
	rsxFinish (context, 1);
	free (host_addr);
	UnregisterCallBack(EVENT_SLOT0);
	already_done=1;
}

