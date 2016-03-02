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
# define MAG_A 1024
# define MIN_L 2
# define MAG_R 4
# define MIN_R 8
# define MIN_T 16
# define MIN_U 32
# define MIN_C 512
# define MIN_F 64
# define MIN_G 128
# define MIN_D 256
# define RABBIT_TIME_C rabbit->stat.st_atimespec.tv_sec
# define TURTLE_TIME_C turtle->stat.st_atimespec.tv_sec
# define RABBIT_TIME_M rabbit->stat.st_mtimespec.tv_sec
# define TURTLE_TIME_M turtle->stat.st_mtimespec.tv_sec
# define RABBIT_TIME_A rabbit->stat.st_atimespec.tv_sec
# define TURTLE_TIME_A turtle->stat.st_atimespec.tv_sec
# define S_IFMT 0170000           /* type of file */
# define S_IFIFO  0010000  /* named pipe (fifo) */
# define S_IFCHR  0020000  /* character special */
# define S_IFDIR  0040000  /* directory */
# define S_IFBLK  0060000  /* block special */
# define S_IFREG  0100000  /* regular */
# define S_IFLNK  0120000  /* symbolic link */
# define S_IFSOCK 0140000  /* socket */
# define S_IFWHT  0160000  /* whiteout */
# define S_ISUID 0004000  /* set user id on execution */
# define S_ISGID 0002000  /* set group id on execution */
# define S_ISVTX 0001000  /* save swapped text even after use */
# define S_IRUSR 0000400  /* read permission, owner */
# define S_IWUSR 0000200  /* write permission, owner */
# define S_IXUSR 0000100  /* execute/search permission, owner */

typedef struct		s_dirent
{
	struct dirent   *data;
	struct s_dirent	*next;
	struct stat		stat;
}					t_dirent;

t_dirent	*ft_listshunt(t_dirent *lst, int arg);
void		ft_printperm(t_dirent *lst);
void		ft_deldot(t_dirent **lst, int mode);
void		ft_printl(t_dirent *lst);
long		ft_cmpls(t_dirent *turtle, t_dirent *rabbit, int arg);
void		ft_swaplist(t_dirent *rabbit, t_dirent *turtle);
int			ft_create_direntlist(t_dirent **begin, DIR *dir, char *name);
void		ft_free_dirent_lst(t_dirent *lst);
void		ft_sortlst(t_dirent **begin, int arg);
void		ft_revlst(t_dirent **begin);
void		ft_lstdir(char *name, int arg, t_dirent *lst, int *end);
int			ft_ls(char **av, int ac, int arg, int i);

#endif
