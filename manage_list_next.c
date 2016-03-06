/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list_next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:10:42 by tboos             #+#    #+#             */
/*   Updated: 2016/03/06 08:36:56 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "ft_ls.h"

static void	ft_printtime(t_dirent *lst)
{
	char		*tmp;
	int			i;

	ft_putchar(' ');
	if ((tmp = ctime(&(lst->stat.st_mtime))))
	{
		i = ft_strlen(tmp);
		tmp[i - 9] = '\0';
		ft_putstr(tmp + 4);
	}
	ft_putchar(' ');
}

static int	ft_findtotal(t_dirent *lst, int *len)
{
	int			total;
	int			memo;
	int			tmp;

	memo = 0;
	total = 0;
	while (lst)
	{
		total += lst->stat.st_blocks;
		if ((tmp = lst->stat.st_size) > memo)
			memo = tmp;
		if ((tmp = lst->stat.st_blksize) > memo)
			memo = tmp;
		lst = lst->next;
	}
	while (memo)
	{
		*len += 1;
		memo /= 10;
	}
	return (total);
}

static char		ft_puttype(int st_mode)
{
	if (S_ISDIR(st_mode))
		return ('d');
	if (S_ISREG(st_mode))
		return ('-');
	if (S_ISCHR(st_mode))
		return ('c');
	if (S_ISBLK(st_mode))
		return ('b');
	if (S_ISLNK(st_mode))
		return ('l');
	if (S_ISFIFO(st_mode))
		return ('f');
	return ('s');
}

void		ft_printl(t_dirent *lst)
{
	int			len;
	int			total;
	char		c;

	len = 0;
	c = ft_puttype(lst->stat.st_mode);
	total = ft_findtotal(lst, &len);
	ft_putstr_nbr_str("total ", total, "\n");
	while (lst)
	{
		ft_putchar(c);
		ft_printperm(lst);
		ft_putstr_nbr_str("  ", lst->stat.st_nlink, " ");
		ft_putstr((getpwuid(lst->stat.st_uid))->pw_name);
		ft_putstr("  ");
		ft_putstr((getgrgid(lst->stat.st_gid))->gr_name);
		if (c == '-' || c == 'd' || c == 'l')
			ft_putcstr(ft_itoa(lst->stat.st_size), ' ', len, 'R');
		else
			ft_putmajmin(lst->stat);
		ft_printtime(lst);
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
