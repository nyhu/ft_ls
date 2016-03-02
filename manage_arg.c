# include "libft.h"
# include "ft_ls.h"

void	ft_deldot(t_dirent **lst)
{
	t_dirent	*rabbit;
	t_dirent	*turtle;

	while (*lst && ((*lst)->data->d_name)[0] == '.')
	{
		rabbit = (*lst)->next;
		free(*lst);
		*lst = rabbit;
	}
	turtle = *lst;
	while (turtle)
	{
		rabbit = turtle->next;
		if (rabbit && rabbit->data->d_name[0] == '.')
		{
			turtle->next = rabbit->next;
			free(rabbit);
		}
		else
			turtle = turtle->next;
	}
}

void	ft_printperm(t_dirent *lst)
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
