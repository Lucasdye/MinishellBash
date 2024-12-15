/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshl_expand.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:58:47 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/12 15:22:27 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHL_EXPAND_H
# define MSHL_EXPAND_H

typedef struct s_exp_var
{
	t_bool	ks;
	t_bool	ks_ls;
	t_bool	ks_end_s;
	t_dup	s;
	t_dup	s_var;
	t_dup	s_line;
	t_dup	s_tmp;
}	t_exp_var;

/* main expand */
t_bool	ft_expand(t_data *dt);
t_bool	ft_expand_cmd(t_data *dt, register size_t idx);
t_bool	ft_exp_core_var(t_data *dt, char **s1);
t_bool	ft_exp_str(t_data *dt, char **str, char ***tab_sb);
t_bool	ft_set_tk_arg_tab(t_data *dt, char ***tab_s, register size_t idx);
t_bool	ft_expand_exitcode(t_data *dt, char **s1);
t_bool	ft_expand_path(t_data *dt, char **dest, char *src, register size_t idx);
t_bool	ft_expand_path_01(t_data *dt, char **dest, register size_t idx);
t_bool	ft_expand_var(t_data *dt, char *str, register size_t idx);
t_bool	ft_expand_arg_redir(t_data *dt, t_token *tk);
t_bool	ft_set_white_space_str(t_data *dt, t_exp_var *sd);
t_bool	ft_order_arg_cmd(t_data *dt, register size_t idx);

/* mem utils */
void	init_exp_data(t_exp_var *sd);
void	free_obj(t_dup *dest);
void	free_all_obj(t_exp_var *sd);

/* string utils */
t_bool	ft_var_read(t_data *dt, char **s1);
t_bool	ft_var_read_line(t_exp_var *sd, t_dup *dest, t_dup *src);
t_dup	ft_var_dup(const char *s, register size_t s_idx_init,
			register size_t s_idx_max);
char	**ft_split_str_wp(char const *s);
char	**ft_split_str_qt(char const *s);
void	ft_len_count( t_quote *qt, const char *str, size_t *len_s, size_t i);
#endif 
