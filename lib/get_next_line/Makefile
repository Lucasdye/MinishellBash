# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 13:23:39 by jveuille          #+#    #+#              #
#    Updated: 2023/06/07 13:15:23 by jveuille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libftgnl.a
PARENT_DIR= $(shell dirname $(shell pwd))
PARENT_NAME= $(shell basename $(PARENT_DIR))
CURRENT_DIR=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
PROJET_NAME= $(shell basename $(CURRENT_DIR))
#
CC= gcc
NORM_EXE= norminette
CFLAGS= -Wall -Wextra -Werror -g3
#	Extra flags to give to compilers when they are supposed to 
#		invoke the linker, ‘ld’, such as -L. Libraries
LDFLAGS=
# Extra flags to give to compilers when they are supposed to invoke the linker, 
# ‘ld’, such as -L. Libraries
LDLIBS=
#	Library flags or names given to compilers when they are supposed to invoke
#		 the linker, ‘ld’. LOADLIBES is a deprecated (but still supported)
#		 alternative to LDLIBS. Non-library linker flags, such as -L, 
#		should go in the LDFLAGS variable. 
#
ROOT_DIR = ../$(PROJET_NAME)/
LIBFT_DIR =
LIBFT_AR =

SRC_DIR =
INC_DIR = 
OBJ_DIR =
BONUS_DIR =objs/
BUILD_DIR =

LIBFT = ../$(LIBFT_DIR)

# pour test
SRCS = $(shell find $(ROOT_DIR)$(SRC_DIRS) -name '*.c')
#
SRCS = get_next_line.c get_next_line_utils.c

BONUS_SRCS = $(ROOT_DIR)$(BONUS_DIR)
OBJ_DIRS = $(addprefix $(ROOT_DIR), $(OBJ_DIR))
OBJS =  $(addprefix $(OBJ_DIRS), $(SRCS:.c=.o))

BONUS_OBJS = $(BONUS_SRCS:%.c=$(ROOT_DIR)$(OBJ_DIR)%.o)

BUILD_ROOT =$(NAME:%=$(ROOT_DIR)$(NAME))
BUILD = $(NAME:%=$(ROOT_DIR)$(BUILD_DIR)$(NAME))	

INC_DIRS := $(shell find $(ROOT_DIR)$(INC_DIR) -type d )
INC = $(addprefix -I ,$(ROOT_DIR)$(INC_DIRS))

#===================================#
#   Colors for dialogue's cosmetic  #
#===================================#

ifdef TERM
DEF_COLOR = \033[0;39m
GREY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
LWHILE = \033[0;37m
COLRESET = \033[0m
endif

LINKCOLOR=	$(WHITE)
RMCOLOR = $(GREY)
ONNEXT=	$(LWHILE)
MOVELINE =	"\033[1A"
CLEARLINE =	"\033[K"

ITALICON =033[2m
ITALICOFF =\033[22m
BOLTON =033[1m
BOLTOFF =\033[21m
ULINEON = \033[4m
ULINEOFF = \033[24m

#===================================#
#              Rules                #
#===================================#

.PHONY: default all bonus clean fclean re

$(NAME): $(OBJS)
	@ echo 
	@ echo "$(WHITE)[CREATE]$(COLRESET) : "$@
	@ ar -rcs $(BUILD) $^

all: $(NAME)

bonus: all

$(OBJ)%.o : $(SRC)%.c
	@ echo "$(ONNEXT)[...]$(COLRESET)	: "$@$(MOVELINE)
	@ $(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -c $^ -o $@ 2>&1 </dev/null && \
		(echo $(CLEARLINE)"$(GREEN)[OK]$(COLRESET)	: "$@ ; (exit 0);) || \
		(echo $(CLEARLINE)"$(RED)[KO]$(COLRESET)	: "$@ ; (exit 1)) 
clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all
