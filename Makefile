# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flafi <flafi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/15 10:49:59 by flafi             #+#    #+#              #
#    Updated: 2024/02/15 11:05:22 by flafi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF_COLOR = \033[0;39m
RED = \033[0;91m
GREEN = \033[0;32m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

.SILENT:
NAME = game
CFLAGS = -Wall -Wextra -Werror
CC = cc
LIBFT = libs/libft/libft.a

SRCS = main.c 
# garbage_collector.c 
OBJS = $(SRCS:.c=.o)


all: $(NAME) $(LIBFT)

$(NAME): $(OBJS)
	make -C libs/libft
	cc  $(SRCS) -o $(NAME) $(LIBFT) $(CFLAGS)
	echo "$(GREEN)Cub3D Compiled$(DEF_COLOR)"


clean:
	rm -f $(OBJS)
	make -C libs/libft clean
	echo "$(RED)Object Files are deleted$(DEF_COLOR)"

fclean: clean
	rm -rf $(NAME)
	make -C libs/libft fclean
	echo "Everything is clean"

re: fclean all

.PHONY: all clean fclean re