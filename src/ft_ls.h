/*
 * "It's not a bug — it's an undocumented feature."
 *
 * Author: Leonardo Lopes Pereira
 * Email: lepereir@student.42.fr
 *
 * SPDX-License-Identifier: blessing
 */

#ifndef FT_LS_H
#define FT_LS_H

#include <stdbool.h>

typedef struct s_ft_ls
{
	bool long_format;
	bool recursive;
	bool all;
	bool reverse;
	bool sort_time;
	bool access_time;
	bool no_sort;
	bool no_owner;
	bool self_only;
	bool color;
	const char *progname;
	int operand_count;
	char **operands;
} t_ft_ls;

void bootstrap(t_ft_ls *ls, int argc, char **argv);

#endif
