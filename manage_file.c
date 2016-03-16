/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 19:36:45 by tboos             #+#    #+#             */
/*   Updated: 2016/03/16 07:27:33 by tboos            ###   ########.fr       */
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

void			ft_catlst(t_dirent *begin, t_dirent *rabbit)
{
	while (begin->next)
		begin = begin->next;
	begin->next = rabbit;
}
