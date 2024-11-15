# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: espinell <espinell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 11:45:46 by espinell          #+#    #+#              #
#    Updated: 2024/08/06 11:45:46 by espinell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	minishell.c minishell_utils.c \
		builtin/builtin_utils.c builtin/builtin.c builtin/echo_utils.c builtin/echo.c builtin/export_utils.c \
		executor/executor_utils.c executor/executor.c \
		expander/expand_var_utils.c expander/expand_var.c \
		garbage_and_error/error.c garbage_and_error/garbage_collector.c \
		lexer/lexer_utils.c lexer/lexer.c lexer/utils.c \
		redirect/expand_heredoc.c redirect/here_doc.c redirect/heredoc_utils.c redirect/redirect_utils.c redirect/redirect.c \
		signal/ctrl.c signal/signal.c \
		utils/utils.c utils/utils_II.c utils/utils_III.c utils/utils_IV.c utils/utils_V.c utils/altsplit.c

NAME = minishell

LIBFT_DIR = Libft/
LIBFT = Libft/libft.a

COMPILE = gcc -g -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

all: $(NAME)

supp : 
	@make -C $(LIBFT_DIR)
	@$(COMPILE) $(OBJS) $(LIBFT) -lreadline -no-pie -o $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=ignore_readline.supp ./minishell

$(NAME): $(OBJS)
	@rm -rf tmp
	@make -C $(LIBFT_DIR)
	@mkdir tmp
	@$(COMPILE) $(OBJS) $(LIBFT) -lreadline -no-pie -o $(NAME)
	@echo "Compiled Minishell"

%.o: %.c
	@$(COMPILE) -I . -c $< -o $@ 

clean:
	@rm -f $(OBJS) $(BOBJS)
	@make clean -C $(LIBFT_DIR)
	@echo "Clean"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -rf tmp
	@rm -f $(NAME)
	@echo "Fclean"

re: fclean all