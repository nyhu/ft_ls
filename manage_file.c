/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 19:36:45 by tboos             #+#    #+#             */
/*   Updated: 2016/03/10 19:32:46 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

void			ft_normprint(t_dirent *lst)
{
	while (lst)
	{
		ft_putcoldname(lst);
		lst = lst->next;
	}
}

time_t			ft_returntime(t_dirent *lst, int arg)
{
	if (arg & MIN_U)
		return (lst->stat.st_atimespec.tv_sec);
	if (arg & MAG_U)
		return (lst->stat.st_birthtimespec.tv_sec);
	if (arg & MIN_C)
		return (lst->stat.st_ctimespec.tv_sec);
	return (lst->stat.st_mtimespec.tv_sec);
}

static void		ft_print_only_one(t_dirent *lst, char *name, int arg, int *end)
{
	t_dirent	*kill;

	while (lst && ft_strcmp(lst->data->d_name, name))
	{
		kill = lst;
		lst = lst->next;
		kill->next = NULL;
		ft_free_dirent_lst(kill);
	}
	if (lst)
	{
		ft_free_dirent_lst(lst->next);
		lst->next = NULL;
		if (lst->pad.c == 'd')
			ft_lstdir(name, arg, NULL, 0);
		else
			ft_runlist(&lst, arg, name, 0);
		ft_free_dirent_lst(lst);
		*end = 1;
	}
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	*end = 1;
}

int				ft_manage_file(char *name, int arg, int *end)
{
	t_dirent		*lst;
	DIR				*dir;
	char			*tmp;

	lst = NULL;
	if (!name || !(*name))
	{
		tmp = ft_strjoin("ft_ls: ", "fts_open");
		perror(tmp);
		free(tmp);
		*end |= 1;
		return (1);
	}
	else if (!(dir = opendir(".")))
		*end = 1;
	else
	{
		ft_create_d_list(&lst, dir, ".", arg);
		ft_print_only_one(lst, name, arg, end);
		return (1);
	}
	return (0);
}

void			ft_catlst(t_dirent *begin, t_dirent *rabbit)
{
	while (begin->next)
		begin = begin->next;
	begin->next = rabbit;
}
