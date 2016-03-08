/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:10:56 by tboos             #+#    #+#             */
/*   Updated: 2016/03/08 20:33:40 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <grp.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <pwd.h>
# include <time.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/time.h>

# define MIN_A 0000001
# define MAG_A 0000002
# define MIN_L 0000004
# define MAG_R 0000010
# define MIN_R 0000020
# define MIN_T 0000040
# define MIN_U 0000100
# define MIN_C 0000200
# define MIN_F 0000400
# define MIN_O 0001000
# define MAG_H 0002000
# define NUM_O 0004000
# define MAG_C 0010000
# define MAG_U 0020000
# define MIN_Y 0040000
# define RABBIT_TIME_B rabbit->stat.st_birthtimespec.tv_sec
# define TURTLE_TIME_B turtle->stat.st_birthtimespec.tv_sec
# define RABBIT_TIME_C rabbit->stat.st_atimespec.tv_sec
# define TURTLE_TIME_C turtle->stat.st_atimespec.tv_sec
# define RABBIT_TIME_M rabbit->stat.st_mtimespec.tv_sec
# define TURTLE_TIME_M turtle->stat.st_mtimespec.tv_sec
# define RABBIT_TIME_A rabbit->stat.st_ctimespec.tv_sec
# define TURTLE_TIME_A turtle->stat.st_ctimespec.tv_sec
# define SIX_MONTH_IN_SEC 15552000
# define CMP_6MONTH ((timeval.tv_sec - time) > SIX_MONTH_IN_SEC)
# define D_SIZE sizeof(struct dirent)
# define DIRENT_MEMDUP (ft_memcpy(ft_memalloc(D_SIZE), new, D_SIZE))
# define FREE1 ft_freegiveone
# define MIN_R_ARG (MIN_R & arg)

typedef struct dirent	t_direntori;
typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;
typedef struct timeval	t_timeval;
typedef struct			s_lpadding
{
	char				c;
	int					total;
	int					nlink;
	int					uid;
	int					gid;
	int					size;
}						t_lpadding;
typedef struct			s_dirent
{
	t_direntori			*data;
	t_stat				stat;
	t_lpadding			pad;
	t_passwd			passwd;
	t_group				group;
	struct s_dirent		*next;
}						t_dirent;

void			ft_catlst(t_dirent *begin, t_dirent *rabbit);
void					ft_normprint(t_dirent *lst);
time_t					ft_returntime(t_dirent *lst, int arg);
void					ft_runlist(t_dirent **lst, int arg, char *name, int *end);
int						ft_manage_file(char *name, int arg);
char					ft_returntype(mode_t st_mode);
void					ft_putcoldname(char *d_name, char c);
void					ft_putmajmin(t_stat stat);
void					ft_printcol(t_dirent *lst, size_t nb_col, size_t ldisp,
						size_t jump);
void					ft_printperm(t_dirent *lst);
void					ft_deldot(t_dirent **lst, int mode);
void					ft_printl(t_dirent *lst, int arg);
long					ft_cmpls(t_dirent *turtle, t_dirent *rabbit, int arg);
int						ft_create_d_list(t_dirent **begin, DIR *dir,
						char *name, int arg);
void					ft_free_dirent_lst(t_dirent *lst);
void					ft_revlst(t_dirent **begin);
void					ft_lstdir(char *name, int arg, t_dirent *lst, int *end);
int						ft_ls(char **av, int ac, int arg, int i);
void					ft_list_insert(t_dirent **begin, t_dirent *rabbit,
						int arg);

#endif
