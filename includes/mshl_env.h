/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshl_env.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:43:47 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 07:39:04 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHL_ENV_H
# define MSHL_ENV_H

# ifndef SPTH_MODE
#  define SPTH_MODE	0
# elif SPTH_MODE < 0 || SPTH_MODE > 1
#  undef SPTH_MODE
#  define SPTH_MODE  0
# endif

# define MSHL_DEF_ENV_PATH "/etc/environment"

typedef struct s_data	t_data;

/* minishell internal definition */
typedef char			*t_env_str;

typedef struct s_chk_stab
{
	t_bool	ks;
	size_t	idx;
}	t_chk_stab;

typedef struct s_chk_stab_e
{
	t_bool		ks;
	t_chk_stab	stab;
}	t_chk_stab_e;

typedef struct s_env_var
{
	char	*name;
	char	*val;
}	t_env_var;

typedef struct s_env
{
	char		**var_name;
	char		**tab;
	size_t		size;
	size_t		idx;

}	t_env;

/* env utils */
t_bool			set_envp(t_data *dt, char **envp);
t_bool			set_def_env(t_data *dt);
t_bool			print_env(t_data *dt, char **env, t_bool ks);
t_bool			print_env_line(t_err *err, char **env, size_t i);
t_bool			print_env_sort(t_data *dt, t_err *err, t_bool flt);
t_bool			print_env_filter(t_data *dt, t_err *err, t_env *env,
					t_bool flt);
t_bool			resize_env_tab(t_err *err, t_env *env,
					register size_t new_size);
void			push_up_env_tab(t_err *err, t_env *env, register size_t idx);
void			sort_env_tab(t_err *err, t_env *env);
void			init_chk_var(t_chk_stab_e *chk);
t_bool			set_err_init(t_err *err, char *str);
t_chk_stab_e	chk_var_exist_env(t_err *err, t_env *env, char *str);
//char			*ft_evar_join(t_env_var var);
char			*get_env_var(t_data *dt, char *var_name);
t_bool			set_env_var(t_data *dt, char **var_name);
t_bool			get_pwd(t_data *dt);
t_bool			get_home(t_data *dt);
t_bool			get_path(t_data *dt);

/*error env*/
void			set_err_env_01(t_err *err);
void			set_err_env_02(t_err *err);
void			set_err_env_03(t_err *err);
void			set_err_env_04(t_err *err);

#endif