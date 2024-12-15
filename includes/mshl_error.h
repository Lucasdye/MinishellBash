/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshl_error.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:27:21 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/20 21:05:31 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHL_ERROR_H
# define MSHL_ERROR_H

# ifndef ERR_MODE
#  define ERR_MODE	0
# elif ERR_MODE < 0 || ERR_MODE > 1
#  undef ERR_MODE
#  define ERR_MODE  0
# endif

# ifndef INF_MODE
#  define INF_MODE	0
# elif INF_MODE < 0 || INF_MODE > 1
#  undef INF_MODE
#  define INF_MODE  0
# endif

# ifndef DBG_MODE
#  define DBG_MODE	0
# elif DBG_MODE < 0 || DBG_MODE > 1
#  undef DBG_MODE
#  define DBG_MODE  0
# endif

# include <errno.h>

/* string table gravity*/
# define MSHL_DLG_GRV_SIZE	5
# define MSHL_DLG_GRV_INF "info"
# define MSHL_DLG_GRV_WRN "warning"
# define MSHL_DLG_GRV_NRM "normal"
# define MSHL_DLG_GRV_CRTL "critical"
# define MSHL_DLG_GRV_FTL "fatal"

/* string message */
# define MSHL_DLG_ERROR "minishell: "
# define MSHL_MISS_ARG "missing argument"
# define MSHL_OVER_ARG "too many argument"
# define MSHL_NULL_ARG "empty argument"
# define MSHL_EINVAL "invalid argument"
# define MSHL_EXIT "exit by ctrl"
# define MSHL_NULL_PARA "abnormal null parameter"
# define MSHL_CMD "command \'"
# define MSHL_NOFOUND "\' not found"
# define MSHL_NOT_YET_FUNC "not yet supported"
# define MSHL_DEF_ARG_NOP "default, nothing to do"
# define MSHL_ISDIR "\' Is a directory"

# define MSHL_NOFOUND_NUM 127
# define MSHL_ISDIR_NUM 126

/* parse error message */
# define MSHL_DLG_PARSE_NL "newline"
# define MSHL_PARSE_UNBALANCED_QUOTE " missing quote"
# define MSHL_PARSE_BAD_TOKEN "syntax error near unexpected token"
# define MSHL_PARSE_AMB_REDIR "ambiguous redirect"
# define MSHL_PARSE_BAD_FD "Bad file descriptor"
# define MSHL_PARSE_BAD_SPACE "missing space separator"

/*builtin echo error*/
# define MSHL_DLG_ERR_ECHO "echo: "

/*builtin cd error*/
# define MSHL_DLG_ERR_CD "cd: "
# define MSHL_NOVALID_HOME_CD "HOME not set"
# define MSHL_DEFECTIVE_DRIVE "no valide logical drive "
/*builtin cd error*/
# define MSHL_DLG_ERR_PWD "pwd: "
# define MSHL_NOT_YET_ARG "argument not yet supported"

/*builtin export error*/
# define MSHL_DLG_ERR_EXPORT "export: "
# define MSHL_NOVALID_ARG_EXPORT_01 "bad option:"
# define MSHL_NOVALID_ARG_EXPORT_02 "invalid option"
# define MSHL_NOVALID_KEY_EXPORT "not valid in this context: "
# define MSHL_NOVALID_VAR_EXPORT "not a valid identifier"

/*builtin exit error*/
# define MSHL_DLG_ERR_EXIT "exit: "
# define MSHL_BAD_NUM_ARG "numeric argument required"

/*builtin unset error*/
# define MSHL_DLG_ERR_UNSET "unset: "
# define MSHL_NOVALID_ARG_UNSET "unrecognized option "

/*misc env error*/
# define MSHL_DLG_ERR_ENV "env: "
# define MSHL_NOTVALID_ENV_VAR "malformed variable"
# define MSHL_NO_ENV_ARG "empty variable table"
# define MSHL_NO_ENV_VAR "noexistent environment variable"

/* heredor error */
# define MSHL_HER_CTRLD_01 "here-document at line 1 delimited by end-of-file \
(wanted `"
# define MSHL_HER_CTRLD_02 "')"
/* enum error gravity */
typedef enum e_grv_err
{
	INFO = 0x0 ,
	WARNING = 0x1,
	NORMAL = 0x2 ,
	CRITICAL = 0x4,
	FATAL = 0x8
}	t_grv_err;

typedef struct s_data		t_data;

/* error gravity table struct */
typedef struct s_grav
{
	t_grv_err	num;
	char		*str;
}	t_grav;

/* error error max struct */
typedef struct s_err_max
{
	t_grv_err	n_grv;
	int			lvl;
}	t_err_max;

/* error signal struct */
typedef struct s_err_sig
{
	t_bool			ks;
	t_grv_err		n_grv;
	t_lssize_t		num;
	char			*str;
}	t_err_sig;

/* error content  struct */
typedef struct s_err_var
{
	t_bool			ks;
	t_grv_err		n_grv;
	int				lvl;
	int				num;
	char			*str;
	char			*arg;
}	t_err_var;

/* buffer */
typedef struct s_buff
{
	char			*str;
	size_t			size;
	size_t			idx;
}	t_buff;

/*error history list struct*/
typedef struct s_lst_err
{
	t_err_var			content;
	struct s_lst_err	*next;
}						t_lst_err;

/* error main struct */
typedef struct s_err
{
	t_lst_err		*hist_err;
	t_err_var		v;
	t_err_max		h_max;
	t_grav			grav[5];
	t_buff			buff;
}	t_err;

/* error main util */
void		init_error_tab(t_err *err);
void		init_error_data(t_err *err);
char		*set_err_tab(t_err *err, t_grv_err gravity);
void		set_err_var_01(t_err *err, t_bool ks, t_grv_err grav, int num);
void		set_err_var_02(t_err *err, t_bool ks, t_grv_err grav, int num);
void		log_hist_err(t_err *err);
void		log_hist_err_01(t_data *dt);
void		clear_hist_err(t_err *err);
void		set_error(t_data *dt, t_err *err, char *src);
void		chk_error_sig(t_data *dt);
void		print_error(t_data *dt);

/* error standard */
void		set_err_std_01(t_err *err);
void		set_err_std_02(t_err *err);

/* error builtin util */
void		chk_error_sig_buitin(t_err *err, char *src);
void		print_builtin_error(t_err *err, char *src);

/* misc utils*/
t_bool		ft_init_buff_m(t_buff *buff);
t_bool		ft_buffer_m(t_err *err, t_buff *buff, char *add_str);

/* lst utils*/
t_lst_err	*ft_lsterr_new(t_err_var *content);
t_lst_err	*ft_lsterrlast(t_lst_err *lst);
void		ft_lsterradd_back(t_lst_err **lst, t_lst_err *new);
void		lstiter_err(t_data *dt, t_err *err, t_lst_err *lst,
				void (*f)(t_data *dt, t_err *, t_err_var));
void		lstiter_err_01(t_data *dt, t_lst_err *lst,
				void (*f)(t_data *, t_err_var));
#endif
