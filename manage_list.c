/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:10:11 by tboos             #+#    #+#             */
/*   Updated: 2016/03/03 13:31:38 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "ft_ls.h"
/*
void			ft_revlst(t_dirent **begin)
{
	t_dirent	*rabbit;
	t_dirent	*turtle;
	t_dirent	*memo;

	if (*begin && (*begin)->next)
	{
		memo = *begin;
		turtle = memo->next;
		rabbit = turtle->next;
		memo->next = NULL;
		while (turtle)
		{
			turtle->next = memo;
			memo = turtle;
			turtle = rabbit;
			if (rabbit)
				rabbit = rabbit->next;
		}
		*begin = memo;
	}
}

void			ft_sortlst(t_dirent **begin, int arg)
{
	t_dirent		*stick;
	t_dirent		*rabbit;

	*begin = ft_listshunt(*begin, arg);
	stick = *begin;
	while (stick->next != *begin)
	{
		rabbit = stick->next;
		while (rabbit->next != *begin)
		{
			if (ft_cmpls(rabbit->next, stick->next, arg) < 0)
			{
				ft_swaplist(stick, rabbit);
				rabbit = stick->next;
			}
			rabbit = rabbit->next;
		}
		stick = stick->next;
	}
	stick->next = NULL;
}
*/

void			ft_list_insert(t_dirent **begin, t_dirent *rabbit, int arg)
{
	t_dirent		*find;

	if (MIN_R_ARG && ft_cmpls(*begin, rabbit, arg) < 0)
	{
		rabbit->next = *begin;
		*begin = rabbit;
	}
	else if (!MIN_R_ARG && ft_cmpls(*begin, rabbit, arg) > 0)
	{
		rabbit->next = *begin;
		*begin = rabbit;
	}
	else
	{
		find = *begin;
		while (find->next && MIN_R_ARG && !(ft_cmpls(find->next, rabbit, arg) < 0))
			find = find->next;
		while (find->next && !MIN_R_ARG && !(ft_cmpls(find->next, rabbit, arg) > 0))
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

static t_dirent	*ft_create_direntelem(struct dirent *new, char *name)
{
	t_dirent		*next;
	char			*tmp;
	char			*the_name;

	if (!(next = (t_dirent *)malloc(sizeof(t_dirent))))
		return (NULL);
	next->data = new;
	tmp = ft_strjoin(name, "/");
	the_name = ft_strjoin(tmp, new->d_name);
	free(tmp);
	if (stat(the_name, &(next->stat)) < 0 && ft_freegiveone(next))
		return (NULL);
	free(the_name);
	next->next = NULL;
	return (next);
}

int				ft_create_d_list(t_dirent **begin, DIR *dir, char *name, int arg)
{
	struct dirent	*new;
	t_dirent		*rabbit;

	if (!(new = readdir(dir)))
		return (0);
	if (!(new = (struct dirent *)DIRENT_MEMDUP))
		return (1);
	if ((!begin || !(*begin = ft_create_direntelem(new, name))) && FREE1(new))
		return (1);
	while ((new = readdir(dir)))
	{
		if (!(new = (struct dirent *)DIRENT_MEMDUP))
			return (1);
		if (!(rabbit = ft_create_direntelem(new, name)) && FREE1(new))
			return (1);
		ft_list_insert(begin, rabbit, arg);
	}
	return (0);
}
