#include <stdio.h>
#include "global.h"
#include "nospc.h"

struct stopwatch Sw[NSW];

/* Stop a stopwatch and record its value.
 * Uses stopval() routine in stopwatch.asm
 */
void
swstop(n)
int n;
{
	register struct stopwatch *sw;
	int32 ticks;

	ticks = 65536 - stopval();
	sw = &Sw[n];

	if(sw->calls++ == 0){
		sw->maxval = ticks;
		sw->minval = ticks;
	} else if(ticks > sw->maxval){
		sw->maxval = ticks;
	} else if(ticks < sw->minval){
		sw->minval = ticks;
	}
	sw->totval += ticks;
}
int
doswatch(argc,argv,p)
int argc;
char *argv[];
void *p;
{
	register struct stopwatch *sw;
	long maxval,minval,avgval;
	int i;

	if(argc > 1){
		/* Clear timers */
		for(i=0,sw=Sw;i < NSW;i++,sw++){
			sw->calls = 0;
			sw->totval = 0;
		}
	}
	for(i=0,sw=Sw;sw < &Sw[NSW];i++,sw++){
		if(sw->calls == 0)
			continue;
		minval = sw->minval * 838L/1000;
		maxval = sw->maxval * 838L/1000;
		avgval = sw->totval / sw->calls * 838L / 1000L;
		printf("%u: calls %lu min %lu max %lu avg %lu tot %lu\n",
		 i,sw->calls,minval,maxval,avgval,sw->totval);

	}
	return 0;
}
