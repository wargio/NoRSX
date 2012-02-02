#ifndef __NORSX_MAIN_H__
#define __NORSX_MAIN_H__

#include "rsxutil.h"
#include "EventHandler.h"
#include "Image.h"
#include "spu.h"


class NoRSX : public EventH, public Image{
public:

	 NoRSX();
	~NoRSX();

	void Flip(){
		flip();
	}
private:
	static void ExitCallBack();
	void *host_addr;
//	void *main_addr;
};

#endif
