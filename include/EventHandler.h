#ifndef __NORSX_EVENT_HANDLER__
#define __NORSX_EVENT_HANDLER__

#include <sysutil/video.h>
#include <sysutil/sysutil.h>

class EventH{
public:
	EventH();
	~EventH(){}

	static void CheckEvent();
	int Exit(){return exitapp;}
	int XMB(){return xmbopen;}
protected:
	static int exitapp, xmbopen;
	static inline void eventHandler(u64 status, u64 param, void * userdata);
};
#endif
