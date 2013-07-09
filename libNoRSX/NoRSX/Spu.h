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
