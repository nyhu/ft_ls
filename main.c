/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 20:52:38 by tboos             #+#    #+#             */
/*   Updated: 2016/03/10 13:54:33 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

static void	ft_timesort(char c, int *arg)
{
	if (c == 't')
		*arg |= MIN_T;
	if (c == 'U' && (*arg |= MAG_U))
	{
		if (*arg & MIN_U)
			*arg -= MIN_U;
		if (*arg & MIN_C)
			*arg -= MIN_C;
	}
	if (c == 'c' && (*arg |= MIN_C))
	{
		if (*arg & MIN_U)
			*arg -= MIN_U;
		if (*arg & MAG_U)
			*arg -= MAG_U;
	}
	if (c == 'u' && (*arg |= MIN_U))
	{
		if (*arg & MIN_C)
			*arg -= MIN_C;
		if (*arg & MAG_U)
			*arg -= MAG_U;
	}
}

static void	ft_format(char c, int *arg)
{
	if (c == '1' && (*arg |= NUM_O))
	{
		if (*arg & MIN_L)
			*arg -= MIN_L;
		if (*arg & MAG_C)
			*arg -= MAG_C;
	}
	if (c == 'l' && (*arg |= MIN_L))
	{
		if (*arg & NUM_O)
			*arg -= NUM_O;
		if (*arg & MAG_C)
			*arg -= MAG_C;
	}
	if (c == 'C' && (*arg |= MAG_C))
	{
		if (*arg & MIN_L)
			*arg -= MIN_L;
		if (*arg & NUM_O)
			*arg -= NUM_O;
	}
	if (c == 'y')
		*arg |= MIN_Y;
	if (c == 'H')
		*arg |= MAG_H;
}

static int	ft_matcharg(char *str, int *arg)
{
	if (*(++str) && *str == '-')
		return (0);
	while (*str)
	{
		ft_format(*str, arg);
		ft_timesort(*str, arg);
		if (*str == 'a')
			*arg |= MIN_A;
		if (*str == 'A')
			*arg |= MAG_A;
		if (*str == 'R')
			*arg |= MAG_R;
		if (*str == 'r')
			*arg |= MIN_R;
		if (*str == 'f')
			*arg |= MIN_F;
		if (*str == 'o')
			*arg |= MIN_O;
		str++;
	}
	return (1);
}

int			main(int ac, char **av)
{
	int		arg;
	int		i;

	arg = 0;
	i = 1;
	while (ac > 1 && i < ac && av[i][0] == '-')
		if (!(ft_matcharg(av[i++], &arg)))
			break ;
	if (!(MIN_Y & arg) && (MAG_H & arg) && (MIN_L & arg))
		arg -= MAG_H;
	return (ft_ls(av, ac, arg, i));
}
