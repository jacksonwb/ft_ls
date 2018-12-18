# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/01 14:21:53 by jbeall            #+#    #+#              #
#    Updated: 2018/12/13 10:59:25 by jbeall           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
FLAGS = -Wall -Werror -Wextra
SRC_DIR = ./src/
SRC = ft_ls.c ls_sort.c ls_print.c ls_utils1.c ls_utils2.c ls_print_utils.c \
ls_sort_utils.c ls_parse.c ls_utils3.c
INC_DIR = ./includes/
LIB_INC_DIR = ./libft/includes/
LIB = ./libft/libft.a

$(NAME):
	@make -C ./libft --no-print-directory
	@echo "Creating ft_ls executable..."
	@gcc -o $(NAME) $(FLAGS) $(addprefix $(SRC_DIR), $(SRC)) $(LIB) -I$(LIB_INC_DIR) -I$(INC_DIR) -O3
	@echo "\033[92mdone!\033[0m"
all: $(NAME)
dev:
	@rm -f ./ft_ls
	@make -C ./libft --no-print-directory
	@echo "compiling dev build..."
	@gcc -o $(NAME) $(FLAGS) -g $(addprefix $(SRC_DIR), $(SRC)) $(LIB) -I$(LIB_INC_DIR) -I$(INC_DIR)
	@echo "\033[92mdone!\033[0m"
clean:
	@echo "cleaning..."
	@make clean -C ./libft --no-print-directory
fclean: clean
	@rm -f $(NAME)
	@echo "ft_ls executable removed!"
	@make fclean -C ./libft --no-print-directory
re: fclean all