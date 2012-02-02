#include "rsxutil.h"

#define GCM_LABEL_INDEX		255

videoResolution res;
gcmContextData *context = NULL;

u32 curr_fb = 0;
u32 first_fb = 1;

u32 display_width;
u32 display_height;

u32 depth_pitch;
u32 depth_offset;
u32 *depth_buffer;

u32 color_pitch;
u32 color_offset[2]; //where you need to draw
u32 *color_buffer[2]; 

static u32 sLabelVal = 1;


static void waitFinish(){
	rsxSetWriteBackendLabel(context,GCM_LABEL_INDEX,sLabelVal);

	rsxFlushBuffer(context);

	while(*(vu32*)gcmGetLabelAddress(GCM_LABEL_INDEX)!=sLabelVal)
		usleep(30);

	++sLabelVal;
}

static void waitRSXIdle(){
	rsxSetWriteBackendLabel(context,GCM_LABEL_INDEX,sLabelVal);
	rsxSetWaitLabel(context,GCM_LABEL_INDEX,sLabelVal);

	++sLabelVal;

	waitFinish();
}

void setRenderTarget(u32 index){
	gcmSurface surface;

	surface.colorFormat		= GCM_TF_COLOR_X8R8G8B8;
	surface.colorTarget		= GCM_TF_TARGET_0;
	surface.colorLocation[0]	= GCM_LOCATION_RSX;
	surface.colorOffset[0]		= color_offset[index];
	surface.colorPitch[0]		= color_pitch;

	surface.colorLocation[1]	= GCM_LOCATION_RSX;
	surface.colorLocation[2]	= GCM_LOCATION_RSX;
	surface.colorLocation[3]	= GCM_LOCATION_RSX;
	surface.colorOffset[1]		= 0;
	surface.colorOffset[2]		= 0;
	surface.colorOffset[3]		= 0;
	surface.colorPitch[1]		= 64;
	surface.colorPitch[2]		= 64;
	surface.colorPitch[3]		= 64;

	surface.depthFormat		= GCM_TF_ZETA_Z16;
	surface.depthLocation		= GCM_LOCATION_RSX;
	surface.depthOffset		= depth_offset;
	surface.depthPitch		= depth_pitch;

	surface.type			= GCM_TF_TYPE_LINEAR;
	surface.antiAlias		= GCM_TF_CENTER_1;

	surface.width			= display_width;
	surface.height			= display_height;
	surface.x			= 0;
	surface.y			= 0;

	rsxSetSurface(context,&surface);
}

void init_screen(void *host_addr,u32 size){

	context = rsxInit(CB_SIZE,size,host_addr);

	videoState state;
	videoGetState(0,0,&state);

	videoGetResolution(state.displayMode.resolution,&res);

	videoConfiguration vconfig;
	memset(&vconfig,0,sizeof(videoConfiguration));

	vconfig.resolution = state.displayMode.resolution;
	vconfig.format = VIDEO_BUFFER_FORMAT_XRGB;
	vconfig.pitch = res.width*sizeof(u32);

	waitRSXIdle();

	videoConfigure(0,&vconfig,NULL,0);
	videoGetState(0,0,&state);

	gcmSetFlipMode(GCM_FLIP_VSYNC);

	display_width = res.width;
	display_height = res.height;

	color_pitch = display_width*sizeof(u32);
	color_buffer[0] = (u32*)rsxMemalign(64,(display_height*color_pitch));
	color_buffer[1] = (u32*)rsxMemalign(64,(display_height*color_pitch));

	rsxAddressToOffset(color_buffer[0],&color_offset[0]);
	rsxAddressToOffset(color_buffer[1],&color_offset[1]);

	gcmSetDisplayBuffer(0,color_offset[0],color_pitch,display_width,display_height);
	gcmSetDisplayBuffer(1,color_offset[1],color_pitch,display_width,display_height);

	depth_pitch = display_width*sizeof(u32);
	depth_buffer = (u32*)rsxMemalign(64,(display_height*depth_pitch)*2);
	rsxAddressToOffset(depth_buffer,&depth_offset);

}

void waitflip(){
	while(gcmGetFlipStatus()!=0) usleep(200);
	gcmResetFlipStatus();
}

void flip()
{
	if(!first_fb) waitflip();
	else gcmResetFlipStatus();

	gcmSetFlip(context,curr_fb);
	rsxFlushBuffer(context);

	gcmSetWaitFlip(context);

	curr_fb ^= 1;
	setRenderTarget(curr_fb);

	first_fb = 0;
}
