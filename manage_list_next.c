/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list_next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:10:42 by tboos             #+#    #+#             */
/*   Updated: 2016/03/08 14:01:34 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "ft_ls.h"

static void	ft_printtime(t_dirent *lst, int arg)
{
	char		*tmp;
	int			i;
	t_timeval	timeval;
	time_t		time;

	time = ft_returntime(lst, arg);
	tmp = ctime(&time);
	bzero(&timeval, sizeof(t_timeval));
	ft_putchar(' ');
	if (!gettimeofday(&timeval, NULL) && CMP_6MONTH )
	{
		write(1, tmp + 4, 7);
		ft_putchar(' ');
		write(1, tmp + 20, 4);
	}
	else
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

char		ft_returntype(int st_mode)
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

void		ft_putcoldname(char *d_name, char c)
{
	if (c == 'd')
		ft_putcolendl(d_name, "CYAN");
	else if (c == '-')
		ft_putcolendl(d_name, "YELLOW");
	else if (c == 'c')
		ft_putcolendl(d_name, "RED");
	else if (c == 'b')
		ft_putcolendl(d_name, "MAGENTA");
	else if (c == 'l')
		ft_putcolendl(d_name, "BLUE");
	else if (c == 'f')
		ft_putcolendl(d_name, "CYAN");
	else
		ft_putcolendl(d_name, "");
}

void		ft_printl(t_dirent *lst, int arg)
{
	t_dirent	*rabbit;

	if (lst)
	{
		rabbit = lst;
		ft_findpad(lst);
		if (lst->next)
			ft_putstr_nbr_str("total ", lst->pad.total, "\n");
		while (lst)
		{
			ft_putchar(rabbit->pad.c);
			ft_printperm(lst);
			ft_putcstr(ft_st_itoa(lst->stat.st_nlink), ' ', rabbit->pad.nlink + 3, 'R');
			ft_putchar(' ');
			ft_putcstr(lst->passwd.pw_name, ' ', rabbit->pad.uid + 2, 'L');
			ft_putcstr(lst->group.gr_name, ' ', rabbit->pad.gid, 'L');
			if (rabbit->pad.c == '-' || rabbit->pad.c == 'd' || rabbit->pad.c == 'l')
				ft_putcstr(ft_st_itoa(lst->stat.st_size), ' ', rabbit->pad.size + 3, 'R');
			else
				ft_putmajmin(lst->stat);
			ft_printtime(lst, arg);
			ft_putcoldname(lst->data->d_name, lst->pad.c);
			lst = lst->next;
		}
	}
}
