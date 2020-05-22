# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 10:52:00 by vgrankul          #+#    #+#              #
#    Updated: 2020/02/27 16:08:26 by vgrankul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = ./ft_ls.c ./create_list.c ./filearr.c ./sort_list.c ./set_data.c ./helpfunctions.c ./sort_filearr.c ./print_files.c
OBJECTS = ./ft_ls.o ./create_list.o ./filearr.o ./sort_list.o ./set_data.o ./helpfunctions.o ./sort_filearr.o ./print_files.o
INC = ./

all: $(NAME)
	
$(NAME):
	make -C ./libft
	gcc -Wextra -Werror -Wall -I $(INC) $(SRC) -L libft/ -lft -o $(NAME) -ggdb3

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
