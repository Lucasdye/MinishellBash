# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 13:23:39 by jveuille          #+#    #+#              #
#    Updated: 2023/11/21 15:30:34 by jveuille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
PARENT_DIR= $(shell dirname $(shell pwd))
PARENT_NAME= $(shell basename $(PARENT_DIR))
CURRENT_DIR =$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
PROJET_NAME = $(shell basename $(CURRENT_DIR))
#
CC = gcc
NORM_EXE= norminette
#CFLAGS = -Wall -Wextra -Werror -g3 -O3  -Wno-unused-result

CFLAGS = -Wall -Wextra -Werror -g3 -D ERR_MODE=1 -D INF_MODE=0 -D DBG_MODE=0 -D SPTH_MODE=0 -D BUFF_MOD=1 #-std=c99 #-fsanitize=address  #-MMD 
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

LIB_AR=libmy.a
LIBFT_DIR=libft/
LIBFT_AR=libft.a
LIBPF_DIR=ft_printf/
LIBPF_AR=libftprintf.a
LIBGL_DIR=get_next_line/
LIBGL_AR=libftgnl.a

SRC_DIR = srcs/
INC_DIR = includes/
LIB_DIR = lib/
OBJ_DIR = objs/
#BONUS_DIR =
#BUILD_DIR = 

#===================================#
#  Flag for include archive library #
#===================================#

LIBFT= $(ROOT_DIR)$(LIB_DIR)$(LIBFT_DIR)
LIB_FT = $(addprefix $(ROOT_DIR)$(LIB_DIR), $(LIBFT_AR))
FLG_LIBFT= -L $(ROOT_DIR)$(LIB_DIR) -l:$(LIBFT_AR)
#FLG_LIBFT= -L $(ROOT_DIR)$(LIB_DIR) -I$(LIBFT_AR)

LIBPF= $(ROOT_DIR)$(LIB_DIR)$(LIBPF_DIR)
LIB_PF= $(addprefix $(ROOT_DIR)$(LIB_DIR), $(LIBPF_AR))
FLG_LIBPF= -L $(ROOT_DIR)$(LIB_DIR) -l:$(LIBPF_AR)
#FLG_LIBPF= -L $(ROOT_DIR)$(LIB_DIR) -I:$(LIBPF_AR)

LIBGL= $(ROOT_DIR)$(LIB_DIR)$(LIBGL_DIR)
LIB_GL= $(addprefix $(ROOT_DIR)$(LIB_DIR), $(LIBGL_AR))
FLG_LIBGL= -L $(ROOT_DIR)$(LIB_DIR) -l:$(LIBGL_AR)
#FLG_LIBGL= -L $(ROOT_DIR)$(LIB_DIR) -I$(LIBGL_AR)

 
FLG_LIB= $(FLG_LIBMLX) $(FLG_LIBFT) $(FLG_LIBPF)  $(FLG_LIBGL)


#===================================#
#    source directory repository    #
#===================================#

# Only for test , forbidden by norm
#SRCS = $(shell find $(ROOT_DIR)$(SRC_DIR) $(ROOT_DIR)$(INC_DIR) -name '*.c')
#SRCS = $(shell find -path '$(ROOT_DIR)$(SRC_DIR)' -name '*.c')

SRCS_CORE = minishell.c mshl_exit.c signal_utils_01.c
SRCS_ARG = arg_utils_01.c
SRCS_CMD = cd_01.c cd_02.c cd_03.c cd_utils_err.c \
			echo.c exit.c pwd.c env_01.c env_02.c
SRCS_ENV = env_utils_01.c env_utils_02.c env_utils_setvar.c env_utils_tab.c \
			env_utils_path.c env_utils_pwd.c  env_utils_err.c \
			env_utils_var.c env_utils_var_ini.c\
			env_utils_print_01.c env_utils_print_02.c env_utils_def.c
SRCS_ERR = error_utils_init.c error_utils_lst.c error_utils_01.c error_utils_02.c\
			error_utils_std.c error_utils_builtin.c error_utils_sig.c
