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

#ifndef __NORSX_ANIMATION_H__
#define __NORSX_ANIMATION_H__

#include "Min.h"
#include "Image.h"

typedef struct {
//ALL THESE VALUES ARE LOADED WHEN YOU WILL CALL LoadAnimation() FUNCTION

	uint32_t elem_num;     //the number of elements of the animation.
	uint32_t elem_height;  //the height of a single element
	uint32_t elem_width;   //the width of a single element


//DON'T CHANGE THE FOLLOWINGS VALUES IN YOUR CODE.

	uint32_t chromakey;    //Chroma Key. you don't need it if you will use AlphaDrawAnimation
	int load;              //check if something it's loaded
	uint16_t bitmap_width;       //it is needed to calculate the frame. DO NOT CHANGE IT
	uint16_t *elem_x;       //it is needed to calculate the frame. DO NOT CHANGE IT
	uint16_t *elem_y;       //it is needed to calculate the frame. DO NOT CHANGE IT
	uint32_t *bitmap;
} NoRSX_Animation;


class Animation{
public:
	Animation(Minimum *g){
		G=g;
	}
	~Animation(){}
//use this only if you will use AlphaDrawAnimation
	void LoadAnimation (uint32_t Elem_num, uint32_t Elem_w, uint32_t Elem_h, pngData* PNG, NoRSX_Animation *anim);

//use these for AlphaDrawAnimation and DrawAnimation
	void LoadAnimation (uint32_t Elem_num, uint32_t Elem_w, uint32_t Elem_h, uint32_t ChromaKey, pngData* PNG, NoRSX_Animation *anim);
	void LoadAnimation (uint32_t Elem_num, uint32_t Elem_w, uint32_t Elem_h, uint32_t ChromaKey, jpgData* JPG, NoRSX_Animation *anim);

//REMEMBER TO CLEAN THE NoRSX_Animation struct before the NoRSX_Exit() function.
	void ClearAnimation(NoRSX_Animation *anim);

	void DrawAnimation (int X, int Y, uint32_t frame, NoRSX_Animation *anim);
	void AlphaDrawAnimation (int X, int Y, uint32_t frame, NoRSX_Animation *anim);

private:
	Minimum *G;
};

#endif
