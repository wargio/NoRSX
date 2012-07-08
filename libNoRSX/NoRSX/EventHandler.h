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


#ifndef __NORSX_EVENTHANDLER_H__
#define __NORSX_EVENTHANDLER_H__
#include <sysutil/sysutil.h>


/*Return*/
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
	void AppStart();
	void AppExit();
private:
	static void EvHandler(u64 status, u64 param, void * userdata);
	static int app_status, xmb_status;

};

#endif
