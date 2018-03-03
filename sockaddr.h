#ifndef _SOCKADDR_H
#define _SOCKADDR_H

/* Generic socket address structure */
struct sockaddr {
	short sa_family;
	char sa_data[14];
};

/* This is a structure for "historical" reasons (whatever they are) */
struct in_addr {
	unsigned long s_addr;
};

/* Socket address, DARPA Internet style */
struct sockaddr_in {
	short sin_family;
	unsigned short sin_port;
	struct in_addr sin_addr;
	char sin_zero[8];
};

#define	SOCKSIZE	(sizeof(struct sockaddr))
#define MAXSOCKSIZE	SOCKSIZE /* All sockets are of the same size for now */

#endif /* _SOCKADDR_H */
