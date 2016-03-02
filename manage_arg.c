# include "libft.h"
# include "ft_ls.h"

static int	ft_todelete(const char *str, int mag_a)
{
	if (str[0] == '.')
	{
		if (!mag_a)
			return (1);
		if (!(str[1]))
			return (1);
		if (str[1] == '.' && !(str[2]))
			return (1);
	}
	return (0);
}

void		ft_deldot(t_dirent **lst, int mag_a)
{
	t_dirent	*rabbit;
	t_dirent	*turtle;

	while (*lst && ft_todelete((*lst)->data->d_name, mag_a))
	{
		rabbit = (*lst)->next;
		free(*lst);
		*lst = rabbit;
	}
	turtle = *lst;
	while (turtle)
	{
		rabbit = turtle->next;
		if (rabbit && ft_todelete(rabbit->data->d_name, mag_a))
		{
			turtle->next = rabbit->next;
			free(rabbit);
		}
		else
			turtle = turtle->next;
	}
}

void		ft_printperm(t_dirent *lst)
{
	(lst->stat.st_mode & S_IRUSR ? ft_putchar('r') : ft_putchar('-'));
	(lst->stat.st_mode & S_IWUSR ? ft_putchar('w') : ft_putchar('-'));
	(lst->stat.st_mode & S_IXUSR ? ft_putchar('x') : ft_putchar('-'));
	(lst->stat.st_mode & S_IRGRP ? ft_putchar('r') : ft_putchar('-'));
	(lst->stat.st_mode & S_IWGRP ? ft_putchar('w') : ft_putchar('-'));
	(lst->stat.st_mode & S_IXGRP ? ft_putchar('x') : ft_putchar('-'));
	(lst->stat.st_mode & S_IROTH ? ft_putchar('r') : ft_putchar('-'));
	(lst->stat.st_mode & S_IWOTH ? ft_putchar('w') : ft_putchar('-'));
	(lst->stat.st_mode & S_IXOTH ? ft_putchar('x') : ft_putchar('-'));
}
