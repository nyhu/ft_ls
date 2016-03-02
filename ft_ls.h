#ifndef FT_LS_H
# define FT_LS_H

#include <grp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <time.h>
#include <stdio.h>

# define MIN_A 1
# define MIN_L 2
# define MAG_R 4
# define MIN_R 8
# define MIN_T 16
# define MIN_U 32
# define MIN_F 64
# define MIN_G 128
# define MIN_D 256
# define MAG_U 512

typedef struct		s_dirent
{
	struct dirent   *data;
	struct s_dirent	*next;
	struct stat		stat;
}					t_dirent;

t_dirent	*ft_listshunt(t_dirent *lst, int arg);
void		ft_printperm(t_dirent *lst);
void		ft_deldot(t_dirent **lst);
void		ft_printl(t_dirent *lst);
int			ft_cmpls(t_dirent *turtle, t_dirent *rabbit, int arg);
void		ft_swaplist(t_dirent *rabbit, t_dirent *turtle);
int			ft_create_direntlist(t_dirent **begin, DIR *dir, char *name);
void		ft_free_dirent_lst(t_dirent *lst);
void		ft_sortlst(t_dirent **begin, int arg);
void		ft_revlst(t_dirent **begin);
void		ft_lstdir(char *name, int arg, t_dirent *lst, int *end);
int			ft_ls(char **av, int ac, int arg, int i);

#endif
