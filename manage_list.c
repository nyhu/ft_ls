/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:10:11 by tboos             #+#    #+#             */
/*   Updated: 2016/03/10 14:05:07 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

long			ft_cmpls(t_dirent *turtle, t_dirent *rabbit, int arg)
{
	if ((MIN_T & arg) && (MIN_C & arg))
		return (RABBIT_TIME_A - TURTLE_TIME_A);
	if ((MIN_T & arg) && (MIN_U & arg))
		return (RABBIT_TIME_C - TURTLE_TIME_C);
	if ((MIN_T & arg) && (MAG_U & arg))
		return (RABBIT_TIME_B - TURTLE_TIME_B);
	if ((MIN_T & arg))
		return (RABBIT_TIME_M - TURTLE_TIME_M);
	return (ft_strcmp(turtle->data->d_name, rabbit->data->d_name));
}

void			ft_list_insert(t_dirent **begin, t_dirent *rabbit, int arg)
{
	t_dirent		*find;

	if ((MIN_R & arg) && ft_cmpls(*begin, rabbit, arg) < 0)
	{
		rabbit->next = *begin;
		*begin = rabbit;
	}
	else if (!(MIN_R & arg) && ft_cmpls(*begin, rabbit, arg) > 0)
	{
		rabbit->next = *begin;
		*begin = rabbit;
	}
	else
	{
		find = *begin;
		while (find->next && (MIN_R & arg) && !CMP_ELEM < 0)
			find = find->next;
		while (find->next && !(MIN_R & arg) && !CMP_ELEM > 0)
			find = find->next;
		rabbit->next = find->next;
		find->next = rabbit;
	}
}

void			ft_free_dirent_lst(t_dirent *lst)
{
	t_dirent		*kill;

	while (lst)
	{
		kill = lst;
		lst = lst->next;
		free(kill->data);
		free(kill);
	}
}

static t_dirent	*ft_create_direntelem(struct dirent *new, char *name, int arg)
{
	t_dirent		*next;
	char			*tmp;
	char			*the_name;

	if (!(next = (t_dirent *)ft_memalloc(sizeof(t_dirent))))
		return (NULL);
	next->data = new;
	tmp = ft_strjoin(name, "/");
	the_name = ft_strjoin(tmp, new->d_name);
	free(tmp);
	if ((MAG_H & arg) && stat(the_name, &(next->stat)) < 0
		&& ft_freegiveone(next))
		return (NULL);
	if (!(MAG_H & arg) && lstat(the_name, &(next->stat)) < 0
		&& ft_freegiveone(next))
		return (NULL);
	free(the_name);
	ft_memcpy(&next->passwd, getpwuid(next->stat.st_uid), sizeof(t_passwd));
	ft_memcpy(&next->group, getgrgid(next->stat.st_gid), sizeof(t_group));
	next->pad.c = ft_returntype(next->stat.st_mode);
	next->next = NULL;
	return (next);
}

int				ft_create_d_list(t_dirent **begin, DIR *dir,
				char *name, int arg)
{
	struct dirent	*new;
	t_dirent		*rabbit;

	if (!(new = readdir(dir)))
		return (0);
	if (!(new = (struct dirent *)DIRENT_MEMDUP))
		return (1);
	if ((!begin || !(*begin = ft_create_direntelem(new, name, arg)))
		&& FREE1(new))
		return (1);
	while ((new = readdir(dir)))
	{
		if (!(new = (struct dirent *)DIRENT_MEMDUP))
			return (1);
		if (!(rabbit = ft_create_direntelem(new, name, arg)) && FREE1(new))
			return (1);
		if ((MIN_F & arg))
			ft_catlst(*begin, rabbit);
		else
			ft_list_insert(begin, rabbit, arg);
	}
	return (0);
}
