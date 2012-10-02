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

#ifndef __NORSX_ANIMATION_H__
#define __NORSX_ANIMATION_H__

#include "Min.h"
#include "Image.h"

#define ANIMATION_ALPHA_CHROMAKEY	0x000000ff


typedef struct {
//ALL THESE VALUES ARE LOADED WHEN YOU WILL CALL LoadAnimation() FUNCTION

	uint32_t elem_num;     //the number of elements of the animation.
	uint32_t elem_height;  //the height of a single element
	uint32_t elem_width;   //the width of a single element


//DON'T CHANGE THE FOLLOWINGS VALUES IN YOUR CODE.

	uint32_t chromakey;    //Chroma Key. you don't need it if you will use AlphaDrawAnimation
	uint32_t bitmap_height;//the height of the bitmap (DO NOT CHANGE IT) this element is loaded automatically
	uint32_t bitmap_width; //the width of the bitmap (DO NOT CHANGE IT) this element is loaded automatically
	int load;              //check if something it's loaded
	uint32_t elem_x;       //it is needed to calculate the frame. DO NOT CHANGE IT
	uint32_t elem_y;       //it is needed to calculate the frame. DO NOT CHANGE IT
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
	void CleanAnimation(NoRSX_Animation *anim);

	void DrawAnimation (uint32_t X, uint32_t Y, uint32_t frame, NoRSX_Animation *anim);
	void AlphaDrawAnimation (uint32_t X, uint32_t Y, uint32_t frame, NoRSX_Animation *anim);

private:
	Minimum *G;
};

#endif
