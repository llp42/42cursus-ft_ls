/*
 * "It's not a bug — it's an undocumented feature."
 *
 * Author: Leonardo Lopes Pereira
 * Email: lepereir@student.42.fr
 *
 * SPDX-License-Identifier: blessing
 */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_ft_ls	ls;

	bootstrap(&ls, argc, argv);
	return (0);
}