SRCS_EXEC = exec.c exec_subshell.c \
			exec_cmd_01.c exec_cmd_02.c exec_cmd_err.c \
			exec_utils_01.c exec_utils_02.c exec_utils_03.c \
			exec_utils_mini.c exec_utils_tk_merge.c exec_utils_heredoc.c
SRCS_EXPN = expand.c expand_utils_01.c\
			expand_utils_cmd_01.c expand_utils_cmd_02.c expand_utils_cmd_03.c\
			expand_utils_excd.c expand_utils_path_01.c expand_utils_redir.c\
			expand_utils_var_01.c expand_utils_var_02.c
SRCS_FILE = file_ops.c file_utils_01.c
SRCS_INIT = init_utils_01.c init_utils_02.c init_utils_03.c init_utils_04.c
SRCS_MEM = mem_utils_01.c mem_utils_02.c mem_utils_obj.c 
SRCS_MISC = misc_utils_01.c misc_utils_02.c misc_utils_03.c misc_utils_04.c \
			misc_utils_strdup_01.c misc_utils_strdup_02.c\
			misc_utils_split_str.c misc_utils_split_qt_01.c misc_utils_split_qt_02.c \
			misc_utils_buff.c misc_utils_lst.c misc_utils_file.c \
			misc_utils_quote_01.c misc_utils_quote_02.c \
			misc_utils_str_01.c \
			misc_utils_tab_01.c misc_utils_tab_02.c
SRCS_PARS = parse.c parse_utils_tk_01.c parse_utils_tk_02.c parse_token.c \
			parse_quote.c parse_sep.c parse_spec.c \
			parse_fd.c parse_redir_01.c parse_redir_02.c parse_file.c \
			parse_cmdb.c parse_word.c parse_utils_01.c parse_utils_02.c
SRCS_PRMPT = prompt.c prompt_utils.c
SRCS_REDIR = dup_utils_01.c dup_utils_02.c \
			heredoc_01.c heredoc_02.c heredoc_utils.c heredoc_err.c \
			pipe_utils_01.c pipe_utils_02.c \
			redir_01.c redir_utils_01.c \
			redirections_loop.c redir_exec.c redir_exec_utils.c
SRCS_RULE = rule_check_01.c rule_check_02.c  rule_check_03.c rule_utils.c

#prefixing directory names
SRCS_ARGS = $(addprefix arg/, $(SRCS_ARG))
SRCS_CMDS = $(addprefix builtin_cmd/, $(SRCS_CMD))
SRCS_ENVS = $(addprefix env/, $(SRCS_ENV))
SRCS_ERRS = $(addprefix error/, $(SRCS_ERR))
SRCS_EXECS = $(addprefix exec/, $(SRCS_EXEC))
SRCS_EXPNS = $(addprefix expand/, $(SRCS_EXPN))
SRCS_FILES = $(addprefix file/, $(SRCS_FILE))
SRCS_INITS = $(addprefix init/, $(SRCS_INIT))
SRCS_MEMS = $(addprefix mem/, $(SRCS_MEM))
SRCS_MISCS = $(addprefix misc/, $(SRCS_MISC))
SRCS_PARSS = $(addprefix parse/, $(SRCS_PARS))
SRCS_PRMPTS = $(addprefix prompt/, $(SRCS_PRMPT))
SRCS_REDIRS = $(addprefix redir/, $(SRCS_REDIR))
SRCS_RULES = $(addprefix rule/, $(SRCS_RULE))


SRCS= $(SRCS_CORE) $(SRCS_ARGS) $(SRCS_CMDS) $(SRCS_ENVS) $(SRCS_ERRS) \
	$(SRCS_EXECS) $(SRCS_EXPNS) $(SRCS_FILES) $(SRCS_INITS) $(SRCS_MEMS) \
	$(SRCS_MISCS) $(SRCS_PARSS) $(SRCS_PRMPTS) $(SRCS_REDIRS) $(SRCS_RULES)

# listing of all  source subdirectory
SRC_SUB_DIR = $(shell find $(SRC_DIR) -type d)
OBJ_SUB_DIR = $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC_SUB_DIR))

