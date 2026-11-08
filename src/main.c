/*
 * "It's not a bug — it's an undocumented feature."
 *
 * Author: Leonardo Lopes Pereira
 * Email: lepereir@student.42.fr
 *
 * SPDX-License-Identifier: blessing
 */

#include "ft_ls.h"

#include <errno.h>

int	main(int argc, char **argv)
{
	t_ft_ls	ls;
	int		i;

	bootstrap(&ls, argc, argv);
	if (ls.operand_count == 0)
		list_dir(&ls, ".");
	i = 0;
	while (i < ls.operand_count)
	{
		list_dir(&ls, ls.operands[i]);
		i++;
	}
	return (errno != 0);
}
