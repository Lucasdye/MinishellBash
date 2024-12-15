# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 08:36:09 by jveuille          #+#    #+#              #
#    Updated: 2023/11/17 11:18:16 by jveuille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
PARENT_DIR= $(shell dirname $(shell pwd))
PARENT_NAME= $(shell basename $(PARENT_DIR))
CURRENT_DIR =$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
PROJET_NAME = $(shell basename $(CURRENT_DIR))
#
CC = clang
NORM_EXE= norminette
CFLAGS = -Wall -Wextra -Werror
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

SRCS = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_ishexa.c ft_iswhite_space.c ft_isalnum_var.c \
	ft_bzero.c ft_calloc.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memcpy_idx.c \
	ft_memmove.c ft_memset.c ft_tolower.c ft_toupper.c ft_putchar_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
	ft_strcmp.c ft_strcpy.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strmapi.c \
	ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strrchr_idx.c  ft_strtrim.c \
	ft_substr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_atoi.c ft_atoi_m.c\
	ft_itoa.c ft_atol.c ft_atof.c ft_atoh.c ft_ftoa.c ft_lltoa.c \
	ft_skip_white_space.c ft_trim_white_space.c ft_strjcat.c

BONUS_SRCS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJ_SRCS = $(addprefix $(ROOT_DIR)$(SRC_DIR), $(SRCS))
OBJ_DIRS = $(addprefix $(ROOT_DIR), $(OBJ_DIR))

OBJS =  $(addprefix $(OBJ_DIRS), $(SRCS:.c=.o))
#OBJS = $(SRCS:%.c=%.o)
BONUS_OBJS = $(addprefix $(OBJ_DIRS), $(BONUS_SRCS:%.c=%.o))
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

$(NAME): $(OBJS) $(BONUS_OBJS)
	@ echo 
	@ echo "$(WHITE)[CREATE]$(COLRESET) : "$@
	@ ar -rcs $(NAME) $^ 

all: $(NAME)

$(OBJ)%.o : $(SRC)%.c
	@ echo "$(ONNEXT)[...]$(COLRESET)	: "$@$(MOVELINE)
	@ $(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -c $^ -o $@ 2>&1 </dev/null && \
		(echo $(CLEARLINE)"$(GREEN)[OK]$(COLRESET)	: "$@ ; (exit 0);) || \
		(echo $(CLEARLINE)"$(RED)[KO]$(COLRESET)	: "$@ ; (exit 1)) 

clean:
		rm -f $(OBJS) $(BONUS_OBJS)
fclean: 
		rm -f $(BUILD)

re: fclean all
