/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshl_builtin.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:33:33 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/20 15:20:07 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHL_BUILTIN_H
# define MSHL_BUILTIN_H

# define  MSHL_ECHO_OPT	"neE"

typedef struct s_data	t_data;

/* builtin function */
int			ft_echo(t_data *dt, char **var_name);
int			ft_cd(t_data *dt, char **var_name);
int			ft_pwd(t_data *dt, char **var_name);
int			ft_exit(t_data *dt, char **var_name);
int			ft_unset_env(t_data *dt, char **var_name);
int			ft_export_env(t_data *dt, char **var_name);
int			ft_env(t_data *dt, char **var_name);

/* builtin util */
t_chk_str	chk_def_dir(t_data *dt, t_err *err, char **dir, char **cdir);
t_bool		try_set_parent_dir(t_data *dt, char **dir, t_err *err);

/* builtin error */
void		set_err_cd_01(t_err *err);
void		set_err_cd_02(t_err *err);
void		set_err_cd_03(t_err *err);
#endif
