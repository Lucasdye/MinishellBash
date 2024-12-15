/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshl_signal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:40:19 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/09 16:34:57 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHL_SIGNAL_H
# define MSHL_SIGNAL_H

# include <signal.h>

typedef struct s_data	t_data;

void		handle_sig(int n_sig);
void		ft_handle_sig(int n_sig);
void		ft_heredoc_sig(int n_sig);
void		ft_init_sig(t_bool flg, t_bool src);

#endif
