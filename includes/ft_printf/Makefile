# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashulha <ashulha@student.42.us.crg>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/09 12:46:14 by ashulha           #+#    #+#              #
#    Updated: 2017/03/09 12:46:15 by ashulha          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libftprintf.a

FLAG =		-Wall -Werror -Wextra -I 

PFDR =		src/

FTDR =		libft/

PFFL =		check_format.c ft_printf.c identification_1.c identification_2.c identification_3.c \
 			count_position.c flags_set.c flags_others.c ft_build.c length_precision.c \
 			read_wchar.c min_width.c identification_4.c

FTFL =		ft_atoi.c ft_isalnum.c ft_isdigit.c ft_isprint.c ft_itoa_double.c ft_itoa_double_g.c \
			ft_itoa_exp.c ft_itoa_negative.c ft_power.c ft_putchar.c ft_putstr.c ft_strdup.c \
			ft_strjoin.c ft_strlen.c ft_strnew.c ft_strsub.c ft_toupper_s.c ft_itoa_signed.c \
			ft_itoa_unsigned.c ft_itoa.c ft_memset.c  ft_memalloc.c ft_countnumber.c ft_bzero.c

PFSR =		$(addprefix $(PFDR), $(PFFL))

FTSR =		$(addprefix $(FTDR), $(FTFL))

POBJ =		$(PFSR:.c=.o)
LOBJ =		$(FTSR:.c=.o)

all: $(NAME)

$(POBJ): %.o: %.c
	@gcc -c $(FLAG) src/ $< -o $@

$(LOBJ): %.o: %.c
	@gcc -c $(FLAG) libft/ $< -o $@

$(NAME): $(LOBJ) $(POBJ)
	@ar rcs $(NAME) $(POBJ) $(LOBJ)

clean:
	@rm -rf $(PFDR)*.o
	@rm -rf $(FTDR)*.o $(FTDR)libft.a

fclean: clean
	@rm -rf $(NAME)

re: fclean all
