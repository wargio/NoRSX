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


#ifndef __NORSX_EVENTHANDLER_H__
#define __NORSX_EVENTHANDLER_H__
#include <sysutil/sysutil.h>


/*Return*/
#define NO_SIGNAL				0
#define EXIT_SIGNAL				1

#define APP_EXIT				0
#define APP_START				1

#define XMB_OPEN				0
#define XMB_CLOSE				1



/*! \brief Event slot 0 */	
#define EVENT_SLOT0				0
/*! \brief Event slot 1 */
#define EVENT_SLOT1				1
/*! \brief Event slot 2 */
#define EVENT_SLOT2				2
/*! \brief Event slot 3 */
#define EVENT_SLOT3				3

class EventHandler{
public:
	 EventHandler();
	~EventHandler();
	void CheckCallBack();
	void RegisterCallBack(s32 SLOT);
	void UnregisterCallBack(s32 SLOT);
	int  GetAppStatus() const;
	int  GetXMBStatus() const;
	int  ExitSignalStatus() const;
	void AppStart();
	void AppExit();
private:
	static void EvHandler(u64 status, u64 param, void * userdata);
	static int app_status, xmb_status, app_signal;

};

#endif
