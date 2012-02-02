#include "EventHandler.h"

int EventH::exitapp, EventH::xmbopen;

EventH::EventH(){
	exitapp=1;
	sysUtilRegisterCallback(SYSUTIL_EVENT_SLOT0, eventHandler, NULL);
}


inline void EventH::eventHandler(u64 status, u64 param, void * userdata){
	switch(status){
		case SYSUTIL_EXIT_GAME:
			exitapp = 0;
			break;
		case SYSUTIL_MENU_OPEN:
			xmbopen = 1;
			break;
		case SYSUTIL_MENU_CLOSE:
			xmbopen = 0;
			break;
	}
}


void EventH::CheckEvent(){
	sysUtilCheckCallback();
}

