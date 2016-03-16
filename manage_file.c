/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 19:36:45 by tboos             #+#    #+#             */
/*   Updated: 2016/03/16 14:58:58 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

static char	*ft_nbrchar(char *nbr, off_t n, int i)
{
	while (n)
	{
		nbr[i] = '0' + (n % 10);
		n = n / 10;
		i--;
	}
	return (nbr);
}

char		*ft_st_offttoa(off_t n)
{
	off_t		m;
	int			i;
	static char	nbr[36];

	i = -1;
	m = n;
	while (m)
	{
		m = m / 10;
		i++;
	}
	if (n == 0)
		i++;
	bzero(nbr, sizeof(nbr));
	if (!n)
		nbr[0] = '0';
	return (ft_nbrchar(nbr, n, i));
}

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
