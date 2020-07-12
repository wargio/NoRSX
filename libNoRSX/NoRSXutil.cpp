/*
 * This software is distributed under the terms of the GNU General Public
 * License("GPL") version 3, as published by the Free Software Foundation.
 */

#include <ppu-lv2.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <sysutil/video.h>
#include <rsx/gcm_sys.h>
#include <rsx/rsx.h>
#include <io/pad.h>
#include <time.h>
#include <math.h>

#include <NoRSX/NoRSXutil.h>

#define GCM_LABEL_INDEX		255

static void waitRSXIdle(gcmContextData *context);

static u32 depth_pitch;
static u32 depth_offset;
static u32 *depth_buffer;

void waitFlip(){
	while(gcmGetFlipStatus() != 0)
		usleep(300);	/* Sleep, to not stress the cpu. */
	gcmResetFlipStatus();
}

int flip(gcmContextData *context, s32 buffer){
	if(gcmSetFlip(context, buffer) == 0) {
		rsxFlushBuffer(context);
		// Prevent the RSX from continuing until the flip has finished.
		gcmSetWaitFlip(context);
		return TRUE;
	}
	return FALSE;
}

u32 *makeMemBuffer(u16 width, u16 height, u32 *buffer_size){
	u32 size = width * height * sizeof(u32);
	*buffer_size = size;
	return (u32*) rsxMalloc(size);
}

int makeBuffer(rsxBuffer * buffer, u16 width, u16 height, int id){
	int depth = sizeof(u32);
	int pitch = depth * width;
	int size = depth * width * height;

	buffer->ptr =(uint32_t*) rsxMemalign(64, size);

	if(buffer->ptr == NULL)
		goto error;

	if(rsxAddressToOffset(buffer->ptr, &buffer->offset) != 0)
		goto error;

	/* Register the display buffer with the RSX */
	if(gcmSetDisplayBuffer(id, buffer->offset, pitch, width, height) != 0)
		goto error;

	buffer->width = width;
	buffer->height = height;
	buffer->id = id;

	return TRUE;

 error:
	if(buffer->ptr != NULL)
		rsxFree(buffer->ptr);

	return FALSE;
}

int getResolution(u16 *width, u16 *height){
	videoState state;
	videoResolution resolution;

	/* Get the state of the display */
	if(videoGetState(0, 0, &state) == 0 &&
			videoGetResolution(state.displayMode.resolution, &resolution) == 0) {
		if(width)
			*width = resolution.width;
		if(height)
			*height = resolution.height;

		return TRUE;
	}
	return FALSE;
}

gcmContextData *initScreen(void *host_addr, u32 size, u32 vid_id, u16 width, u16 height){
	gcmContextData *context = NULL; /* Context to keep track of the RSX buffer. */
	videoState state;
	videoConfiguration vconfig;
	videoResolution res; /* Screen Resolution */

	/* Initilise Reality, which sets up the command buffer and shared IO memory */
	rsxInit(&context, CB_SIZE, size, host_addr);
	if(context == NULL)
		goto error;

	/* Get the state of the display */
	if(videoGetState(0, 0, &state) != 0)
		goto error;

	/* Make sure display is enabled */
	if(state.state != 0)
		goto error;

	/* Get the current resolution */
	if(videoGetResolution(state.displayMode.resolution, &res) != 0)
		goto error;

	/* Configure the buffer format to xRGB */
	memset(&vconfig, 0, sizeof(videoConfiguration));
	if(vid_id==0)
		vconfig.resolution = state.displayMode.resolution;
	else
		vconfig.resolution = vid_id;
	vconfig.format = VIDEO_BUFFER_FORMAT_XRGB;

	vconfig.pitch = width * sizeof(u32);

	vconfig.aspect = state.displayMode.aspect;
	waitRSXIdle(context);

	if(videoConfigure(0, &vconfig, NULL, 0) != 0)
		goto error;

	if(videoGetState(0, 0, &state) != 0)
		goto error;

	gcmSetFlipMode(GCM_FLIP_VSYNC); // Wait for VSYNC to flip

	depth_pitch = width * sizeof(u32);
	depth_buffer =(u32 *) rsxMemalign(64,(height * depth_pitch)* 2);
	rsxAddressToOffset(depth_buffer, &depth_offset);

	gcmResetFlipStatus();

	return context;

 error:
	if(context)
		rsxFinish(context, 0);

	if(host_addr)
		free(host_addr);

	return NULL;
}


