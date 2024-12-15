/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:51:09 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/07 15:44:23 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	ft_set_prompt_head(t_data *dt)
{
	if (set_str_arg(&dt->err, &dt->var.prompt_head, dt->var.user) == true)
		return (true);
	dt->var.prompt_head = ft_strjoin_m(dt->var.prompt_head, "@");
	if (dt->var.prompt_head != NULL)
	{
		dt->var.prompt_head = ft_strjoin_m(dt->var.prompt_head,
				dt->var.hostname);
		if (dt->var.prompt_head != NULL)
		{
			dt->var.prompt_head = ft_strjoin_m(dt->var.prompt_head, ":");
			if (dt->var.prompt_head != NULL)
				return (false);
		}
	}
	set_err_std_02(&dt->err);
	return (true);
}

static t_bool	ft_set_prompt_end(t_data *dt)
{
	t_bool	ks;

	ks = true;
	if (set_str_arg(&dt->err, &dt->var.prompt, dt->var.prompt_head) == true)
		return (true);
	dt->var.prompt = ft_strjoin_m(dt->var.prompt, dt->var.pwd);
	if (dt->var.prompt != NULL)
	{
		dt->var.prompt = ft_strjoin_m(dt->var.prompt, MSHL_DLG_PROMPT);
		if (dt->var.prompt != NULL)
			ks = false;
	}
	if (ks == true)
	{
		set_err_std_02(&dt->err);
		return (true);
	}
	return (false);
}

t_bool	ft_set_prompt(t_data *dt, t_ptype type)
{
	if (dt->var.prompt != NULL)
		free_str(&dt->var.prompt);
	if (type == p_posix)
	{
		if (set_str_arg(&dt->err, &dt->var.prompt, MSHL_DLG_PROMPT_PX) == true)
			return (true);
		if (dt->var.p_prnt != NULL)
			free(dt->var.p_prnt);
		set_str_arg(&dt->err, &dt->var.p_prnt, MSHL_DLG_PRINT_PX);
	}
	else
	{
		if (ft_set_prompt_end(dt) == true)
			return (true);
		if (dt->var.p_prnt != NULL)
			free(dt->var.p_prnt);
		set_str_arg(&dt->err, &dt->var.p_prnt, MSHL_DLG_PRINT);
	}
	return (false);
}
