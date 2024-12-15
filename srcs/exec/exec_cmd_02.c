/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 09:21:37 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 07:46:01 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clean_path_cmd_01(char **cmd)
{
	register int	i;

	i = 0;
	while ((*cmd)[i] != '\0' && ((*cmd)[i] == DOT))
		i++;
	if ((i == 1) && ((*cmd)[i] == '/'))
		ft_memmove(&(*cmd)[0], (&(*cmd)[i + 1]), (ft_strlen(*cmd) - i));
	return ;
}

t_bool	ft_clean_path_cmd_02(t_data *dt, t_chk_str *chk, char *cmd)
{
	register int	i;

	i = 0;
	while (cmd[i] != '\0' && (cmd[i] == DOT))
		i++;
	if ((i == 1) && (cmd[i] == '/'))
	{
		set_err_cmd_01(dt, cmd);
		chk->ks = true;
		return (true);
	}
	return (false);
}

static t_bool	ft_join_path_cmd(t_data *dt, char ***fpaths, char **paths
	, char *cmd)
{
	register int	i;
	char			*s_tmp;

	i = 0;
	s_tmp = NULL;
	s_tmp = ft_strjoin_m(s_tmp, ft_strdup("/"));
	s_tmp = ft_strjoin_m(s_tmp, cmd);
	if (s_tmp == NULL)
	{
		free(*fpaths);
		set_err_std_01(&dt->err);
		return (true);
	}
	while (paths[i] != NULL)
	{	
		(*fpaths)[i] = ft_strjoin(paths[i], s_tmp);
		i++;
	}
	free(s_tmp);
	return (false);
}

char	**ft_merge_path_cmd(t_data *dt, char **paths, char *cmd)
{
	int		size;
	char	**fpaths;

	size = 0;
	if (paths != NULL)
		size = ft_tablen(paths);
	fpaths = ft_calloc((size + 1), sizeof(char *));
	if (fpaths == NULL)
	{
		set_err_std_01(&dt->err);
		return (NULL);
	}
	if (paths != NULL)
	{
		if (ft_join_path_cmd(dt, &fpaths, paths, cmd) == true)
			return (NULL);
	}
	return (fpaths);
}
