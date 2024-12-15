/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 00:56:00 by jveuille          #+#    #+#             */
/*   Updated: 2023/09/09 14:33:02 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef LIBFT_H
#  include "../includes/libft.h"
# endif

/* standard library */
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>

/* constant boolean */
# ifndef ERR
#  define ERR -1
# endif

/* Buffert */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE  64
# elif BUFFER_SIZE <= 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE  0
# endif

# ifdef FD_MAX
#  undef FD_MAX
# endif
# define FD_MAX 1024

/* */
typedef struct s_dup
{
	char	*str;
	size_t	size;
	size_t	ptr;
}	t_dup;

/* table of  buffer */
typedef struct s_obj_buff
{
	t_bool		ks_fd_use;
	t_bool		ks_new_bf;
	t_bool		ks_end_bf;
	ssize_t		bt_rd;
	size_t		s_idx;
	char		s_buff[BUFFER_SIZE];
}	t_obj_buff;

typedef struct s_buff_fd
{
	t_obj_buff	buff[FD_MAX];
}	t_buff_fd;

/* control of  read function */
typedef struct s_read
{
	t_bool		ks_flow;
	t_bool		ks_lf;
	t_bool		ks_new_ln;
	t_dup		line;
	t_dup		rtline;
	int			mc_count;
}	t_read;

/*main*/
char	*get_next_line(int fd);

/* util */
void	*ft_calloc(size_t elcount, size_t elsize);
char	*ft_strchr_m(const char *s, int c, size_t s_idx_init, size_t s_idx_max);
t_dup	ft_strdup_m(const char *s, int c, size_t s_idx_init, size_t s_idx_max);
size_t	ft_strlcat_obj(t_dup dst, const t_dup src, size_t size);
t_dup	ft_strjoin_obj(t_dup const s1, t_dup const s2);

#endif
