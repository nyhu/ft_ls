# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboos <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/07 15:35:19 by tboos             #+#    #+#              #
#    Updated: 2016/03/17 10:32:55 by tboos            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
DNAME = d_ft_ls
FLAGS = -Wall -Wextra -Werror
DFLAGS = -Wall -Wextra -Weverything
SRC = main.c manage_list.c manage_list_next.c ft_ls.c manage_arg.c \
	  manage_file.c ft_ls_spe.c attr_acl.c
OBJ = $(SRC:.c=.o)

all: lib $(NAME)

lib:
	cd libft ; make

%.o: %.c
	gcc $(FLAGS) -c $^ -I libft

$(NAME): $(OBJ)
	gcc $(FLAGS) $(OBJ) -I libft libft/libft.a -o $(NAME)

$(DNAME): $(OBJ) lib
	gcc $(DFLAGS) $(OBJ) -I libft libft/libft.a -o $(DNAME)

clean:
	rm -f $(OBJ)
	cd libft ; make clean

fclean: clean
	rm -f $(NAME)
	rm -f $(DNAME)
	cd libft ; make fclean

re: fclean lib $(NAME)
dre: fclean $(DNAME)
.PHONY: fclean re
