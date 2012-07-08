#include <NoRSX/EventHandler.h>

int EventHandler::app_status, EventHandler::xmb_status;

EventHandler::EventHandler(){
	app_status = APP_EXIT;
	xmb_status = XMB_CLOSE;
}

EventHandler::~EventHandler(){

}

void EventHandler::EvHandler(u64 status, u64 param, void * userdata){
	switch(status){
		case SYSUTIL_EXIT_GAME:
			app_status = APP_EXIT;
			break;
		case SYSUTIL_MENU_OPEN:
			xmb_status = XMB_OPEN;
			break;
		case SYSUTIL_MENU_CLOSE:
			xmb_status = XMB_CLOSE;
			break;
	}
}


void EventHandler::CheckCallBack(){
	sysUtilCheckCallback();
}


void EventHandler::RegisterCallBack(s32 SLOT){
	sysUtilRegisterCallback(SLOT , EvHandler, NULL);
}


void EventHandler::UnregisterCallBack(s32 SLOT){
	sysUtilUnregisterCallback(SLOT);
}

int EventHandler::GetAppStatus() const {
	return app_status;
}

int EventHandler::GetXMBStatus() const {
	return xmb_status;
}

void EventHandler::AppStart(){
	app_status = APP_START;
}

void EventHandler::AppExit(){
	app_status = APP_EXIT;
}