static void waitFinish(gcmContextData *context, u32 sLabelVal){
	rsxSetWriteBackendLabel(context, GCM_LABEL_INDEX, sLabelVal);

	rsxFlushBuffer(context);

	while(*(vu32 *) gcmGetLabelAddress(GCM_LABEL_INDEX) != sLabelVal)
		usleep(30);

	sLabelVal++;
}

static void waitRSXIdle(gcmContextData *context){
	u32 sLabelVal = 1;

	rsxSetWriteBackendLabel(context, GCM_LABEL_INDEX, sLabelVal);
	rsxSetWaitLabel(context, GCM_LABEL_INDEX, sLabelVal);

	sLabelVal++;

	waitFinish(context, sLabelVal);
}

void setRenderTarget(gcmContextData *context, rsxBuffer *buffer){
	gcmSurface sf;

	sf.colorFormat = GCM_SURFACE_X8R8G8B8;
	sf.colorTarget = GCM_SURFACE_TARGET_0;
	sf.colorLocation[0] = GCM_LOCATION_RSX;
	sf.colorOffset[0] = buffer->offset;
	sf.colorPitch[0] = depth_pitch;

	sf.colorLocation[1] = GCM_LOCATION_RSX;
	sf.colorLocation[2] = GCM_LOCATION_RSX;
	sf.colorLocation[3] = GCM_LOCATION_RSX;
	sf.colorOffset[1] = 0;
	sf.colorOffset[2] = 0;
	sf.colorOffset[3] = 0;
	sf.colorPitch[1] = 64;
	sf.colorPitch[2] = 64;
	sf.colorPitch[3] = 64;

	sf.depthFormat = GCM_SURFACE_ZETA_Z16;
	sf.depthLocation = GCM_LOCATION_RSX;
	sf.depthOffset = depth_offset;
	sf.depthPitch = depth_pitch;

	sf.type = GCM_TEXTURE_LINEAR;
	sf.antiAlias 	= GCM_SURFACE_CENTER_1;

	sf.width = buffer->width;
	sf.height = buffer->height;
	sf.x = 0;
	sf.y = 0;

	rsxSetSurface(context, &sf);
}
/*
void copyToBuffer(gcmContextData *context, u32 buf_width, u32 buf_height, rsxBuffer *buffer, u32 *bitmap, u32 bitmap_off){
	gcmTransferScale xferscale;
	memset(&xferscale, 0, sizeof(xferscale));

	gcmTransferSurface xfersurface;
	memset(&xfersurface, 0, sizeof(xfersurface));

	// configure transfer scale 
	xferscale.conversion = GCM_TRANSFER_CONVERSION_TRUNCATE;
	xferscale.format = GCM_TRANSFER_SCALE_FORMAT_A8R8G8B8;
	xferscale.operation = GCM_TRANSFER_OPERATION_SRCCOPY;
	xferscale.clipX = 0;
	xferscale.clipY = 0;
	xferscale.clipW = buffer->width;
	xferscale.clipH = buffer->height;
	xferscale.outX  = 0;
	xferscale.outY  = 0;
	xferscale.outW  = buffer->width;
	xferscale.outH  = buffer->height;
	xferscale.inW   = buf_width;
	xferscale.inH   = buf_height;

	xferscale.ratioX = rsxGetFixedSint32((float)xferscale.inW / (float)xferscale.outW);
	xferscale.ratioY = rsxGetFixedSint32((float)xferscale.inH / (float)xferscale.outH);

	xferscale.pitch = depth_pitch;
	xferscale.origin = GCM_TRANSFER_ORIGIN_CORNER;
	xferscale.interp = GCM_TRANSFER_INTERPOLATOR_NEAREST;
	xferscale.offset = bitmap_off;

	xferscale.inX = rsxGetFixedUint16(1.0f);
	xferscale.inY = rsxGetFixedUint16(1.0f);

	// configure destination surface for transfer //
	xfersurface.format = GCM_TRANSFER_SURFACE_FORMAT_A8R8G8B8;
	xfersurface.pitch = depth_pitch;
	xfersurface.offset = depth_offset;

	// blit font buffer //
	rsxSetTransferScaleMode(context, GCM_TRANSFER_LOCAL_TO_LOCAL, GCM_TRANSFER_SURFACE);
	rsxSetTransferScaleSurface(context, &xferscale, &xfersurface);
}
*/

