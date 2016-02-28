# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2015/11/04 18:24:51 by tboos             #+#    #+#             #
#   Updated: 2015/11/05 00:11:36 by tboos            ###   ########.fr       #
#                                                                            #
# ************************************************************************** #
NAME = ft_ls
FLAGS = -Wall -Wextra -Werror
S =

all: $(NAME)

lib:
	cd libft ; make ; cp libft.a ../.

$(NAME): lib
	gcc $(FLAGS) $(SRC) -I includes libft.a -o $(NAME)

clean:
	rm -f libft.a

fclean: clean
	rm -f $(NAME) 

re: fclean $(NAME)

.PHONY: clean fclean re 
