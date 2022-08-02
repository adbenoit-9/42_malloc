# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 16:29:13 by adbenoit          #+#    #+#              #
#    Updated: 2022/08/02 20:32:16 by adbenoit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION
CC		= gcc
CFLAGS 	= -Wall -Wextra -Werror -fsanitize=address -g3
IFLAGS 	= -I./incs

UNAME	:= $(shell uname)
ifeq ($(UNAME), Darwin)
	CFLAGS += -DOS
endif

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# DIRECTORIES
BUILD 			:= .build
SRC_DIR 		:= srcs
OBJ_DIR 		:= $(BUILD)/obj
SUB_DIR			:= 
DIRS			:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))


# FILES
NAME			:= libft_malloc_$(HOSTTYPE).so
LINK			:= libft_malloc.so
SRC				:=	malloc.c \
					free.c \
					realloc.c
SUB_SRC			:= 
# SRC				+= $(addprefix {name}, $(SUB_SRC))

OBJ				:= $(SRC:%.c=$(OBJ_DIR)/%.o)


# COLORS
NONE			= "\033[0m"
CL_LINE			= "\033[2K"
B_RED			= "\033[1;31m"
B_GREEN			= "\033[1;32m"
B_GREY	 		= "\033[1;38m"
B_MAGENTA 		= "\033[1;35m"
B_CYAN 			= "\033[1;36m"
B_BLUE 			= "\033[1;34m"
B_YELLOW 		= "\033[1;33m"
B_WHITE 		= "\033[1;37m"

# STATUS
DELETE			= "  $(B_MAGENTA)DELETE$(NONE)  "
OK				= "    $(B_GREEN)OK$(NONE)    "
KO				= "    $(B_RED)KO$(NONE)    "
LINK_OK			= "   $(B_YELLOW)LINK$(NONE)   "
LINK_KO			= "$(B_RED)LINK ERROR$(NONE)"
COMP			= " $(B_CYAN)COMPILING$(NONE)"

# MAKEFILE
$(NAME): $(OBJ)
	@printf "$(CL_LINE)"
	@($(CC) $(CFLAGS) -shared -o $(NAME) $(OBJ) \
		&& echo "[$(OK)] $@") \
		|| echo "[$(KO)] $@" 
	@(ln -s $(NAME) $(LINK) 2> /dev/null \
		&& echo "[$(LINK_OK)] $(LINK)") \
		|| echo "[$(LINK_KO)] $(LINK)"


all: $(NAME)

clean:
	@rm -Rf $(BUILD)
	@echo "[$(DELETE)] $(BUILD)"

fclean: clean
	@rm -Rf $(LINK)
	@echo "[$(DELETE)] $(LINK)"
	@rm -Rf $(NAME)
	@echo "[$(DELETE)] $(NAME)"

re: fclean all

test: re
	@echo ""
	@$(CC) $(CFLAGS) $(OBJ) tests.c
	@echo "\n\t$(B_BLUE)-- TESTS --$(NONE)"
	@./a.out
	@rm -Rf a.out

debug: CFLAGS += -DDEBUG
debug: re

.PHONY: all clean fclean re debug

$(BUILD):
	@mkdir $@ $(DIRS)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c ./incs/malloc.h | $(BUILD)
	@printf "$(CL_LINE)[$(COMP)] $< ...\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -fPIC -c $< -o $@
