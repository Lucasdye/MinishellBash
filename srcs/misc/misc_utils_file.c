/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:14:09 by jveuille          #+#    #+#             */
/*   Updated: 2023/10/25 08:14:21 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_t_file(t_file *file)
{
	file->pathname = NULL;
	file->name = NULL;
	file->path = NULL;
	file->ext = NULL;
	return ;
}

void	ft_free_t_file(t_file *file)
{
	if (file->pathname != NULL)
		free(file->pathname);
	if (file->name != NULL)
		free(file->name);
	if (file->path != NULL)
		free(file->path);
	if (file->ext != NULL)
		free(file->ext);
	return ;
}

t_bool	ft_get_file_info(t_file *file)
{
	register int	i;
	register int	j;
	register int	k;
	register int	len_s;

	i = 0;
	j = 0;
	k = 0;
	if (!file->pathname)
		return (true);
	len_s = ft_strlen(file->pathname);
	while ((i <= len_s) && (file->pathname[len_s - i] != '.'))
		i++;
	while (((i + j) <= len_s) && (file->pathname[len_s - i - j] != '/'))
		j++;
	while (((i + j + k) <= len_s))
		k++;
	file->path = ft_substr(file->pathname, 0, k);
	file->name = ft_substr(file->pathname, k, (j - 1));
	file->ext = ft_substr(file->pathname, (k + j), (i - 1));
	if ((file->path == NULL) || (file->name == NULL) || (file->name == NULL))
		return (true);
	return (false);
}

static t_kstr	ft_core_path(t_data *dt, t_file *file, t_kstr chk)
{
	if (ft_get_file_info(file) == true)
	{
		set_err_std_01(&dt->err);
		chk.ks = true;
	}
	if (chk.ks == false)
	{
		if (set_str_arg(&dt->err, &chk.str, file->path) == true)
			chk.ks = true;
	}
	ft_free_t_file(file);
	return (chk);
}

t_kstr	ft_get_path(t_data *dt, char *pathname)
{
	t_file	file;
	t_kstr	chk;

	chk.ks = false;
	chk.str = NULL;
	ft_init_t_file(&file);
	if (!pathname)
	{
		set_err_std_02(&dt->err);
		chk.ks = true;
	}
	else
	{
		if (set_str_arg(&dt->err, &file.pathname, pathname) == true)
		{
			chk.ks = true;
			return (chk);
		}
		chk = ft_core_path(dt, &file, chk);
	}
	return (chk);
}
