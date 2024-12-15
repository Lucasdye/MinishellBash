/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshl_rule.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:03:21 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/15 16:15:51 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHL_RULE_H
# define MSHL_RULE_H

typedef struct s_data	t_data;

/* main function */
t_bool	ft_check_rules(t_data *dt);
t_bool	ft_parse_bad_pipe_02(t_data *dt, register size_t i);
t_bool	ft_parse_bad_str(t_data *dt, register size_t i);
t_bool	ft_parse_bad_03(t_data *dt, register size_t	i, t_redir_op n_rp);
t_bool	ft_parse_miss_file_01(t_data *dt, register size_t i);
t_bool	ft_parse_miss_file_02(t_data *dt, register size_t i);
t_bool	ft_check_err_parse(t_data *dt);

/*error util token & redir*/
void	ft_set_err_parse_01(t_data *dt, char s1);
void	ft_set_err_parse_02(t_data *dt, t_bool opt, t_redir_op n_redir);
void	ft_set_err_parse_03(t_data *dt, t_sep_op n_sep);
void	ft_set_err_parse_04(t_data *dt, char *prev);
void	ft_set_err_parse_05(t_data *dt, char *s1);

#endif