/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:40:32 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 13:14:20 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_H
# define BASE_H

/* standard library */
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>

# ifndef ERR
#  define ERR -1
# endif

/* Buffert */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# elif BUFFER_SIZE <= 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE  0
# endif

# ifndef ALL
#  define ALL 0
# endif

# ifndef SPACE
#  define SPACE "\x20"
# endif

typedef unsigned long long	t_lsize_t;
typedef long long			t_lssize_t;

typedef struct s_chars
{
	char	*str;
	size_t	size;
}	t_chars;

/*file struct */
typedef struct s_file
{
	int		fd;
	char	*pathname;
	char	*name;
	char	*path;
	char	*ext;
}	t_file;

void	ft_free_t_file(t_file *file);
void	ft_init_t_file(t_file *file);

#endif