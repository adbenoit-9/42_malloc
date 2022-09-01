# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 16:29:13 by adbenoit          #+#    #+#              #
#    Updated: 2022/09/01 14:18:38 by adbenoit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION
CC		= gcc
CFLAGS 	= -Wall -Wextra -Werror
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
SUB_DIR			:= utils
TEST_DIR		:= tests
DIRS			:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))


# FILES
NAME			:= libft_malloc_$(HOSTTYPE).so
LINK_NAME		:= libft_malloc.so
TEST_EXEC		:= tests_malloc
SRC				:=	malloc.c \
					write_heap.c \
					read_heap.c \
					iter_heap.c
SUB_SRC			:= ft_putnbr_base.c \
					ft_bzero.c \
					ft_strlen.c \
					print_metadata.c \
					ft_memcpy.c
SRC				+= $(addprefix utils/, $(SUB_SRC))

TEST_SRC		:=	main.c \
					malloc_tests.c \
					realloc_tests.c \
					free_tests.c
TEST_SRC		:= $(addprefix $(TEST_DIR)/, $(TEST_SRC))

OBJ				:= $(SRC:%.c=$(OBJ_DIR)/%.o)


# COLORS
NONE			= \033[0m
CL_LINE			= \033[2K
B_RED			= \033[1;31m
B_GREEN			= \033[1;32m
B_GREY	 		= \033[1;38m
B_MAGENTA 		= \033[1;35m
B_CYAN 			= \033[1;36m
B_BLUE 			= \033[1;34m
B_YELLOW 		= \033[1;33m
B_WHITE 		= \033[1;37m

# STATUS
DELETE			= "\ \ "$(B_MAGENTA)"DELETE"$(NONE)"\ \ "
OK				= "\ \ \ \ "$(B_GREEN)"OK"$(NONE)"\ \ \ \ "
KO				= "\ \ \ \ "$(B_RED)"KO"$(NONE)"\ \ \ \ "
LINK_OK			= "\ \ \ "$(B_YELLOW)"LINK"$(NONE)"\ \ \ "
LINK_KO			= ""$(B_RED)"LINK ERROR"$(NONE)""
COMP			= "\ "$(B_CYAN)"COMPILING"$(NONE)""

# MAKEFILE
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -shared -o $@ $(OBJ)
	@echo "$(CL_LINE)[$(OK)] $@"
	@(ln -sf $@ $(LINK_NAME) 2> /dev/null \
		&& echo "[$(LINK_OK)] $(LINK_NAME)") \
		|| echo "[$(LINK_KO)] $(LINK_NAME)"

all: $(NAME)

$(BUILD):
	@mkdir $@ $(DIRS)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c | $(BUILD)
	@printf "$(CL_LINE)[$(COMP)] $< ...\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -fPIC -c $< -o $@

clean:
	@rm -Rf $(BUILD)
	@echo "[$(DELETE)] $(BUILD)"

fclean: clean
	@rm -Rf $(LINK_NAME) $(NAME) $(TEST_EXEC)
	@echo "[$(DELETE)] $(LINK_NAME)"
	@echo "[$(DELETE)] $(NAME)"

re: fclean all

run: $(NAME)
	@$(CC) $(CFLAGS) $(IFLAGS) $(TEST_SRC) $(LINK_NAME) -o $(TEST_EXEC)
	@echo "[$(OK)] tests"
	@echo "usage:\n  ./run.sh ./tests_malloc [function(s) to test]"

debug: CFLAGS += -DDEBUG
debug: re

debug_make:
	@echo $(SRC)

.PHONY: all clean fclean re debug run
