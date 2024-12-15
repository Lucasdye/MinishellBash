/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshl_redir.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:48:03 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/21 14:51:56 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHL_REDIR_H
# define MSHL_REDIR_H

# define FDNONE "-"
# define FDIN "0"
# define FDOUT "1"
# define FDERR "2"
# define MSHL_DEF_FD0NAME "/dev/stdin"
# define MSHL_DEF_FD1NAME "/dev/stdout"
# define MSHL_DEF_FD2NAME "/dev/stderr"

typedef struct s_data	t_data;
typedef struct s_exec	t_exec;

typedef enum e_fd_redir
{
	fdnone = -1,
	fdin,
	fdout,
	fdderr
}	t_fd_redir;

/* enumateur de type de redirection */
typedef enum e_redir_op
{
	none,
	redir_l,
	redir_r,
	redir_inp,
	redir_app,
	redir_pipe,
	redir_rp,
	redir_s_inp,
	redir_movin,
	redir_movout,
	redir_rw,
	redir_s_app,
}	t_redir_op;

typedef enum e_flag
{	
	NONE,
	WRITE,
	CLOSE,
	READ,
	APPEND,
	TRUNC
}	t_flag;

typedef struct s_std
{
	int	in;
	int	out;
}	t_std;

typedef struct s_her
{
	t_pipe	pipe;
	char	*eof;
	int		*fd;
	t_bool	isquote;
	size_t	idx;
	t_bool	ks_sigc_her;
	t_bool	enc_hd;
}	t_her;

typedef struct s_redir
{
	char		*str;
	size_t		size;
	t_bool		ks;
	t_flag		flg;
	char		*rdr;
	t_bool		opt;
}	t_redir;

/* redir utils */
t_bool	init_std(t_data *dt);
t_bool	backup_std(t_data *dt);
t_bool	restore_std(t_data *dt);
t_bool	ft_redir_input(t_data *dt, size_t idx, t_flag flag);
t_bool	ft_redir_output(t_data *dt, size_t idx, t_flag flag);

/* heredoc utils*/
//t_bool	heredoc(t_data *dt, int fd, char *var_name);
t_bool	heredoc(t_data *dt, int fd, char *var_name, int *fdin);
t_bool	ft_set_heredoc(t_data *dt, register size_t idx);
t_bool	ft_exp_heredoc(t_data *dt, char **s1);
void	close_fd_hd(t_data *dt, t_pipe p);
void	close_fd_hd_tab(t_data *dt);
t_bool	chk_eof(t_data *dt, char *eof);
t_bool	ft_here_pipe(t_data *dt);
void	ft_err_doc(t_data *dt, int fd);
void	set_err_eof(t_data *dt);
void	print_err_doc_exit(char *eof);
void	close_all_her_fds(t_data *dt, t_exec *exec);
void	close_all_her_fds_but_current(t_data *dt, t_exec *exec);

/*redir exec*/
t_bool	set_fds_intro(t_data *dt, t_exec *exec);
t_bool	set_fds_outro(t_data *dt, t_exec *exec);

/*fd utils */
t_bool	ft_init_tab_hd_fd(t_data *dt);
t_bool	close_fd(t_data *dt, int fd);
t_bool	close_fd_all(t_data *dt, t_pipe p);

/*dup utils*/
t_bool	dup_src_fd(t_data *dt, int *fd, const int src);
t_bool	dup_src_fd_noc(t_data *dt, int *fd, const int src);
t_bool	dup2_src_fd(t_data *dt, int *fd, const int src);
t_bool	dup2_src_fd_noc(t_data *dt, int *fd, const int src);
t_bool	ft_dup2(t_data *dt, t_exec *exec);
#endif
