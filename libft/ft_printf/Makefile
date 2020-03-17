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

NAME = libftprintf.a
SRC = ./libft/ft_putchar.c ./libft/ft_putstr.c ./libft/ft_strlen.c ./libft/ft_strcpy.c ./libft/ft_strcmp.c ./libft/ft_strdup.c ./libft/ft_strncmp.c ./libft/ft_strncpy.c ./libft/ft_strcat.c ./libft/ft_strncat.c ./libft/ft_putnbr.c ./libft/ft_atoi.c ./libft/ft_memset.c ./libft/ft_bzero.c ./libft/ft_memcpy.c ./libft/ft_memccpy.c ./libft/ft_memchr.c ./libft/ft_memcmp.c ./libft/ft_strchr.c ./libft/ft_strrchr.c ./libft/ft_strstr.c ./libft/ft_strnstr.c ./libft/ft_memmove.c ./libft/ft_isalpha.c ./libft/ft_isdigit.c ./libft/ft_isalnum.c ./libft/ft_isascii.c ./libft/ft_isprint.c ./libft/ft_toupper.c ./libft/ft_tolower.c ./libft/ft_strlcat.c ./libft/ft_strclr.c ./libft/ft_striter.c ./libft/ft_putendl.c ./libft/ft_putchar_fd.c ./libft/ft_putendl_fd.c ./libft/ft_putstr_fd.c ./libft/ft_putnbr_fd.c ./libft/ft_striteri.c ./libft/ft_strequ.c ./libft/ft_strnequ.c ./libft/ft_strmap.c ./libft/ft_strmapi.c ./libft/ft_memalloc.c ./libft/ft_memdel.c ./libft/ft_strnew.c ./libft/ft_strdel.c ./libft/ft_strjoin.c ./libft/ft_strsub.c ./libft/ft_strtrim.c ./libft/ft_itoa.c ./libft/ft_strsplit.c ./libft/ft_octal.c ./libft/ft_hex.c ./libft/ft_power_of.c ./libft/ft_count_digits.c ./check_flags_string.c ./checks.c ./help_functions.c ./str_help_functions.c ./va_arg_cspf.c ./va_arg_diouxx.c ./check_flags_diouxx.c ./check_flags_float.c ./long_double.c ./double.c ./help.c ./ft_printf.c ./check_flags_char.c ./libft/ft_count_udigits.c ./libft/ft_uitoa.c
OBJECTS = ./ft_putchar.o ./ft_putstr.o ./ft_strlen.o ./ft_strcpy.o ./ft_strcmp.o ./ft_strdup.o ./ft_strncmp.o ./ft_strncpy.o ./ft_strcat.o ./ft_strncat.o ./ft_putnbr.o ./ft_atoi.o ./ft_memset.o ./ft_bzero.o ./ft_memcpy.o ./ft_memccpy.o ./ft_memchr.o ./ft_memcmp.o ./ft_strchr.o ./ft_strrchr.o ./ft_strstr.o ./ft_strnstr.o ./ft_memmove.o ./ft_isalpha.o ./ft_isdigit.o ./ft_isalnum.o ./ft_isascii.o ./ft_isprint.o ./ft_toupper.o ./ft_tolower.o ./ft_strlcat.o ./ft_strclr.o ./ft_striter.o ./ft_putendl.o ./ft_putchar_fd.o ./ft_putendl_fd.o ./ft_putstr_fd.o ./ft_putnbr_fd.o ./ft_striteri.o ./ft_strequ.o ./ft_strnequ.o ./ft_strmap.o ./ft_strmapi.o ./ft_memalloc.o ./ft_memdel.o ./ft_strnew.o ./ft_strdel.o ./ft_strjoin.o ./ft_strsub.o ./ft_strtrim.o ./ft_itoa.o ./ft_strsplit.o ./ft_octal.o ./ft_hex.o ./ft_power_of.o ./ft_count_digits.o ./check_flags_string.o ./checks.o ./help_functions.o ./str_help_functions.o ./va_arg_cspf.o ./va_arg_diouxx.o ./check_flags_diouxx.o ./check_flags_float.o ./long_double.o ./double.o ./help.o ./ft_printf.o ./check_flags_char.o ./ft_count_udigits.o ./ft_uitoa.o
INC = ./libft/libft.h ft_printf.h

all: $(NAME)
	
$(NAME):
	gcc -c -Wextra -Werror -Wall  $(SRC) -I $(INC)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
