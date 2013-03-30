#include <ctype.h>
#include "arg.h"
#include "uncomp.h"
#include "bmp.h"

void hex_dump(void *data, int size);

int is_img(unsigned char *buf, unsigned int size)
{
	unsigned char width;
	unsigned char height;

	width = *(unsigned char*)buf++;
	height = *(unsigned char*)buf;
	if (width * height == size - 2)
		return 1;
	return 0;
}

void mirrorud(unsigned char *pixelData, unsigned int width, unsigned int height)
{
	unsigned int x,y;

    	for (x = 0; x < width; x++)
	{
		for (y = 0; y < height / 2; y++)
		{
			int a = x + (y * width);
                	char temp = pixelData[a];
                	pixelData[a] = pixelData[x + (height - 1 - y) * width];
                	pixelData[x + (height - 1 - y) * width]=temp;
            	}
    	}
}

void readtobmp(unsigned char *buf, char *name)
{
  	BMP b;
  	char output_name[500];

	b.width = *(unsigned char*)buf++;
	b.height = *(unsigned char*)buf++;
	b.data = buf;
	mirrorud(b.data, b.width, b.height);
	//hex_dump(b.data, b.width * b.height + 2);
	/*rmdir("./extract");
	mkdir("./extract", 0755);*/
	strcpy(output_name, "./extract/");
  	strcat(output_name, name);
  	strcat(output_name, ".bmp");
  	if (!bmp_save(&b, output_name))
	{
		fprintf(stderr, "[-] bmp_save(..., \"%s\")\n", output_name);
	}
}

void bmtobmp(unsigned char *buf, char *name)
{
  	BMP b;
  	char output_name[500];

	b.width = *(unsigned char*)buf++;
	b.height = *(unsigned char*)buf++;
	b.data = buf;
	//mirrorud(b.data, b.width, b.height);
	//hex_dump(b.data, b.width * b.height + 2);
	/*rmdir("./extract");
	mkdir("./extract", 0755);*/
	strcpy(output_name, "./extract/");
  	strcat(output_name, name);
  	strcat(output_name, ".bmp");
  	if (!bmp_savebm(&b, output_name))
	{
		fprintf(stderr, "[-] bmp_save(..., \"%s\")\n", output_name);
	}
}

void strupr(char *string)
{
	while(*string)
   	{
       		if (*string >= 'a' && *string <= 'z')
       		{
          		*string = *string - 32;
       		}
       		string++;
   	}
}

char *strstri(char *s1, char *s2)
{
	char *s, *t, *u;

    	if ((s1 == NULL) || (s2 == NULL))
        	return NULL;
    	s = strdup(s1);
    	if (s == NULL)
        	return NULL;
    	t = strdup(s2);
    	if (t == NULL)
        {
        	free(s);
        	return NULL;
        }
    	strupr(s);
    	strupr(t);
    	if ((u = strstr (s, t)) != NULL)
        	u = s1 + (u - s);
    	free(s);
    	free(t);
    	return u;
}

void handleBMFile(unsigned char *buf, unsigned int size)
{
	unsigned short num_entry = 0;
	unsigned int i, j, nb, lsize, val;
	unsigned char **nentry = NULL;
	unsigned char *sbuf = NULL;
	char name[4096];


	(void)size;
	num_entry = *(unsigned short*)buf;
	buf += 2;
	printf("Num_entry = %X\n", num_entry);
	if (!(nentry = malloc(sizeof (char*) * num_entry)))
	{
		perror("malloc()");
		return;
	}
	for (i = 0; i < num_entry; i++)
	{
		sbuf = buf;
		nb = *(buf + 1);
		buf += 2;
		lsize = 2;
		for (j = 0; j < nb; j++)
		{
			val = *(buf + 1);
			buf += 2;
			lsize += 2;
			if (val)
			{
				buf += val;
				lsize += val;
			}
		}
		if (!(nentry[i] = malloc(sizeof (char) * lsize)))
		{
			perror("malloc()");
			break;
		}
		memcpy(nentry[i], sbuf, lsize);
		printf("Dump %d\n", i);
		//hex_dump(nentry[i], lsize);
		//if (i == 17)
		memset(name, 0, 4096);
		sprintf(name, "LOL_%d", i);
		bmtobmp(nentry[i], name);
		//readtobmp(nentry[i] + 1, name);
		//exit(0);
	}
	for (i = 0; i < num_entry; i++)
	{
		if (nentry[i])
			free(nentry[i]);
	}
	free(nentry);
}

void extract(struct s_conf *conf)
{
	unsigned int uncomp_size = 0;
	unsigned char *buf = NULL;
	unsigned char *out_buf = NULL;
	unsigned short num_entry = 0;
	unsigned int i;
	unsigned char width, height;
	char name[4096];

	buf = conf->map;
	uncomp_size = *(unsigned int*)buf;
	buf += 4;
	printf("Uncompressed Size = %X\n", uncomp_size);
	if (!(out_buf = malloc(sizeof (char) * uncomp_size)))
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	if (!uncomp(buf, conf->map + conf->fin_size, out_buf, out_buf + uncomp_size))
	{
		free(out_buf);
		exit(EXIT_FAILURE);
	}
	hex_dump(out_buf, uncomp_size);
	if (is_img(out_buf, uncomp_size))
	{
		printf("[+] Image !\n");
		readtobmp(out_buf, "LOL");
	}
	else if (strstri(conf->filename, "BM.LZW"))
	{
		handleBMFile(out_buf, uncomp_size);
	}
	else
	{
		buf = out_buf;
		num_entry = *(unsigned short*)buf;
		buf += 2;
		printf("[-] Not an image ! Num_entry = %X\n", num_entry);
		for (i = 0; i < num_entry; i++)
		{
			memset(name, 0, 4096);
			sprintf(name, "LOL_%d", i);
			width = *buf;
			height = *(buf + 1);
			readtobmp(buf, name);
			buf = buf + (width * height) + 2;
		}
	}
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

