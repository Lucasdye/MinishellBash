/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshl_file.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:50:05 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/04 15:28:08 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHL_FILE_H
# define MSHL_FILE_H

typedef struct s_data	t_data;

/* file utils */
t_bool	file_ops(t_data *dt, const char *pathname, int *fd, t_flag action);
void	close_file(t_data *dt);
t_bool	ft_get_file_info(t_file *file);
t_kstr	ft_get_path(t_data *dt, char *pathname);
t_bool	ft_path_join(t_data *dt, char **dest, char **s1);

#endif