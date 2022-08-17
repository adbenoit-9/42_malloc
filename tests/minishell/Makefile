# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/25 23:32:24 by adbenoit          #+#    #+#              #
#    Updated: 2022/08/17 15:01:35 by adbenoit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell

INC			=	includes/
HEADER		=	$(INC)minishell.h

SRCS_PATH	=	srcs/
UTIL_PATH 	=	srcs/util/
BUILTIN_PATH=	srcs/builtin/
PARS_PATH 	=	srcs/parsing/

TMP		=	main.c				run_cmd.c \
				redirect.c			fork_handle.c \
				signal.c			exec_cmd.c \
				ft_shlvl.c

UTIL		=	ft_error.c			deal_lst.c\
				deal_var.c			ft_env_utils.c 

BUILTIN 	=	ft_cd.c				ft_env.c \
				ft_export.c			ft_echo.c \
				ft_exit.c			ft_pwd.c \
				ft_unset.c

PARS 		=	parsing.c			deal_quote.c \
				deal_dollar.c		save_cmd.c \
				set_tokens.c		deal_sep.c \
				split_token.c		parse_file.c

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

LIB_DIR		=	libft
LIB			=	$(LIB_DIR)/libft.a
MALLOC		=	"../../libft_malloc.so"

SRCS		=	$(addprefix $(SRCS_PATH),$(TMP))
SRCS		+=	$(addprefix $(UTIL_PATH),$(UTIL))
SRCS		+=	$(addprefix $(BUILTIN_PATH),$(BUILTIN))
SRCS		+=	$(addprefix $(PARS_PATH),$(PARS))

all: $(LIB) $(NAME)

$(LIB) :
	@make -C $(LIB_DIR) > /dev/null

$(NAME) : $(LIB)
	@printf "\n"
	@$(CC) $(CFLAGS) $(MALLOC) $(SRCS) $(LIB) -o $(NAME) 
	@echo "Compilation of \033[33;1m$(NAME)\033[0;1m: [\033[1;32mOK\033[0;1m]\033[0m"

run: all
	@./$(NAME)

clean:
	@make -C $(LIB_DIR) clean > /dev/null
	@echo "\033[33;1m$(NAME)\033[0;1m: objects deleted\033[0m"

fclean:	clean
	@rm -Rf $(NAME)
	@make -C $(LIB_DIR) fclean > /dev/null
	@echo "\033[33;1m$(NAME)\033[0;1m: $(NAME) deleted\033[0m"

re: fclean all

FILE=norme_error.txt
ERROR= `cat $(FILE) | grep -B 1 "Error"`
norme:
	@make -C $(LIB_DIR) norme
	@printf "\033[33mLaunching ...\033[0m"
	@norminette */*/*c */*c */*h > $(FILE)
	@printf "\rNorme of \033[33;1m$(NAME)\033[0;1m: [\033[1;32mOK\033[0;1m]\033[0m"
	@ echo "\r$(ERROR)"
	@rm $(FILE)
	

debug:
	@echo "\033[34;1mOBJS\033[0;m = $(OBJS)"
	@echo "\033[34;1mHEADER\033[0;m = $(HEADER)\n"

.PHONY: all clean fclean re run
