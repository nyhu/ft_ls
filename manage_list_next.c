/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list_next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:10:42 by tboos             #+#    #+#             */
/*   Updated: 2016/03/06 02:17:12 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "ft_ls.h"

void		ft_printcol(t_dirent *lst, size_t nb_col, size_t ldisp, size_t jump)
{
	char		**tab;
	size_t		i;
	size_t		tmp;

		j++;
	}
}

static void	ft_printtime(t_dirent *lst)
{
	char		*tmp;
	int			i;

	if ((tmp = ctime(&(lst->stat.st_mtime))))
	{
		i = ft_strlen(tmp);
		tmp[i - 9] = '\0';
		ft_putstr(tmp + 4);
	}
}

static int	ft_findtotal(t_dirent *lst, int *len)
{
	int			total;
	int			tmp;

	tmp = 0;
	total = 0;
	while (lst)
	{
		total += lst->stat.st_blocks;
		tmp |= lst->stat.st_size;
		lst = lst->next;
	}
	while (tmp)
	{
		*len += 1;
		tmp /= 10;
	}
	return (total);
}

void		ft_printl(t_dirent *lst)
{
	int			len;
	int			total;

	len = 1;
	total = ft_findtotal(lst, &len);
	ft_putstr_nbr_str("total ", total, "\n");
	while (lst)
	{
		ft_putchar((S_ISDIR(lst->stat.st_mode) ? 'd' : '-'));
		ft_printperm(lst);
		ft_putstr_nbr_str("  ", lst->stat.st_nlink, " ");
		ft_putstr((getpwuid(lst->stat.st_uid))->pw_name);
		ft_putstr("  ");
		ft_putstr((getgrgid(lst->stat.st_gid))->gr_name);
		ft_putchar(' ');
		ft_putcstr(ft_itoa(lst->stat.st_size), ' ', len, 'R');
		ft_putchar(' ');
		ft_printtime(lst);
		ft_putchar(' ');
		ft_putendl(lst->data->d_name);
		lst = lst->next;
	}
}

long		ft_cmpls(t_dirent *turtle, t_dirent *rabbit, int arg)
{
	if ((MIN_C & arg))
		return (RABBIT_TIME_A - TURTLE_TIME_A);
	if ((MIN_U & arg))
		return (RABBIT_TIME_C - TURTLE_TIME_C);
	if ((MIN_T & arg))
		return (RABBIT_TIME_M - TURTLE_TIME_M);
	return (ft_strcmp(turtle->data->d_name, rabbit->data->d_name));
}
