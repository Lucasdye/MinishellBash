/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshl_parse.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:46:01 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/19 14:10:35 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHL_PARSE_H
# define MSHL_PARSE_H

# define MSHL_TK_TAB_NB	64

/* minishell internal definition */
# define MSHL_TK_NUM 14
# define MSHL_CMD_B_NUM 7
# define MSHL_REDIR_NUM 12
# define MSHL_SEP_NUM 7

# define MSHL_SPEC "\x20|><;()&"
# define MSHL_REDIR "|><"
# define MSHL_VAR_SPEC "*@#?-$!0"
# define MSHL_FILE "|><;()&"
# define MSHL_SEP "|><;"
# define MSHL_SEP_I "\x20;()|&"
# define MSHL_SEP_FDI "\x20><&;"
# define MSHL_SEP_FDO "><&;"
# define QUOTE "\x22\x27"
# define SQUOTE '\''
# define DQUOTE '\"'
# define BRACE "()"
# define LBRACE '('
# define RBRACE ')'
# define EQUAL '='
# define PLUS '+'
# define MINUS '-'
# define DOT '.'
# define SEP_INST ';'

typedef struct s_data	t_data;

//static char *const g_tk_tab[] = {"cd", tk_cmd_b};

/* enumateur d'ouverture de quote */
typedef enum e_dir
{
	out,
	in
}	t_dir;

/* enumateur de type de token */
typedef enum e_tk_type
{
	tk_none,
	tk_op,
	tk_ctrl_op,
	tk_redir_op,
	tk_fd,
	tk_file,
	tk_label,
	tk_cmd_b,
	tk_cmd,
	tk_var,
	tk_exp,
	tk_sep,
	tk_quote,
	tk_word
}	t_tk_type;

typedef enum e_sep_op
{
	c_none,
	c_inst,
	c_lbrace,
	c_rbrace,
	c_and,
	c_equal,
	c_or
}	t_sep_op;

/* enumateur des commandes builtin  */
typedef enum e_cmd_b
{
	c_echo,
	c_cd,
	c_pwd,
	c_export,
	c_unset,
	c_env,
	c_exit
}	t_cmd_b;

/* pointeur de fonction  pour tableau des builtin*/
typedef int				(*t_func_cmd)(t_data *dt ,char **arg);

typedef struct s_kstr
{
	t_bool	ks;
	char	*str;
}	t_kstr;

typedef struct s_ks_stab
{
	t_bool	ks;
	size_t	size;
	size_t	idx;
}	t_ks_stab;

typedef struct s_func_cmdb
{
	char		*name;
	t_func_cmd	func;
}	t_func_cmdb;

typedef struct s_quote
{
	t_bool	ks;
	char	type;
	t_dir	dir;
}	t_quote;

typedef struct s_token
{
	char		*name;
	char		**arg;
	char		*prvar;
	t_tk_type	type;
	size_t		subtype;
}	t_token;

typedef struct s_tk_tab
{
	t_token		*tab;
	size_t		size;
	size_t		nbr;
	size_t		idx;
}	t_tk_tab;

typedef struct s_lst_tk	t_lst_tk;

typedef struct s_parse
{
	t_func_cmdb	ftab[MSHL_CMD_B_NUM];
	t_redir		rtab[MSHL_REDIR_NUM];
	t_kstr		stab[MSHL_SEP_NUM];
	char		*t_tk_tab[MSHL_TK_NUM];
	t_tk_tab	tk;
	t_idx		idx;
	t_quote		quote;
	size_t		nbr_bk;
	t_chk_str	icmd;
	t_bool		is_redir;
	t_bool		err_space;
}	t_parse;

/* main parse*/
t_bool		parse_rt_line(t_data *dt);
t_chk_str	parse_tk_fd(t_data *dt, t_str *s_tmp, size_t *idx);

/* token utils*/
t_bool		set_token(t_data *dt, char *s1, t_tk_type type, size_t sub_type);
t_bool		store_tk_str(t_data *dt, t_str *s_tmp, size_t *idx, t_bool ks_end);
t_bool		ft_set_tk_quote(t_data *dt, char c, size_t subtype);
t_bool		ft_chk_tk_redir(t_data *dt, size_t *idx);
void		ft_trim_opt(t_data *dt, size_t *idx, t_idx *s_idx);
t_bool		ft_set_tk_redir_opt(t_data *dt, t_token *tk, size_t *idx,
				t_idx s_idx);
t_bool		ft_set_tk_var(t_data *dt, register size_t idx);
t_bool		ft_set_tk_cmdb(t_data *dt, t_str *s1);
t_chk_stab	ft_isstr_ftab_sz(char *s1, t_func_cmdb *tab,
				register size_t size);
t_bool		ft_set_tk_sep(t_data *dt, size_t *idx);
t_bool		ft_chk_tk_fd(t_data *dt, t_str *s_tmp, size_t *idx);
void		ft_chk_filename(t_data *dt, t_idx *s_idx);
t_bool		ft_chk_tk_file(t_data *dt, size_t *idx, t_idx s_idx);
t_bool		ft_chk_tk_word(t_data *dt, t_str *s_tmp);
t_bool		ft_merge_tk_redir(t_data *dt);

/* quote utils*/
void		ft_init_flg_quote(t_quote *quote);
void		ft_set_flg_quote(t_quote *quote, char c);
t_bool		ft_ctrl_tk_quote(t_data *dt);

/* init utils */
void		init_tk_tab_type(t_data *dt);
void		init_tk_tab_cmdb(t_data *dt);
void		init_tk_tab_redir(t_data *dt);
void		init_tk_tab_sep(t_data *dt);

/* mem utils */
void		free_tk_u(t_token **tab, register size_t idx);
void		free_tk_tb(t_token **tab, register size_t size);

/* misc utils */
t_bool		init_tk_tab(t_data *dt, t_token **tab, register size_t size);
t_bool		redim_tk_tab(t_data *dt, register size_t size_data);
t_chk_str	ft_srchstr(char c, char *wtab);
t_bool		ft_isquote(char c, register size_t type);
t_chk_str	ft_chk_quote(char c);
t_chk_str	ft_chk_str_quote(char *str);
t_chk_str_e	ft_chk_str_quote_01(char *str);
t_bool		ft_clean_str_quote(t_data *dt, t_quote *qt, char **str);
t_chk_str_e	ft_clean_str_quote_ext(t_data *dt, char **str);
t_bool		ft_ischar_spec(char c, char *wtab, register size_t type);
t_chk_str	ft_chk_spec(char c, char *wtab);
size_t		ft_find_tab_idx(char c, char *wtab);
t_bool		ft_isvar_str(char *s);
t_bool		ft_create_stab(t_err *err, char ***tab, size_t size);
t_bool		ft_copy_stab(t_err *err, char ***dest, char **src,
				register size_t size);
t_bool		ft_resize_stab(t_err *err, char ***tab, register size_t size,
				register size_t new_size);
t_chk_str_e	ft_is_redir_str(t_data *dt, size_t idx);
t_bool		ft_conform_str(t_data *dt);
char		*ft_clean_white_space_qt(char *src);

#endif 