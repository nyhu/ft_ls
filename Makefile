# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboos <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/07 15:35:19 by tboos             #+#    #+#              #
#    Updated: 2016/03/07 15:37:08 by tboos            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
FLAGS = -Wall -Wextra -Werror
SRC = main.c manage_list.c manage_list_next.c ft_ls.c manage_arg.c

all: $(NAME)
lib:
	cd libft ; make ; cp libft.a ../.

$(NAME): lib
	gcc $(FLAGS) $(SRC) -I libft libft.a -o $(NAME)

clean:
	rm -f libft.a

fclean: clean
	rm -f $(NAME) 

re: fclean $(NAME)
.PHONY: fclean re
