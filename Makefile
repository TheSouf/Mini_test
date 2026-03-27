# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sofkhali <sofkhali@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/06 20:13:24 by sofkhali          #+#    #+#              #
#    Updated: 2026/03/27 19:14:57 by sofkhali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
 
SRCS_DIR	= src
PARSING_DIR	= $(SRCS_DIR)/parsing
BUILTINS_DIR	= $(SRCS_DIR)/builtins
EXEC_DIR	= $(SRCS_DIR)/exec
LIBFT_DIR	= libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a
 
CC		= gcc
CFLAGS		= -Wall -Wextra -Werror -g
 
SRCS		= $(SRCS_DIR)/main.c \
		  $(BUILTINS_DIR)/builtin_echo.c \
		  $(BUILTINS_DIR)/builtin_cd.c \
		  $(BUILTINS_DIR)/builtin_pwd.c \
		  $(BUILTINS_DIR)/builtin_env.c \
		  $(BUILTINS_DIR)/builtin_export.c \
		  $(BUILTINS_DIR)/builtin_unset.c \
		  $(BUILTINS_DIR)/builtin_exit.c \
		  $(BUILTINS_DIR)/utils_builtin.c \
		  $(EXEC_DIR)/exec_cmd.c \
		  $(EXEC_DIR)/exec_path.c \
		  $(EXEC_DIR)/exec_redir.c \
		  $(EXEC_DIR)/exec_process.c \
		  $(EXEC_DIR)/exec_pipeline.c \
		  $(EXEC_DIR)/utils_env.c \
		  $(EXEC_DIR)/utils_env2.c \
		  $(EXEC_DIR)/signal_handling.c \
		  $(PARSING_DIR)/lexer.c \
		  $(PARSING_DIR)/lexer_redir.c \
		  $(PARSING_DIR)/token.c \
		  $(PARSING_DIR)/cmd.c \
		  $(PARSING_DIR)/parsing.c \
		  $(PARSING_DIR)/utils.c \
		  $(PARSING_DIR)/utils_pars.c \
		  $(PARSING_DIR)/arg.c \
		  $(PARSING_DIR)/var.c \
		  $(PARSING_DIR)/var2.c
 
OBJS		= $(SRCS:.c=.o)
 
all: $(LIBFT_LIB) $(NAME)
 
$(LIBFT_LIB):
	make -C $(LIBFT_DIR)
 
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -I includes -lreadline -o $(NAME)
	@echo "✓ Compilation terminée: ./$(NAME)"
 
%.o: %.c
	$(CC) $(CFLAGS) -I includes -c $< -o $@
 
clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	@echo "✓ Fichiers objets supprimés"
 
fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_LIB)
	@echo "✓ Exécutable supprimé"
 
re: fclean all
 
.PHONY: all clean fclean re
