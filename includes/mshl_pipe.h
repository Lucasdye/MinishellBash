/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshl_pipe.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:48:03 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/31 13:36:08 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHL_PIPE_H
# define MSHL_PIPE_H

typedef struct s_data	t_data;

typedef struct s_pipe
{
	int		fd[2];
}	t_pipe;

typedef struct s_bk
{
	t_bool	ks;
	t_pipe	*pipe;
	int		*pid;
}	t_bk;

/* pipe utils */
t_bool	init_t_bk(t_data *dt, size_t count);
t_bool	create_pipe_u(t_data *dt, size_t idx);
t_bool	create_t_pipe(t_data *dt, t_pipe *p);
void	close_pipe(t_data *dt, size_t idx);
t_bool	pipe_cmd(t_data *dt, t_idx *tk, size_t count);
void	status_child(int status);

void	free_bk(t_data *dt);

#endif
