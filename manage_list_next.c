# include "libft.h"
# include "ft_ls.h"

void	ft_swaplist(t_dirent **begin, t_dirent *stick, t_dirent *turtle)
{
	t_dirent	*rabbit;

	if (turtle != stick)
	{
		if (*begin == stick)
			*begin = turtle;
		else
		{
			rabbit = *begin;
			while (rabbit->next != stick)
				rabbit = rabbit->next;
			rabbit->next = turtle;
		}
		rabbit = stick;
		while (rabbit->next != turtle)
			rabbit = rabbit->next;
		rabbit->next = stick;
		rabbit = turtle->next;
		turtle->next = stick->next;
		stick->next = rabbit;
	}
}

static void	ft_printperm(t_dirent *lst)
{
	((lst->stat).st_mode & S_IRUSR ? ft_putchar('r') : ft_putchar('-'));
	((lst->stat).st_mode & S_IWUSR ? ft_putchar('w') : ft_putchar('-'));
	((lst->stat).st_mode & S_IXUSR ? ft_putchar('x') : ft_putchar('-'));
	((lst->stat).st_mode & S_IRGRP ? ft_putchar('r') : ft_putchar('-'));
	((lst->stat).st_mode & S_IWGRP ? ft_putchar('w') : ft_putchar('-'));
	((lst->stat).st_mode & S_IXGRP ? ft_putchar('x') : ft_putchar('-'));
	((lst->stat).st_mode & S_IROTH ? ft_putchar('r') : ft_putchar('-'));
	((lst->stat).st_mode & S_IWOTH ? ft_putchar('w') : ft_putchar('-'));
	((lst->stat).st_mode & S_IXOTH ? ft_putchar('x') : ft_putchar('-'));
}

static void	ft_printtime(t_dirent *lst)
{
	char	*tmp;
	int		i;

	if ((tmp = ctime(&(lst->stat.st_mtime))))
	{
		i = ft_strlen(tmp);
		tmp[i - 1] = '\0';
		ft_putstr(tmp);
	}
}

void		ft_printl(t_dirent *lst)
{
	ft_putstr("total ?\n");
	while (lst)
	{
		ft_putchar(lst->data->d_type);
		ft_printperm(lst);
		ft_putchar(' ');
		ft_putnbr((lst->stat).st_nlink);
		ft_putchar(' ');
		ft_putstr((getpwuid((lst->stat).st_uid))->pw_name);
		ft_putchar(' ');
		ft_putstr((getgrgid((lst->stat).st_gid))->gr_name);
		ft_putchar(' ');
		ft_putnbr(lst->data->d_reclen);
		ft_putchar(' ');
		ft_printtime(lst);
		ft_putchar(' ');
		ft_putstr(lst->data->d_name);
		lst = lst->next;
	}
}

int			ft_cmpls(t_dirent *turtle, t_dirent *rabbit, int arg)
{
	if (MIN_T & arg)
		return ((turtle->stat).st_mtime - (rabbit->stat).st_mtime);
	return (0);
}
