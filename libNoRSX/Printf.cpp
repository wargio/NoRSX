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


#include <stdio.h>
#include <fstream>
#include <NoRSX/Printf.h>
#include <stdarg.h>
using namespace std;

Printf::Printf(const char* filename){
	f.open(filename,ios::out);
	if(f.fail())
		can_print =-1;
	else
		can_print = 0;
}

int Printf::printf(const char *a, ...){
	char text[1024];
	va_list va;
	va_start(va, a);
	vsnprintf(text, sizeof text, a, va);
	if(can_print>0)
		f << text;
	return 1;
}

Printf::~Printf(){
	if(can_print==0)
		f.close();
}
