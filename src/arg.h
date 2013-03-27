#ifndef __ARG_H__
#define __ARG_H__

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

struct s_conf
{
        char *filename;
	int extract;
	FILE *fin;
	size_t fin_size;
	unsigned char *map;
};

void help(char *name);
void parse_opt(int argc, char **argv, struct s_conf *conf);
void check_opt(struct s_conf *conf, char *name);
void clean(struct s_conf *conf);

#endif // __ARG_H__

