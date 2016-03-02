# include "libft.h"
# include "ft_ls.h"

static void		ft_print(t_dirent *lst, int arg)
{
	if (MIN_L & arg)
		ft_printl(lst, arg);
	else
		while (lst)
		{
			ft_putendl(lst->data->d_name);
			lst = lst->next;
		}
}

static void		ft_recurlist(t_dirent *lst, int arg, char *name, int *end)
{
	char	tmp;
	char	*the_name;

	while (lst)
	{
		if ((lst->data).d_type == DT_DIR)
		{
			tmp = ft_strjoin(name, "/");
			the_name = ft_strjoin(tmp, (lst->data).d_name);
			free(tmp);
			ft_lstdir(the_name, arg, NULL, end);
			free(the_name);
		}
		lst = lst->next;
	}
}

static void		ft_runlist(t_dirent *lst, int arg, char *name, int *end)
{
	if (MIN_T & arg)
		ft_sortlst(&lst, arg, name);
	if (MIN_R & arg)
		ft_revlst(&lst);
	if (MAG_R & arg)
	{
		ft_putstr(name);
		ft_putstr(":\n");
	}
	ft_print(lst, arg);
	if (MAG_R & arg)
		ft_recurlist(lst, arg, name, end);
}

static int		ft_lstdir(char *name, int arg, t_dirent *lst, int *end)
{
	DIR			dir;

	if ((dir = opendir(name)) < 0)
	{
		ft_putstr_fd("ft_ls : ");
		ft_putstr_fd(name);
		ft_putstr_fd(" : ");
		perror(strerror(errno));
		*end |= -dir;
	}
	else
	{
		*end |= ft_create_direntlist(&lst, dir, name);
		ft_runlist(lst, arg, name, end);
		ft_free_dirent_lst(lst);
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
			ft_lstdir(av[i], arg, NULL, &end);
			i++;
		}
	return ((end == 3 ? 2 : end));
}
