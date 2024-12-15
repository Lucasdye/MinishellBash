# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 13:23:39 by jveuille          #+#    #+#              #
#    Updated: 2023/06/21 11:27:30 by jveuille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
PARENT_DIR= $(shell dirname $(shell pwd))
PARENT_NAME= $(shell basename $(PARENT_DIR))
CURRENT_DIR =$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
PROJET_NAME = $(shell basename $(CURRENT_DIR))
#
CC = gcc
NORM_EXE= norminette
CFLAGS = -Wall -Wextra -Werror -g3 -D PERR_MODE=1
#	Extra flags to give to compilers when they are supposed to 
#		invoke the linker, ‘ld’, such as -L. Libraries
LDFLAGS =
# Extra flags to give to compilers when they are supposed to invoke the linker, 
# ‘ld’, such as -L. Libraries
LDLIBS =
#	Library flags or names given to compilers when they are supposed to invoke
#		 the linker, ‘ld’. LOADLIBES is a deprecated (but still supported)
#		 alternative to LDLIBS. Non-library linker flags, such as -L, 
#		should go in the LDFLAGS variable. 
#
ROOT_DIR = ../$(PROJET_NAME)/
SRC_DIR =
BUILD_DIR =

LIBFT_DIR=libft/
LIBFT_AR=libft.a

LIBFT = ../$(LIBFT_DIR)

SRCS = ft_printf.c ft_fac_func_01.c ft_fac_func_02.c ft_format_char.c \
ft_format_hex.c ft_format_hex_ptr.c ft_list_op.c ft_printf_num.c \
ft_printf_num_u.c ft_printf_util_01.c ft_printf_util_02.c ft_printf_util_03.c\
ft_printf_util_bonus.c ft_printf_util_misc.c

OBJ_SRCS = $(addprefix $(ROOT_DIR)$(SRC_DIR), $(SRCS))
OBJ_DIRS = $(addprefix $(ROOT_DIR), $(OBJ_DIR))

OBJS =  $(addprefix $(OBJ_DIRS), $(SRCS:.c=.o))

BUILD_ROOT =$(NAME:%=$(ROOT_DIR)$(NAME))
BUILD = $(NAME:%=$(BUILD_DIR)$(NAME))

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

.PHONY: all bonus clean fclean re

$(NAME): $(OBJS)
	@ echo 
	@ echo "$(WHITE)[CREATE]$(COLRESET) : "$@
	@ cp ../$(LIBFT_AR) $(BUILD_ROOT)
	@ ar -rcs $(BUILD) $^

all: $(NAME)

$(OBJ)%.o : $(SRC)%.c
	@ echo "$(ONNEXT)[...]$(COLRESET)	: "$@$(MOVELINE)
	@ $(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -c $^ -o $@ 2>&1 </dev/null && \
		(echo $(CLEARLINE)"$(GREEN)[OK]$(COLRESET)	: "$@ ; (exit 0);) || \
		(echo $(CLEARLINE)"$(RED)[KO]$(COLRESET)	: "$@ ; (exit 1)) 

clean:
		rm -f $(OBJS)
fclean: 
		rm -f $(BUILD)

re: fclean all


