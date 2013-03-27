#ifndef _UNCOMP_H
#define _UNCOMP_H

#include <stdio.h>
#include <string.h>

# define RING_SIZE	4096
# define MATCH_LENGTH	18
# define THRESHOLD	2

# define GET_BYTE(buf, end_buf, val)	\
	if (buf == end_buf)		\
		break;			\
	val = *buf++;			\

# define PUT_BYTE(buf, end_buf, val)						\
	if (buf == end_buf)							\
	{									\
		fprintf(stderr, "[-] Not enough space in output buffer !\n");	\
		return 0;							\
	}									\
	*buf++ = val;

int uncomp(unsigned char *buf, unsigned char *buf_end, unsigned char *out_buf, unsigned char *out_buf_end);

#endif
