/*
 * "It's not a bug — it's an undocumented feature."
 *
 * Author: Leonardo Lopes Pereira
 * Email: lepereir@student.42.fr
 *
 * SPDX-License-Identifier: blessing
 */

#include "ft_ls.h"

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char *progname(const char *argv0)
{
	const char *slash;

	if (argv0 == NULL)
		return ("ft_ls");
	slash = strrchr(argv0, '/');
	if (slash != NULL)
		return (slash + 1);
	return (argv0);
}

/* exit(2) is what ls(1) uses for a bad invocation */
static void invalid_option(const t_ft_ls *ls, int c)
{
	warnx("invalid option -- '%c'", c);
	fprintf(stderr, "usage: %s [-lRartufgdG] [file ...]\n", ls->progname);
	exit(2);
}

static void set_option(t_ft_ls *ls, int c)
{
	switch (c)
	{
		case 'l':
			ls->long_format = true;
			break ;
		case 'R':
			ls->recursive = true;
			break ;
		case 'a':
			ls->all = true;
			break ;
		case 'r':
			ls->reverse = true;
			break ;
		case 't':
			ls->sort_time = true;
			break ;
		case 'u':
			ls->access_time = true;
			break ;
		case 'f':
			ls->no_sort = true;
			ls->all = true; /* -f implies -a */
			break ;
		case 'g':
			ls->no_owner = true;
			ls->long_format = true; /* -g implies -l */
			break ;
		case 'd':
			ls->self_only = true;
			break ;
		case 'G':
			ls->color = true;
			break ;
		default:
			invalid_option(ls, optopt);
	}
}

void bootstrap(t_ft_ls *ls, int argc, char **argv)
{
	int c;

	*ls = (t_ft_ls){0};
	ls->progname = progname(argv[0]);
	opterr = 0; /* our wording, not getopt's */
	/* the '+' stops getopt() at the first operand, like ls(1) */
	while ((c = getopt(argc, argv, "+lRartufgdG")) != -1)
		set_option(ls, c);
	if (optind < argc)
	{
		ls->operands = &argv[optind];
		ls->operand_count = argc - optind;
	}
}
