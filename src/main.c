#include <ctype.h>
#include "arg.h"
#include "uncomp.h"

void hex_dump(void *data, int size);

void extract(struct s_conf *conf)
{
	unsigned int uncomp_size = 0;
	unsigned char *buf = NULL;
	unsigned char *out_buf = NULL;

	buf = conf->map;
	uncomp_size = *(unsigned int*)buf;
	buf += 4;
	printf("Uncompressed Size = %X\n", uncomp_size);
	if (!(out_buf = malloc(sizeof (char) * uncomp_size)))
	{
		perror("malloc()");
		return;
	}
	if (!uncomp(buf, conf->map + conf->fin_size, out_buf, out_buf + uncomp_size))
	{
		free(out_buf);
		return;
	}
	hex_dump(out_buf, uncomp_size);
	free(out_buf);
}

int main(int argc, char **argv)
{
        struct s_conf conf = {0};

   	parse_opt(argc, argv, &conf);
        check_opt(&conf, argv[0]);
	if (conf.extract)
		extract(&conf);
	clean(&conf);
	return 0;
}

void hex_dump(void *data, int size)
{
    unsigned char *p = (unsigned char*)data;
    unsigned char c;
    int n;
    char bytestr[4] = {0};
    char addrstr[10] = {0};
    char hexstr[16 * 3 + 5] = {0};
    char charstr[16 * 1 + 5] = {0};

    for(n = 1; n <= size; n++)
    {
        if (n % 16 == 1)
        {
                snprintf(addrstr, sizeof(addrstr), "%.4x",
                    ((unsigned int)p - (unsigned int)data));
        }
        c = *p;
        if (isprint(c) == 0)
        {
            c = '.';
        }
        snprintf(bytestr, sizeof(bytestr), "%02X ", *p);
        strncat(hexstr, bytestr, sizeof(hexstr) - strlen(hexstr) - 1);
        snprintf(bytestr, sizeof(bytestr), "%c", c);
        strncat(charstr, bytestr, sizeof(charstr) - strlen(charstr) - 1);
        if (n % 16 == 0)
        {
            printf("[%8.8s]   %-50.50s  %s\n", addrstr, hexstr, charstr);
            hexstr[0] = 0;
            charstr[0] = 0;
        }
        else if (n % 8 == 0)
        {
            strncat(hexstr, "  ", sizeof(hexstr) - strlen(hexstr) - 1);
            strncat(charstr, " ", sizeof(charstr) - strlen(charstr) - 1);
        }
        p++;
    }
    if (strlen(hexstr) > 0)
    {
        printf("[%8.8s]   %-50.50s  %s\n", addrstr, hexstr, charstr);
    }
}

