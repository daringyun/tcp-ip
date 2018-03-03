
#include "global.h"
#include "stdio.h"
#include <stdarg.h>

int pascal near __vprinter(
	unsigned pascal near (*)(void *,unsigned, FILE*),
	FILE *, char *, void _ss *);
static unsigned pascal near
fputter(void *ptr,unsigned n,FILE *fp)
{
	return fwrite(ptr,1,n,fp);
}


int
vfprintf(FILE *fp,char *fmt, va_list args)
{


	if(fp == NULL || fp->cookie != _COOKIE)
		return -1;
	return __vprinter(fputter,fp,fmt,(void _ss *)args);
}
