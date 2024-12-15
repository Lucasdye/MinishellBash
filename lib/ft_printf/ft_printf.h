/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:25:35 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/04 12:52:16 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef LIBFT_H
#  include "../../includes/libft.h"
# endif

# ifndef PERR_MODE
#  define PERR_MODE	0
# elif PERR_MODE < 0 || PERR_MODE > 1
#  undef PERR_MODE
#  define PERR_MODE  0
# endif

/* standard library */

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <limits.h>

/* constant boolean */

# ifndef FALSE
#  define FALSE 0
# endif
# ifndef TRUE
#  define TRUE 1
# endif
# ifndef EOF
#  define EOF -1
# endif

/* Buffert */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# elif BUFFER_SIZE <= 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# ifndef NBR_FUNC
#  define NBR_FUNC 9
# endif

/**/
typedef struct s_chk_spec
{
	char	kstate;
	size_t	idx_tab;
}	t_chk_spec;

typedef struct s_exit
{
	char	ks_err;
	char	*str;
}	t_exit;

typedef struct s_print
{
	va_list				arg;
	char				ks_ctrl_err;
	char				ks_ctrl_flow;
	char				ks_flg_spc;
	char				t_spc;
	char				prev_flg_spc;
	char				*str_num;
	size_t				len_s;
	char				*str_tmp;
	char				char_tmp[2];
	ssize_t				char_count;
	char				*str_buff;
	size_t				size_buff;
	size_t				idx_buff;
	char				sharp;
	char				minus;
	char				plus;
	char				space;
	char				zero;
	char				dot;
	size_t				nbr_prec;
	char				ks_padd;
	size_t				nbr_padd;
	char				char_padd;
	int					outprint;
	t_exit				exit;
}	t_print;

/**/
typedef t_print	(*t_func_spec_conv)(t_print str);

typedef struct s_func_spec
{
	t_print				(*func)(t_print str);
}	t_func_spec;

typedef struct s_func_tab
{
	t_func_spec_conv	func_conv[NBR_FUNC];
}	t_func_tab;

/*main*/
int			ft_printf(const char *format, ...);
t_exit		ft_sprintf(const char *format, ...);
t_func_tab	ft_fill_func_tab(void);
char		set_exit_str(t_print *dt);

/*pseudo function*/
t_print		ft_fac_format_c(t_print str);
t_print		ft_fac_format_str(t_print str);
t_print		ft_fac_format_prt(t_print str);
t_print		ft_fac_format_dint(t_print str);
t_print		ft_fac_format_int(t_print str);
t_print		ft_fac_format_uint(t_print str);
t_print		ft_fac_format_xhex(t_print str);
t_print		ft_fac_format_mxhex(t_print str);
t_print		ft_fac_format_perc(t_print str);

/* format */
t_print		ft_format_c(char str, t_print t_str);
t_print		ft_format_str(char *str, t_print t_str);
t_print		ft_format_perc(void);
t_print		ft_format_hex(register unsigned long num, t_print t_str);
t_print		ft_format_hex_ptr(register unsigned long num, t_print t_str);
t_print		ft_format_int(register int num, t_print t_str);
t_print		ft_flag_uint(register unsigned int num, t_print t_str);

/* util */
t_print		ft_buffer(t_print t_str, char *add_str);
t_print		ft_buffer_c(t_print t_str, char add_c);
t_print		fill_str_to_char(t_print t_str, char format);
char		*ft_strcat(char *dest, char *src);
char		*ft_upcase_str(char *s_num);
int			ft_abs(int nbr);
void		set_exit_err(t_print *dt);
void		mem_free(t_print *dt);

/* conversion */
char		ft_spec_flag(char str);
char		*ft_rev_char_tab(char *tab, int size);
t_chk_spec	ft_spec_conv(char str);

/* bonus */
void		ft_init_struct(t_print *dt);
t_print		ft_flag_check(t_print str);
t_print		ft_flag_check_minus(t_print str);
t_print		ft_padding(t_print str, char kssg);
t_print		ft_fill_zero(t_print str);

#endif 
