#include <stdio.h>
#include <fstream>
#include <NoRSX/Printf.h>
#include <stdarg.h>
using namespace std;

static fstream f;
static int can_print = -1;
int init_print(const char* filename){
	f.open(filename,ios::out);
	if(f.fail())
		return -1;
	else
		can_print = 0;
	return 1;
}

int print(const char *a, ...){
	char text[1024];
	va_list va;
	va_start(va, a);
	vsnprintf(text, sizeof text, a, va);
	if(can_print==0)
		f << text;
	return 1;
}

void end_print(){
	if(can_print==0)
		f.close();
}
