/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshl_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:44:01 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/20 17:35:19 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHL_EXEC_H
# define MSHL_EXEC_H

# define CD 1
# define ECHO 2
# define EXIT 3
# define PWD 4
# define CUR_DIR "./"

typedef struct s_data	t_data;

typedef int				t_fd[2];

typedef struct s_fi
{
	int		pipe_fds[2];
	char	*delimiter;
}	t_fi;

typedef struct s_io
{	
	t_her	hd;
	int		in_start;
	int		out_start;
	int		in_curr_fd;
	int		out_curr_fd;
	int		in_std;
	int		out_std;
	int		in_heredoc;
	int		backup_in;
	int		backup_out;
	int		pipe_fds[2];
	int		old_pipe_in;
}	t_io;

typedef struct s_exec
{
	t_io		io;
	int			count_bloc;
	int			exit_code;
	int			signal_code;
	int			nb_blocs;
	int			status;
	int			idx;
	int			idx_pid;
	t_bool		flg_hd;
}	t_exec;

/* main  exec function */
void	init_struct_hd_exec(t_data *dt);
void	init_exec(t_tk_tab *tk, t_exec *exec);
t_bool	exec_redir_hd(t_data *dt);
t_bool	exec(t_data *dt, t_tk_tab *tk);
t_bool	exec_subshell(t_data *dt, t_tk_tab *tk, t_exec *exec);
char	**ft_merge_path_cmd(t_data *dt, char **paths, char *cmd);
t_bool	ft_execve(t_data *dt, char *cmd, char **arg);
t_bool	exec_mini(t_data *dt, char **var, char *cmd, char **arg);

/*exec utils*/
//void	clear_first_elem(char *str);
void	set_idx_to_bloc(t_tk_tab *tk, t_exec *exec);
void	set_idx_to_cmd(t_tk_tab *tk, t_exec *exec);
void	ft_waitpid(t_data *dt, t_exec *exec);
t_bool	is_shell(t_tk_tab *tk, t_exec *exec);
t_bool	is_pipe(t_tk_tab *tk);
int		count_blocs_in_command_line(t_tk_tab *tk);
t_bool	redirections_loop(t_data *dt, t_tk_tab *tk, t_exec *exec);

/* exec error */
t_bool	set_err_cmd_01(t_data *dt, char *cmd);
void	set_err_cmd_02(t_data *dt);
t_bool	set_err_cmd_03(t_data *dt, char *cmd);
#endif
