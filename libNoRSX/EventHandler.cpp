/*
 * Copyright (c) 2013, Giovanni Dante Grazioli (deroad)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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
