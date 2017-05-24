#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: ashulha <ashulha@student.us.org>           +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2017/05/23 00:30:25 by ashulha           #+#    #+#             *#
#*   Updated: 2017/05/23 00:30:27 by ashulha          ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = minishell

SRC = src/*.c

L_DIR = includes/libft/

FT_DIR = includes/ft_printf/

LIBFT = $(L_DIR)libft.a

PRINTF = $(FT_DIR)libftprintf.a

GNL = includes/gnl/get_next_line.c

all : $(NAME)

$(NAME):
	@echo "Building a minishell..."
	@make -C includes/libft re
	@make -C includes/ft_printf re
	@gcc -Wall -Wextra -Werror $(SRC) $(GNL) $(LIBFT) $(PRINTF) -o $(NAME) -lreadline -ledit

clean:
	@echo "Cleaning up *.o files..."
	@make -C $(L_DIR) clean
	@make -C $(FT_DIR) clean

fclean: clean
	@echo "Removing *.a files and executable..."
	@make -C $(L_DIR) fclean
	@make -C $(FT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all