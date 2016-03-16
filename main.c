/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 20:52:38 by tboos             #+#    #+#             */
/*   Updated: 2016/03/16 02:16:20 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

static void	ft_error_usage(char c)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: ls [-ACHRUacflrtuy1] [file ...]\n", 2);
	exit(1);
}

static int	ft_timesort(char c, int *arg)
{
	if (c == 'U' && (*arg |= MAG_U))
	{
		if (*arg & MIN_U)
			*arg -= MIN_U;
		if (*arg & MIN_C)
			*arg -= MIN_C;
	}
	else if (c == 'c' && (*arg |= MIN_C))
	{
		if (*arg & MIN_U)
			*arg -= MIN_U;
		if (*arg & MAG_U)
			*arg -= MAG_U;
	}
	else if (c == 'u' && (*arg |= MIN_U))
	{
		if (*arg & MIN_C)
			*arg -= MIN_C;
		if (*arg & MAG_U)
			*arg -= MAG_U;
	}
	else
		return (0);
	return (1);
}

static int	ft_format(char c, int *arg)
{
	if (c == '1' && (*arg |= NUM_O))
	{
		if (*arg & MIN_L)
			*arg -= MIN_L;
		if (*arg & MAG_C)
			*arg -= MAG_C;
	}
	else if (c == 'l' && (*arg |= MIN_L))
	{
		if (*arg & NUM_O)
			*arg -= NUM_O;
		if (*arg & MAG_C)
			*arg -= MAG_C;
	}
	else if (c == 'C' && (*arg |= MAG_C))
	{
		if (*arg & MIN_L)
			*arg -= MIN_L;
		if (*arg & NUM_O)
			*arg -= NUM_O;
	}
	else
		return (0);
	return (1);
}

static int	ft_matcharg(char *str, int *arg)
{
	if (*(++str) && *str == '-')
		return (0);
	while (*str)
	{
		if (*str == 'a')
			*arg |= MIN_A;
		else if (*str == 'A')
			*arg |= MAG_A;
		else if (*str == 'R')
			*arg |= MAG_R;
		else if (*str == 'r')
			*arg |= MIN_R;
		else if (*str == 't')
			*arg |= MIN_T;
		else if (*str == 'f')
			*arg |= MIN_F;
		else if (*str == 'y')
			*arg |= MIN_Y;
		else if (*str == 'H')
			*arg |= MAG_H;
		else if (!ft_format(*str, arg) && !ft_timesort(*str, arg))
			ft_error_usage(*str);
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
