/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list_next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:10:42 by tboos             #+#    #+#             */
/*   Updated: 2016/03/07 12:07:30 by tboos            ###   ########.fr       */
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

static void	ft_findpad(t_dirent *lst)
{
	t_lpadding	tmp;
	t_dirent	*rabbit;

	bzero(&tmp, sizeof(t_lpadding));
	rabbit = lst;
	while (rabbit)
	{
		lst->pad.total += rabbit->stat.st_blocks;
		if (rabbit->stat.st_nlink > tmp.nlink)
			tmp.nlink = rabbit->stat.st_nlink;
		if (lst->pad.uid < (int)ft_strlen(rabbit->passwd.pw_name))
			lst->pad.uid = ft_strlen(rabbit->passwd.pw_name);
		if (lst->pad.uid < (int)ft_strlen(rabbit->group.gr_name))
			lst->pad.gid = ft_strlen(rabbit->group.gr_name);
		if (tmp.size < (int)rabbit->stat.st_size)
			tmp.size = rabbit->stat.st_size;
		rabbit = rabbit->next;
	}
	while ((tmp.nlink /= 10))
		(lst->pad.nlink)++;
	while ((tmp.size /= 10))
		(lst->pad.size)++;
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
	t_dirent	*rabbit;

	rabbit = lst;
	bzero(&(lst->pad), sizeof(t_lpadding));
	ft_findpad(lst);
	ft_putstr_nbr_str("total ", lst->pad.total, "\n");
	while (lst)
	{
		rabbit->pad.c = ft_puttype(lst->stat.st_mode);
		ft_putchar(rabbit->pad.c);
		ft_printperm(lst);
		ft_putcstr(ft_itoa(lst->stat.st_nlink), ' ', rabbit->pad.nlink + 3, 'R');
		ft_putchar(' ');
		ft_putcstr(lst->passwd.pw_name, ' ', rabbit->pad.uid + 2, 'L');
		ft_putcstr(lst->group.gr_name, ' ', rabbit->pad.gid, 'L');
		if (rabbit->pad.c == '-' || rabbit->pad.c == 'd' || rabbit->pad.c == 'l')
			ft_putcstr(ft_itoa(lst->stat.st_size), ' ', rabbit->pad.size + 3, 'R');
		else
			ft_putmajmin(lst->stat);
		ft_printtime(lst);
		ft_putendl(lst->data->d_name);
		lst = lst->next;
	}
}
