/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_spe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 03:17:22 by tboos             #+#    #+#             */
/*   Updated: 2016/03/17 10:08:55 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_dirent	*ft_createerror(char *tmp, t_dirent *next)
{
	perror(tmp);
	free(tmp);
	free(next->data);
	free(next);
	return (NULL);
}

static t_dirent	*ft_create_felem(struct dirent *new, char *name, int arg)
{
	t_dirent		*next;
	char			*tmp;

	if (!(tmp = ft_strjoin("ls: ", name)))
		return (NULL);
	if (!(next = (t_dirent *)ft_memalloc(sizeof(t_dirent)))
		&& ft_freegiveone(tmp))
		return (NULL);
	if (!(next->data = (struct dirent *)DIRENT_MEMDUP)
		&& ft_freegiveone(tmp) && ft_freegiveone(next))
		return (NULL);
	if ((MAG_H & arg) && stat(name, &(next->stat)) < 0)
		return (ft_createerror(tmp, next));
	if (!(MAG_H & arg) && lstat(name, &(next->stat)) < 0)
		return (ft_createerror(tmp, next));
	ft_memcpy(&next->passwd, getpwuid(next->stat.st_uid), sizeof(t_passwd));
	ft_memcpy(&next->group, getgrgid(next->stat.st_gid), sizeof(t_group));
	next->pad.c = ft_returntype(next->stat.st_mode);
	if (arg & MIN_L && next->pad.c == 'l'
		&& readlink(name, next->link, 255) <= 0)
		perror(next->data->d_name);
	free(new);
	free(tmp);
	return (next);
}

static int		ft_manage_fil_dir(char *name, t_dirent **files, int arg)
{
	t_dirent	*rabbit;
	t_direntori	*new;

	if (!(new = (t_direntori *)ft_memalloc(sizeof(t_direntori))))
		return (1);
	ft_strcpy(new->d_name, name);
	if (!(rabbit = ft_create_felem(new, name, arg)) && ft_freegiveone(new))
		return (1);
	if ((MIN_F & arg) && *files)
		ft_catlst(*files, rabbit);
	else if (*files)
		ft_list_insert(files, rabbit, arg);
	else
		*files = rabbit;
	return (0);
}

static int		ft_dispatch(t_dirent **files, t_dirent **dirs,
				char *name, int arg)
{
	t_stat		tmp;
	char		*error;

	bzero(&tmp, sizeof(t_stat));
	if (!(*name))
	{
		ft_putstr_fd("ls: fts_open: No such file or directory\n", 2);
		return (1);
	}
	else if (ft_strlen(name) > 255)
	{
		ft_putstr_str_str_fd("ls: ", name, ": File name too long\n", 2);
		return (1);
	}
	else if (-1 == lstat(name, &tmp))
	{
		error = ft_strjoin("ls: ", name);
		perror(error);
		free(error);
		return (1);
	}
	else if (S_ISDIR(tmp.st_mode))
		return (ft_manage_fil_dir(name, dirs, arg));
	return (ft_manage_fil_dir(name, files, arg));
}

int				ft_lstspe(char **av, int ac, int arg, int i)
{
	int			end;
	t_dirent	*files;
	t_dirent	*dirs;

	files = NULL;
	dirs = NULL;
	end = 0;
	while (i++ < ac)
		end |= ft_dispatch(&files, &dirs, av[i - 1], arg);
	if (!files && arg & MULTI)
		arg |= FIRST;
	if (files)
		ft_print(files, arg);
	ft_free_dirent_lst(files);
	ft_print_dir(dirs, arg, &end);
	ft_free_dirent_lst(dirs);
	return (end);
}
