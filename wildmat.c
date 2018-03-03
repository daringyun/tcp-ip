#include "global.h"
static int Star(char *s,char *p,char **argv);

static int
Star(s,p,argv)
register char *s;
register char *p;
register char **argv;
{
	char *cp = s;
	while (wildmat(cp, p, argv) == FALSE)
		if(*++cp == '\0')
			return -1;
	return cp - s;
}

int
wildmat(s,p,argv)
register char *s;
register char *p;
register char **argv;
{
	register int last;
	register int matched;
	register int reverse;
	register int cnt;

	for(; *p; s++,p++){
		switch(*p){
		case '\\':
			/* Literal match with following character; fall through. */
			p++;
		default:
			if(*s != *p)
				return FALSE;
			continue;
		case '?':
			/* Match anything. */
			if(*s == '\0')
				return FALSE;
			continue;
		case '*':
			/* Trailing star matches everything. */
			if(argv == NULL)
				return *++p ? 1 + Star(s, p, NULL) : TRUE;
			if(*++p == '\0'){
				cnt = strlen(s);
			} else {
				if((cnt = Star(s, p, argv+1)) == -1)
					return FALSE;
			}
			*argv = mallocw(cnt+1);
			strncpy(*argv,s,cnt);
			*(*argv + cnt) = '\0';
			return TRUE;
		case '[':
			/* [^....] means inverse character class. */
			reverse = (p[1] == '^') ? TRUE : FALSE;
			if(reverse)
				p++;
			for(last = 0400, matched = FALSE; *++p && *p != ']'; last = *p){
				/* This next line requires a good C compiler. */
				if(*p == '-' ? *s <= *++p && *s >= last : *s == *p)
					matched = TRUE;
			}
			if(matched == reverse)
				return FALSE;
			continue;
		}
	}
	/* For "tar" use, matches that end at a slash also work. --hoptoad!gnu */
	return *s == '\0' || *s == '/';
}


#ifdef	TEST
#include <stdio.h>

extern char *gets();

main()
{
	char pattern[80];
	char text[80];
	char *argv[80], *cp;
	int cnt;
    
	while (TRUE){
		printf("Enter pattern:  ");
		if(gets(pattern) == NULL)
			break;
		while (TRUE){
			bzero(argv,80*sizeof(char *);
			printf("Enter text:  ");
			if(gets(text) == NULL)
				exit(0);
			if(text[0] == '\0')
				/* Blank line; go back and get a new pattern. */
				break;
			printf("      %d\n", wildmat(text, pattern, argv);
			for(cnt = 0; argv[cnt] != NULL; ++cnt){
				printf("String %d is: '%s'\n",cnt,argv[cnt]);
				free(argv[cnt]);
			}
		}
	}
	exit(0);
}
#endif	/* TEST */
