/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 00:50:00 by jveuille          #+#    #+#             */
/*   Updated: 2023/09/09 14:33:47 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_bool	ft_flag_set(t_read *rd, t_buff_fd *bf, int fd)
{
	if (rd->ks_lf == true)
	{
		rd->ks_new_ln = true;
		if (bf->buff[fd].ks_end_bf == true)
			bf->buff[fd].ks_new_bf = true;
	}
	else if (bf->buff[fd].ks_end_bf == true)
	{
		rd->ks_flow = true;
		bf->buff[fd].ks_new_bf = true;
		rd->ks_new_ln = false;
	}
	if (rd->rtline.str == NULL)
		return (true);
	return (false);
}

static t_bool	ft_feed_str(t_read *rd, t_buff_fd *bf, int fd)
{
	t_bool	ks_ret;

	if (rd->ks_new_ln == true)
	{	
		rd->rtline.str = ft_calloc_m((rd->line.size + 1), sizeof(char));
		if (rd->rtline.str == NULL)
			return (true);
		rd->rtline.size = 0;
		rd->rtline.ptr = 0;
		rd->rtline.size = ft_strlcat_obj(rd->rtline, rd->line,
				rd->line.size + 1);
		rd->ks_new_ln = false;
	}
	else
	{
		rd->rtline = ft_strjoin_obj(rd->rtline, rd->line);
		if (rd->rtline.str == NULL)
			return (true);
	}
	ks_ret = ft_flag_set(rd, bf, fd);
	if (ks_ret == true)
		return (true);
	return (false);
}

static t_bool	ft_read_line(t_read *rd, t_buff_fd *bf, int fd)
{
	t_bool	ks_ret;

	while (rd->ks_lf == false && bf->buff[fd].ks_end_bf == false)
	{
		rd->ks_lf = false;
		rd->line = ft_strdup_m(bf->buff[fd].s_buff,
				'\n', bf->buff[fd].s_idx, bf->buff[fd].bt_rd);
		if (rd->line.str == NULL)
			return (true);
		bf->buff[fd].s_idx = rd->line.ptr;
		if (rd->line.str[rd->line.size - 1] == '\n')
			rd->ks_lf = true;
		if (bf->buff[fd].s_idx == (size_t)(bf->buff[fd].bt_rd))
			bf->buff[fd].ks_end_bf = true;
		ks_ret = ft_feed_str(rd, bf, fd);
		free(rd->line.str);
		if (ks_ret == true)
			return (true);
	}
	return (false);
}

static t_bool	ft_read(t_read *rd, t_buff_fd *bf, int fd)
{
	t_bool	ks_ret;

	while (rd->ks_flow == true)
	{
		rd->ks_flow = false;
		if (bf->buff[fd].ks_new_bf == true)
		{
			bf->buff[fd].bt_rd = read(fd, bf->buff[fd].s_buff, BUFFER_SIZE);
			bf->buff[fd].ks_end_bf = false;
			if (bf->buff[fd].bt_rd == ERR)
				return (true);
			else if (bf->buff[fd].bt_rd == 0)
			{
				if (rd->rtline.size == 0)
					return (true);
				return (false);
			}
			bf->buff[fd].s_idx = 0;
			bf->buff[fd].ks_new_bf = false;
		}
		ks_ret = ft_read_line(rd, bf, fd);
		if (ks_ret == true)
			return (true);
	}
	return (false);
}

char	*get_next_line(int fd)
{
	static t_buff_fd	bf;
	t_read				rd;
	t_bool				ks_ret;

	rd.ks_flow = true;
	rd.ks_new_ln = true;
	rd.ks_lf = false;
	rd.rtline.size = 0;
	if ((fd < 0) || (fd > FD_MAX) || (BUFFER_SIZE == 0))
		return (NULL);
	if (bf.buff[fd].ks_fd_use == false)
	{
		bf.buff[fd].ks_fd_use = true;
		bf.buff[fd].ks_new_bf = true;
		bf.buff[fd].ks_end_bf = false;
	}
	ks_ret = ft_read(&rd, &bf, fd);
	if (ks_ret == true)
	{
		bf.buff[fd].ks_fd_use = false;
		return (NULL);
	}
	return (rd.rtline.str);
}
