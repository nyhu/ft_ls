/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 03:10:59 by tboos             #+#    #+#             */
/*   Updated: 2016/03/06 08:29:28 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "ft_ls.h"

void		ft_putmajmin(struct stat stat)
{
	int			major;
	int			minor;

	major = (stat.st_rdev >> 24) & 0xff;
	minor = (stat.st_rdev) & 0xffffff;
	ft_putchar(' ');
	ft_putcstr(ft_itoa(major), ' ', 2, 'R');
	ft_putstr(",");
	ft_putcstr(ft_itoa(minor), ' ', 4, 'R');
}

void		ft_printcol(t_dirent *lst, size_t nb_col, size_t ldisp, size_t jump)
{
	char		*tab;
	size_t		i;

	tab = (char *)ft_memalloc(sizeof(char) * (ldisp * (jump / nb_col + 1) + 1));
	ft_memset(tab, ' ', ldisp * (jump / nb_col + 1));
	i = 0;
	while (lst)
	{
		ft_memmove(tab + i, lst->data->d_name, ft_strlen(lst->data->d_name));
		lst = lst->next;
		i = i + ldisp;
		if (i >= ldisp * (jump / nb_col + 1))
			i = i - (ldisp * (jump / nb_col + 1)) + ldisp / nb_col;
	}
	ft_putendl(tab);
	free(tab);
}

static int	ft_todelete(const char *str, int mag_a)
{
	if (str[0] == '.')
	{
		if (!mag_a)
			return (1);
		if (!(str[1]))
			return (1);
		if (str[1] == '.' && !(str[2]))
			return (1);
	}
	return (0);
}

void		ft_deldot(t_dirent **lst, int mag_a)
{
	t_dirent	*rabbit;
	t_dirent	*turtle;

	while (*lst && ft_todelete((*lst)->data->d_name, mag_a))
	{
		rabbit = (*lst)->next;
		free(*lst);
		*lst = rabbit;
	}
	turtle = *lst;
	while (turtle)
	{
		rabbit = turtle->next;
		if (rabbit && ft_todelete(rabbit->data->d_name, mag_a))
		{
			turtle->next = rabbit->next;
			free(rabbit);
		}
		else
			turtle = turtle->next;
	}
}

void		ft_printperm(t_dirent *lst)
{
	(lst->stat.st_mode & S_IRUSR ? ft_putchar('r') : ft_putchar('-'));
	(lst->stat.st_mode & S_IWUSR ? ft_putchar('w') : ft_putchar('-'));
	(lst->stat.st_mode & S_IXUSR ? ft_putchar('x') : ft_putchar('-'));
	(lst->stat.st_mode & S_IRGRP ? ft_putchar('r') : ft_putchar('-'));
	(lst->stat.st_mode & S_IWGRP ? ft_putchar('w') : ft_putchar('-'));
	(lst->stat.st_mode & S_IXGRP ? ft_putchar('x') : ft_putchar('-'));
	(lst->stat.st_mode & S_IROTH ? ft_putchar('r') : ft_putchar('-'));
	(lst->stat.st_mode & S_IWOTH ? ft_putchar('w') : ft_putchar('-'));
	(lst->stat.st_mode & S_IXOTH ? ft_putchar('x') : ft_putchar('-'));
}
