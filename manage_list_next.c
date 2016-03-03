/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list_next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:10:42 by tboos             #+#    #+#             */
/*   Updated: 2016/03/03 14:47:39 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "ft_ls.h"

/*
void	ft_swaplist(t_dirent *rabbit, t_dirent *turtle)
{
	t_dirent	*memo;

	memo = turtle->next;
	turtle->next = turtle->next->next;
	memo->next = rabbit->next;
	rabbit->next = memo;
}

t_dirent	*ft_listshunt(t_dirent *begin, int arg)
{
	t_dirent	*stick;

	stick = begin;
	while (stick->next)
		stick = stick->next;
	stick->next = begin;
	stick = begin->next;
	while (stick != begin)
	{
		if (ft_cmpls(stick, begin, arg) < 0)
			begin = stick;
		stick = stick->next;
	}
	return (begin);
}
*/
static void	ft_printtime(t_dirent *lst)
{
	char	*tmp;
	int		i;

	if ((tmp = ctime(&(lst->stat.st_mtime))))
	{
		i = ft_strlen(tmp);
		tmp[i - 9] = '\0';
		ft_putstr(tmp + 4);
	}
}

void		ft_printl(t_dirent *lst)
{
	ft_putstr("total ?\n");
	while (lst)
	{
		ft_putchar((S_ISDIR(lst->stat.st_mode) ? 'd' : '-'));
		ft_printperm(lst);
		ft_putstr("  ");
		ft_putnbr(lst->stat.st_nlink);
		ft_putchar(' ');
		ft_putstr((getpwuid(lst->stat.st_uid))->pw_name);
		ft_putstr("  ");
		ft_putstr((getgrgid(lst->stat.st_gid))->gr_name);
		ft_putchar(' ');
		ft_putnbr(lst->data->d_reclen);
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