#prefixing directory names with the root of the project name
OBJ_SRCS = $(addprefix $(ROOT_DIR)$(SRC_DIR), $(SRCS))
OBJ_DIRS = $(addprefix $(ROOT_DIR), $(OBJ_DIR))

OBJS =  $(addprefix $(OBJ_DIRS), $(SRCS:.c=.o))

BUILD_ROOT =$(NAME:%=$(ROOT_DIR)$(NAME))
BUILD = $(NAME:%=$(ROOT_DIR)$(BUILD_DIR)$(NAME))

#include .h directory
INC_DIRS := $(shell find $(INC_DIR) -type d )
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

ITALICON =\033[2m
ITALICOFF =\033[22m
BOLTON =\033[1m
BOLTOFF =\033[21m
ULINEON = \033[4m
ULINEOFF = \033[24m

#===================================#
#              Rules                #
#===================================#
.PHONY: default all bonus clean fclean re


$(NAME): $(OBJS) $(LIB_FT) $(LIB_PF) $(LIB_SPF) $(LIB_GL) $(LIB_MLX)
	@ echo 
	@ echo "$(YELLOW)➼ Creating $(NAME)'s executable$(COLRESET)"
	@ echo "target	:$(WHITE)$(NAME)$(COLRESET) in $(WHITE)$(ROOT_DIR)$(COLRESET)"
	@ $(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(FLG_LIB) $(FLG_GPRH) $^ -lreadline -o $(ROOT_DIR)$@ \
		2>&1 </dev/null && \
		(echo $(CLEARLINE)"$(GREEN)[OK]$(COLRESET)	: "$@ ; (exit 0);) || \
		(echo $(CLEARLINE)"$(RED)[KO]$(COLRESET)	: "$@ ; (exit 1)) 
	
all: lambda $(NAME)

$(OBJ_DIRS)%.o : $(SRC_DIR)%.c
	@ echo "$(ONNEXT)[...]$(COLRESET)	: "$@$(MOVELINE)
	@ if [ ! -d "$(ROOT_DIR)$(OBJ_DIR)" ]; then \
		mkdir -p $(ROOT_DIR)$(OBJ_DIR) 2>&1 </dev/null && \
			echo "$(WHITE)[CREATE]$(COLRESET)	:" $(ROOT_DIR)$(OBJ_DIR); (exit 0); \
		mkdir -p $(ROOT_DIR)$(OBJ_SUB_DIR)  2>&1 </dev/null && \
			echo "$(WHITE)[CREATE]$(COLRESET)	:" $(ROOT_DIR)$(OBJ_SUB_DIR); (exit 0); \
	fi
	@ $(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(INC) -c $^ -o $@ 2>&1 </dev/null && \
		(echo $(CLEARLINE)"$(GREEN)[OK]$(COLRESET)	: "$@ ; (exit 0);) || \
		(echo $(CLEARLINE)"$(RED)[KO]$(COLRESET)	: "$@ ; (exit 1)) 

$(LIB_FT):
	@ echo 
	@ echo "$(YELLOW)➼ Generate library$(COLRESET)"
	@ echo "target	:$(WHITE)$(LIBFT_AR)$(COLRESET) in $(WHITE)$(LIBFT)$(COLRESET)"
	@ make -C $(LIBFT) all 2>&1 </dev/null && \
		(echo $(CLEARLINE)"$(GREEN)[OK]$(COLRESET)	: "$@ ; (exit 0);) || \
		(echo $(CLEARLINE)"$(RED)[KO]$(COLRESET)	: "$@ ; (exit 1)) 
	@mv $(LIBFT)$(LIBFT_AR) $(ROOT_DIR)$(LIB_DIR)

$(LIB_PF):
	@ echo 
	@ echo "$(YELLOW)➼ Generate library$(COLRESET)"
	@ echo "target	:$(WHITE)$(LIBPF_AR)$(COLRESET) in $(WHITE)$(LIBPF)$(COLRESET)"
	@ make -C $(LIBPF) all 2>&1 </dev/null && \
		(echo $(CLEARLINE)"$(GREEN)[OK]$(COLRESET)	: "$@ ; (exit 0);) || \
		(echo $(CLEARLINE)"$(RED)[KO]$(COLRESET)	: "$@ ; (exit 1)) 
	@mv $(LIBPF)$(LIBPF_AR) $(ROOT_DIR)$(LIB_DIR)

$(LIB_GL):
	@ echo  
	@ echo "$(YELLOW)➼ Generate library$(COLRESET)"
	@ echo "target	:$(WHITE)$(LIBGL_AR)$(COLRESET) in $(WHITE)$(LIBGL)$(COLRESET)"
	@ make -C $(LIBGL) all 2>&1 </dev/null && \
		(echo $(CLEARLINE)"$(GREEN)[OK]$(COLRESET)	: "$@ ; (exit 0);) || \
		(echo $(CLEARLINE)"$(RED)[KO]$(COLRESET)	: "$@ ; (exit 1)) 	
	@ mv $(LIBGL)$(LIBGL_AR) $(ROOT_DIR)$(LIB_DIR)


norm: $(OBJ_SRCS) $(INC_DIRS) $(LIBFT) $(LIBPF)
	@ echo "$(YELLOW)➼ Check Norm$(COLRESET)"
	@ echo "target	:$(WHITE)"$(ROOT_DIR)"$(COLRESET)"
	@ if [ ! -f "$(NORM_EXE)" ]; then \
		echo $(CLEARLINE)"$(RED)[KO]	$(WHITE)"$(NORM_EXE)" not found$(COLRESET)"; (exit 1); else \
		echo $(CLEARLINE)"$(GREEN)[OK]	$(WHITE)"$(NORM_EXE)" found$(COLRESET)"; \
		$(NORM_EXE) $^ | \
			(! grep -E -B 1 "(^Warning|^Error)" 2>&1 </dev/null) && \
			echo "$(GREEN)[NORM]$(COLRESET)	: pass" || \
			(echo "$(RED)[NORM]$(COLRESET)	: failed "); (exit 0); \
	fi

lambda:
	@ echo "$(YELLOW)➼ Compiling $(NAME)'s project$(COLRESET)"


clean:
	@ echo "$(YELLOW)➼ Remove objects$(COLRESET)"
	@ rm -f $(OBJS) $(LIBFT)*.o $(LIBPF)*.o  $(LIBGL)*.o $(LIBMLX)*.o 2>&1 </dev/null && \
		echo "$(RMCOLOR)[DEL]$(COLRESET)	:" obj ; (exit 0)
	@ if [  -d "$(ROOT_DIR)$(OBJ_DIR)" ]; then \
		rm -r $(OBJ_DIR) 2>&1 </dev/null && \
			echo "$(RMCOLOR)[DEL]$(COLRESET)	:" dep ; (exit 0); \
	fi
	@ echo 

fclean: clean
	@ echo "$(YELLOW)➼ Remove librarys$(COLRESET)"
	@ rm -f $(NAME)  2>&1 </dev/null && \
		echo "$(RMCOLOR)[DEL]$(COLRESET)	:" $(NAME) ; (exit 0);
	@ rm -f $(LIB_DIR)$(LIBFT_AR) 2>&1 </dev/null && \
		echo "$(RMCOLOR)[DEL]$(COLRESET)	:" $(LIB_DIR)$(LIBFT_AR) ; (exit 0)
	@ rm -f $(LIB_DIR)$(LIBPF_AR) 2>&1 </dev/null && \
		echo "$(RMCOLOR)[DEL]$(COLRESET)	:" $(LIB_DIR)$(LIBPF_AR) ; (exit 0)
	@ rm -f $(LIB_DIR)$(LIBGL_AR) 2>&1 </dev/null && \
		echo "$(RMCOLOR)[DEL]$(COLRESET)	:" $(LIB_DIR)$(LIBGL_AR) ; (exit 0)
	@ echo 

re: fclean all
