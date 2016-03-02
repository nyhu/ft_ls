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
