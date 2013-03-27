#include "arg.h"

void help(char *name)
{
        fprintf(stderr, "Usage : %s -x <.lzw>\n", name);
        exit(EXIT_FAILURE);
}

void parse_opt(int argc, char **argv, struct s_conf *conf)
{
        int c;
        int option_index = 0;
       	static struct option long_options[] =
	{
		{"extract", required_argument, 0, 'x'},
		{0, 0, 0, 0}
	};

        while (1)
        {
                c = getopt_long (argc, argv, "x:", long_options, &option_index);
                if (c == -1)
                        break;
                switch (c)
                {
                        case 'x':
                                conf->filename = optarg;
				conf->extract = 1;
                                break;
                        case '?':
                                break;
                        default:
                                help(argv[0]);
                }
        }
}

void check_opt(struct s_conf *conf, char *name)
{
        if (!conf->filename)
                help(name);
	if (!(conf->fin = fopen(conf->filename, "rb")))
	{
		perror("fopen()");
		exit(EXIT_FAILURE);
	}
	fseek(conf->fin, 0, SEEK_END);
	conf->fin_size = ftell(conf->fin);
	fseek(conf->fin, 0, SEEK_SET);
	if (!(conf->map = malloc(sizeof (char) * conf->fin_size)))
	{
		perror("malloc()");
		fclose(conf->fin);
		exit(EXIT_FAILURE);
	}
	if (fread(conf->map, 1, conf->fin_size, conf->fin) != conf->fin_size)
	{
		perror("fread()");
		clean(conf);
		exit(EXIT_FAILURE);
	}
}

void clean(struct s_conf *conf)
{
	free(conf->map);
	fclose(conf->fin);
}

