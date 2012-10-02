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

#ifndef __NORSX_SPU_H__
#define __NORSX_SPU_H__

#include <sys/spu.h>
#include <NoRSX/Errors.h>

#define ptr2ea(x)			((u64)((void*)(x)))

typedef struct {
	sysSpuImage image;
	
	sysSpuThreadArgument args;
	sysSpuThreadGroupAttribute group_attr;
	sysSpuThreadAttribute attr;
	
	u32 group_num;

	u32 status;
	u32 cause;


	u32 spu_id;
	u32 thread_id;
	u32 group_id;

	int loaded_grp_attr;
	int loaded_attr;
	
} NoRSX_Spu;

class Spu{
public:
	 Spu();
	~Spu();

	void SpuAttrubute(NoRSX_Spu *spus, const char *text);
	void SpuGroupAttribute(NoRSX_Spu *spus, const char* text, u32 group_type, u32 mem_container);
	void SpuArgs(NoRSX_Spu *spus, u64 arg1, u64 arg2, u64 arg3, u64 arg4);
	void SpuThreadGroupCreate(NoRSX_Spu *spus, u32 priority);
	void SpuThreadInit(NoRSX_Spu *spus);
	int  LoadELF(const void *module, NoRSX_Spu *spus);
	int  LoadELF(const char *module_path, NoRSX_Spu *spus);
	void SpuCloseImage(NoRSX_Spu *spus);

	int  GetSpuError() const;
	
protected:
	int error;

};

#endif
