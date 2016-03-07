/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:10:49 by tboos             #+#    #+#             */
/*   Updated: 2016/03/07 15:56:59 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "ft_ls.h"

static void		ft_print(t_dirent *lst, int arg)
{
	t_dirent		*rabbit;
	struct winsize	w;
	size_t			nb_col;
	size_t			jump;

	if (MIN_L & arg)
		ft_printl(lst);
	else
	{
		nb_col = 1;
		jump = 0;
		rabbit = lst;
		while (rabbit)
		{
			if (nb_col < ft_strlen(rabbit->data->d_name))
				nb_col = ft_strlen(rabbit->data->d_name);
			rabbit = rabbit->next;
			jump++;
		}
		ioctl(0, TIOCGWINSZ, &w);
		nb_col = w.ws_col / nb_col;
		ft_printcol(lst, (nb_col ? nb_col : 1), w.ws_col, jump);
	}
}

static void		ft_recurlist(t_dirent *lst, int arg, char *name, int *end)
{
	char		*the_name;

	while (lst)
	{
		if (S_ISDIR(lst->stat.st_mode))
		{
			if (!(the_name = ft_strslashjoin(name, lst->data->d_name)))
			{
				perror("ft_ls: error");
				*end |= 1;
				return ;
			}
			else if (strlen(the_name) < 256)
			{
				ft_putstr_str_str_fd("\n", the_name, ":\n", 2);
				ft_lstdir(the_name, arg, NULL, end);
			}
			else
				ft_putstr_str_str_fd("ft_ls: ", the_name, ": File name too long", 2);
			free(the_name);
		}
		lst = lst->next;
	}
}

static void		ft_runlist(t_dirent **lst, int arg, char *name, int *end)
{
	if (!(MIN_A & arg) && !(MAG_A & arg))
		ft_deldot(lst, 0);
	else if (MAG_A & arg)
		ft_deldot(lst, 1);
	ft_print(*lst, arg);
	if (MAG_R & arg)
	{
		if (MIN_A & arg)
			ft_deldot(lst, 1);
		ft_recurlist(*lst, arg, name, end);
	}
}

void			ft_lstdir(char *name, int arg, t_dirent *lst, int *end)
{
	DIR			*dir;
	char		*tmp;

	dir = NULL;
	if (!(dir = opendir(name)))
	{
		if (!name || !(*name))
			tmp = ft_strjoin("ft_ls: ", "fts_open");
		else
			tmp = ft_strjoin("ft_ls: ", name);
		perror(tmp);
		free(tmp);
		*end |= 1;
	}
	else
	{
		*end |= ft_create_d_list(&lst, dir, name, arg);
		if (lst)
		{
			ft_runlist(&lst, arg, name, end);
			ft_free_dirent_lst(lst);
		}
		closedir(dir);
	}
}

int				ft_ls(char **av, int ac, int arg, int i)
{
	int			end;

	end = 0;
	if (i >= ac)
		ft_lstdir(".", arg, NULL, &end);
	else
		while (i < ac)
		{
			if (strlen(av[i]) < 256)
				ft_lstdir(av[i], arg, NULL, &end);
			else
			{
				ft_putstr_str_str_fd("ft_ls: ", av[i],
				": File name too long", 2);
			}
			i++;
		}
	return ((end == 3 ? 2 : end));
}
