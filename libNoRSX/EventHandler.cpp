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

#include <NoRSX/EventHandler.h>

int EventHandler::app_status, EventHandler::xmb_status, EventHandler::app_signal;

EventHandler::EventHandler(){
	app_status = APP_EXIT;
	xmb_status = XMB_CLOSE;
	app_signal = NO_SIGNAL;
}

EventHandler::~EventHandler(){

}

void EventHandler::EvHandler(u64 status, u64 param, void * userdata){
	switch(status){
		case SYSUTIL_EXIT_GAME:
			app_status = APP_EXIT;
			app_signal = EXIT_SIGNAL;
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

int EventHandler::ExitSignalStatus() const {
	return app_signal;
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
