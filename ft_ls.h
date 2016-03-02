#ifndef FT_LS_H
# define FT_LS_H

#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <time.h>

# define MIN_A 1
# define MIN_L (1 < 1)
# define MAG_R (1 < 2)
# define MIN_R (1 < 3)
# define MIN_T (1 < 4)
# define MIN_U (1 < 5)
# define MIN_F (1 < 6)
# define MIN_G (1 < 7)
# define MIN_D (1 < 8)

typedef struct		s_dirent
{
	struct dirent   *data;
	struct s_dirent	*next;
	struct stat		stat;
}					t_dirent;

int			ft_ls(char **av, int ac, int arg, int i);

#endif