void RescaleBuffer(gcmContextData *context, u32 width, u32 height, rsxBuffer *buffer){
	gcmTransferScale xferscale;
	memset(&xferscale, 0, sizeof(xferscale));

	gcmTransferSurface xfersurface;
	memset(&xfersurface, 0, sizeof(xfersurface));

	// configure transfer scale //
	xferscale.conversion = GCM_TRANSFER_CONVERSION_TRUNCATE;
	xferscale.format = GCM_TRANSFER_SCALE_FORMAT_A8R8G8B8;
	xferscale.operation = GCM_TRANSFER_OPERATION_SRCCOPY;
	xferscale.clipX = 0;
	xferscale.clipY = 0;
	xferscale.clipW = buffer->width;
	xferscale.clipH = buffer->height;
	xferscale.outX  = 0;
	xferscale.outY  = 0;
	xferscale.outW  = width;
	xferscale.outH  = height;
	xferscale.inW   = buffer->width;
	xferscale.inH   = buffer->height;

	xferscale.ratioX = rsxGetFixedSint32((float)xferscale.inW / (float)xferscale.outW);
	xferscale.ratioY = rsxGetFixedSint32((float)xferscale.inH / (float)xferscale.outH);

	xferscale.pitch  = depth_pitch;
	xferscale.origin = GCM_TRANSFER_ORIGIN_CORNER;
	xferscale.interp = GCM_TRANSFER_INTERPOLATOR_NEAREST;
	xferscale.offset = depth_offset;

	xferscale.inX = rsxGetFixedUint16(1.0f);
	xferscale.inY = rsxGetFixedUint16(1.0f);

	// configure destination surface for transfer //
	xfersurface.format = GCM_TRANSFER_SURFACE_FORMAT_A8R8G8B8;
	xfersurface.pitch  = depth_pitch;
	xfersurface.offset = depth_offset;

	// blit to buffer //
	rsxSetTransferScaleMode(context, GCM_TRANSFER_LOCAL_TO_LOCAL, GCM_TRANSFER_SURFACE);
	rsxSetTransferScaleSurface(context, &xferscale, &xfersurface);

	gcmSurface sf;

	sf.colorFormat = GCM_SURFACE_X8R8G8B8;
	sf.colorTarget = GCM_SURFACE_TARGET_0;
	sf.colorLocation[0] = GCM_LOCATION_RSX;
	sf.colorOffset[0]   = buffer->offset;
	sf.colorPitch[0]    = depth_pitch;

	sf.colorLocation[1] = GCM_LOCATION_RSX;
	sf.colorLocation[2] = GCM_LOCATION_RSX;
	sf.colorLocation[3] = GCM_LOCATION_RSX;
	sf.colorOffset[1] = 0;
	sf.colorOffset[2] = 0;
	sf.colorOffset[3] = 0;
	sf.colorPitch[1] = 64;
	sf.colorPitch[2] = 64;
	sf.colorPitch[3] = 64;

	sf.depthFormat   = GCM_SURFACE_ZETA_Z16;
	sf.depthLocation = GCM_LOCATION_RSX;
	sf.depthOffset   = depth_offset;
	sf.depthPitch    = depth_pitch;

	sf.type         = GCM_TEXTURE_LINEAR;
	sf.antiAlias 	= GCM_SURFACE_CENTER_1;

	sf.width  = width;
	sf.height = height;
	sf.x = 0;
	sf.y = 0;

	rsxSetSurface(context, &sf);
}
