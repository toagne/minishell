# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 16:11:30 by jmakkone          #+#    #+#              #
#    Updated: 2024/09/05 05:07:01 by jmakkone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME            = minishell
LIBFT_DIR       = ./libft
SRC_DIR         = src
INC_DIR         = inc

SRC             = $(SRC_DIR)/main.c \
				  $(SRC_DIR)/shell_loop/init_shell_variables.c \
				  $(SRC_DIR)/shell_loop/shell_loop.c \
				  $(SRC_DIR)/shell_loop/prompt.c \
				  $(SRC_DIR)/shell_loop/handle_input.c \
				  $(SRC_DIR)/handle_input/handle_pipes.c \
				  $(SRC_DIR)/handle_input/parse_argument.c \
				  $(SRC_DIR)/handle_input/add_argument.c \
				  $(SRC_DIR)/handle_input/append_char.c \
				  $(SRC_DIR)/handle_input/handle_execute.c \
				  $(SRC_DIR)/handle_input/handle_redirections.c \
				  $(SRC_DIR)/handle_input/check_cmd.c \
				  $(SRC_DIR)/handle_input/check_path.c \
				  $(SRC_DIR)/handle_input/check_status.c \
				  $(SRC_DIR)/handle_input/error_handler.c \
				  $(SRC_DIR)/handle_input/exit_handler.c \
				  $(SRC_DIR)/utils/arr_len.c \
				  $(SRC_DIR)/utils/free_arr.c \
				  $(SRC_DIR)/utils/free_shell_allocations.c \
				  $(SRC_DIR)/utils/is_empty_str.c \
				  $(SRC_DIR)/utils/check_if_env_var.c \
				  $(SRC_DIR)/env/env_handler.c \
				  $(SRC_DIR)/builtins/handle_builtin.c \
				  $(SRC_DIR)/builtins/exit.c \
				  $(SRC_DIR)/builtins/env.c \
				  $(SRC_DIR)/builtins/unset.c \
				  $(SRC_DIR)/builtins/export.c \
				  $(SRC_DIR)/builtins/echo.c \
				  $(SRC_DIR)/builtins/pwd.c \
				  $(SRC_DIR)/builtins/cd.c \

OBJ_DIR         = obj
OBJ             = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT           = $(LIBFT_DIR)/libft.a

RM              = rm -f
CC              = clang
CFLAGS          = -Wall -Wextra -Werror \
				  -I$(INC_DIR) -g -ggdb3
LDFLAGS			= -lreadline


all:	$(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
