/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 19:36:45 by tboos             #+#    #+#             */
/*   Updated: 2016/03/10 14:02:03 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

void			ft_normprint(t_dirent *lst)
{
	while (lst)
	{
		ft_putcoldname(lst->data->d_name, lst->pad.c);
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

static int		ft_print_only_one(t_dirent *lst, char *name, int arg)
{
	t_dirent	*kill;

	while (lst && ft_strcmp(lst->data->d_name, name))
	{
		kill = lst;
		lst = lst->next;
		free(kill);
	}
	if (lst)
	{
		ft_free_dirent_lst(lst->next);
		lst->next = NULL;
		ft_runlist(&lst, arg, name, 0);
		ft_free_dirent_lst(lst);
		return (1);
	}
	return (0);
}

int				ft_manage_file(char *name, int arg)
{
	t_dirent		*lst;
	DIR				*dir;
	int				i;
	static char		tmp[256];

	lst = NULL;
	if (!name || !(*name))
		return (0);
	ft_strcpy(tmp, name);
	i = ft_strlen(name);
	while (i--)
		if (tmp[i] == '/')
			break ;
	if (i >= 0 && tmp[i] == '/')
	{
		tmp[i] = '\0';
		if (!(dir = opendir(tmp)))
			return (0);
		ft_create_d_list(&lst, dir, tmp, arg);
	}
	else if (!(dir = opendir(".")))
		return (0);
	else
		ft_create_d_list(&lst, dir, ".", arg);
	return (ft_print_only_one(lst, name, arg));
}

void			ft_catlst(t_dirent *begin, t_dirent *rabbit)
{
	while (begin->next)
		begin = begin->next;
	begin->next = rabbit;
}
