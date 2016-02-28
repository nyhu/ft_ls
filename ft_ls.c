# include "libft.h"
# include "ft_ls.h"

static int		ft_lstdir(char *name, int arg, t_dirent *lst, int *end)
{
	DIR			dir;
	if ((dir = opendir(name)) < 0)
	{
		ft_error_manage("ft_ls", name);
		*end |= -dir;
	}
	else
	{
		lst = ft_create_direntlist(lst, dir);
		ft_runlist(lst, arg)
		ft_free_dirent_lst(lst);
		closedir(dir);
	}
}

int				ft_ls(char **av, int ac, int arg, int i)
{
	int			end;

	end = 0;
	if (i >= ac)
		ft_lstdir(".", arg, new, &end);
	else
		while (i < ac)
		{
			ft_lstdir(av[i], arg, NULL, &end);
			i++;
		}
	return ((end == 3 ? 2 : end));
}
