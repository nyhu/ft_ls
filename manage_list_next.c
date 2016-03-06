/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list_next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:10:42 by tboos             #+#    #+#             */
/*   Updated: 2016/03/06 12:02:49 by tboos            ###   ########.fr       */
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
	t_dirent	rabbit;

	bzero(&tmp, sizeof(t_lpadding));
	while (lst)
	{
		pad->total += lst->stat.st_blocks;
		if (lst->stat.st_nlink > tmp.nlink)
			tmp.nlink = lst->stat.st_nlink;
		if (tmp.uid < (memo = ft_strlen((getpwuid(lst->stat.st_uid))->pw_name)))
			tmp.uid = memo;
		if (tmp.gid < (memo = ft_strlen((getgrgid(lst->stat.st_gid))->gr_name)))
			tmp.gid = memo;
		if (tmp.size < lst->stat.st_size)
			tmp.size = lst->stat.st_size;
		lst = lst->next;
	}
	while ((tmp.nlink /= 10))
		(pad->nlink)++;
	while ((tmp.uid /= 10))
		(pad->uid)++;
	while ((tmp.gid /= 10))
		(pad->gid)++;
	while ((tmp.size /= 10))
		(pad->size)++;
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
	t_lpadding	pad;

	bzero(&pad, sizeof(t_lpadding));
	pad.c = ft_puttype(lst->stat.st_mode);
	ft_findpad(lst, &pad);
	ft_putstr_nbr_str("total ", pad.total, "\n");
	while (lst)
	{
		ft_putchar(pad.c);
		ft_printperm(lst);
		ft_putcstr(ft_itoa(lst->stat.st_nlink), ' ', pad.nlink + 1, 'R');
		ft_putchar(' ');
		ft_putcstr((getpwuid(lst->stat.st_uid))->pw_name, ' ', pad.uid + 3, 'L');
		ft_putcstr((getgrgid(lst->stat.st_gid))->gr_name, ' ', pad.gid + 1, 'L');
		if (pad.c == '-' || pad.c == 'd' || pad.c == 'l')
			ft_putcstr(ft_itoa(lst->stat.st_size), ' ', pad.size + 1, 'R');
		else
			ft_putmajmin(lst->stat);
		ft_printtime(lst);
		ft_putendl(lst->data->d_name);
		lst = lst->next;
	}
}
