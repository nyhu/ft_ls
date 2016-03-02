#include "libft.h"
#include "ft_ls.h"

static void	ft_timesort(char c, int *arg)
{
		if (c == 'c')
		{
			*arg += MIN_C;
			if (*arg & MIN_T)
				*arg -= MIN_T;
			else if (*arg & MIN_U)
				*arg -= MIN_U;
		}
		if (c == 't')
		{
			*arg += MIN_T;
			if (*arg & MIN_C)
				*arg -= MIN_C;
			else if (*arg & MIN_U)
				*arg -= MIN_U;
		}
		if (c == 'u')
		{
			*arg += MIN_U;
			if (*arg & MIN_T)
				*arg -= MIN_T;
			else if (*arg & MIN_C)
				*arg -= MIN_C;
		}
}

static int	ft_matcharg(char *str, int *arg)
{
	if (*(++str) && *str == '-')
		return (0);
	while (*str)
	{
		ft_timesort(*str, arg);
		if (*str == 'a')
			*arg += MIN_A;
		if (*str == 'A')
			*arg += MAG_A;
		if (*str == 'l')
			*arg += MIN_L;
		if (*str == 'R')
			*arg += MAG_R;
		if (*str == 'r')
			*arg += MIN_R;
		if (*str == 'f')
			*arg += MIN_F;
		if (*str == 'g')
			*arg += MIN_G;
		if (*str == 'd')
			*arg += MIN_D;
		str++;
	}
	return (1);
}

int			main(int  ac, char **av)
{
	int		arg;
	int		i;

	arg = 0;
	i = 1;
	while (ac > 1 && i < ac && av[i][0] == '-')
		if (!(ft_matcharg(av[i++], &arg)))
			break ;
	return (ft_ls(av, ac, arg, i));
}
