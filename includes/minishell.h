/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:46:53 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 15:21:28 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BASE_H
#  include "../includes/base.h"
# endif

# ifndef LIBFT_H
#  include "../includes/libft.h"
# endif

# ifndef FT_PRINTF_H
#  include "../includes/ft_printf.h"
# endif

# ifndef GET_NEXT_LINE_H
#  include "../includes/get_next_line.h"
# endif

# ifndef MSHL_ERROR_H
#  include "../includes/mshl_error.h"
# endif

# ifndef MSHL_SIGNAL_H
#  include "../includes/mshl_signal.h"
# endif

# ifndef MSHL_ENV_H
#  include "../includes/mshl_env.h"
# endif

# ifndef MSHL_PIPE_H
#  include "../includes/mshl_pipe.h"
# endif

# ifndef MSHL_REDIR_H
#  include "../includes/mshl_redir.h"
# endif

# ifndef MSHL_PARSE_H
#  include "../includes/mshl_parse.h"
# endif

# ifndef MSHL_EXPAND_H
#  include "../includes/mshl_expand.h"
# endif

# ifndef MSHL_RULE_H
#  include "../includes/mshl_rule.h"
# endif

# ifndef MSHL_FILE_H
#  include "../includes/mshl_file.h"
# endif

# ifndef MSHL_BUILTIN_H
#  include "../includes/mshl_builtin.h"
# endif

# ifndef MSHL_EXEC_H
#  include "../includes/mshl_exec.h"
# endif

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

# define MSHL_DLG_PROMPT "$"
# define MSHL_DLG_PROMPT_PX "minishell$>"
# define MSHL_DLG_PRINT "declare -x "
# define MSHL_DLG_PRINT_PX "export "
# define MSHL_DLG_EXIT "exit\n"
# define MSHL_CMD_HOME "getent passwd "

# define LIMIT_PATH 4096

extern int			g_status;

typedef enum e_ptype
{
	p_deflt,
	p_posix
}	t_ptype;

typedef struct s_var
{
	char		**path;
	char		*oldpwd;
	char		*pwd;
	char		*home;
	char		*hostname;
	char		*user;
	char		*prompt_head;
	char		*prompt;
	char		*p_prnt;
	t_bool		ks_err_path;
	t_ptype		p_type;
	t_std		fd;
}	t_var;

typedef struct s_tmp
{
	char	*str;
}	t_tmp;

typedef struct s_data
{
	t_err		err;
	t_env		env;
	t_exec		exec;
	t_var		var;
	t_her		hd;
	t_bk		bk;
	t_tmp		tmp;
	t_parse		parse;
	t_bool		ks_end;
	t_bool		ks_mini;
	t_bool		ks_exit;
	t_bool		ks_tt;
	char		*rt_line;
	char		**arg;
	size_t		size;
	size_t		n_arg;
	long long	last_err;
}	t_data;

/* main function */
void		init_struct(t_data *dt);
t_bool		ft_get_var(t_data *dt);
t_bool		ft_set_prompt(t_data *dt, t_ptype type);
t_bool		ft_set_prompt_head(t_data *dt);
void		exit_free(t_data *dt, int status);

/* arg utils */
t_bool		set_str_arg(t_err *err, char **str, char *arg);
t_bool		set_str_arg_builtin(t_err *err, char **str, char *arg);

/* mem utils  */
void		free_envp(char **tab, register size_t idx);
void		free_tab(void **tab);
void		free_tab_idx(void **tab, register size_t idx);
void		free_tstr(t_str *dest);
void		free_obj(t_dup *dest);
void		free_all(t_data *dt);
void		free_str(char **s);

/* misc utils */
t_bool		ft_strchk(char *s1, char *s2);
char		*ft_strstr(char *str, char *to_find);
t_bool		chk_strstr(char *s1, char *s2);
char		*ft_strjoin_m(char *s1, char *s2);
char		*ft_strcat_m(char *dest, char *src);
t_bool		ft_isstr_whitespace(char *str);
t_bool		set_substr_arg(char **dest, char *src, register size_t start,
				register size_t end);
t_bool		get_substr(t_err *err, char **dest, char *src, t_idx idx);
t_bool		ft_strjcat_obj(t_dup *dest, t_dup *src);
t_dup		ft_strdup_obj(const char *s, int c, register size_t s_idx_init,
				register size_t s_idx_max);
void		ft_init_t_dup(t_dup *src);
t_dup		ft_dupjoint(char *s1, char *s2, char c, size_t start);
int			ft_tablen(char **tab);
t_bool		ft_isnum_str(char *str);
t_bool		ft_get_info(t_data *dt, char **var, int fd);
t_bool		ft_swrite(t_err *err, char *s, int fd);
void		ft_clean_path_cmd(char **cmd);
t_bool		ft_clean_path_cmd_02(t_data *dt, t_chk_str *chk, char *cmd);

/* tab utils */
t_chk_stab	ft_isstr_tab(char *s1, char **tab);
t_chk_stab	ft_isstr_tab_sz(char *s1, char **tab, register size_t size);
t_chk_stab	ft_isstr_tab_redir(char *s1, t_redir *tab, register size_t size);

#endif
