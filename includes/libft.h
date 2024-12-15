/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveuille <jveuille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:12:33 by jveuille          #+#    #+#             */
/*   Updated: 2023/11/17 11:16:28 by jveuille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BASE_H
#  include "../includes/base.h"
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>

# ifndef FALSE
#  define FALSE 0
# endif
# ifndef TRUE
#  define TRUE 1
# endif

# ifndef SIZE_MAX
#  define SIZE_MAX UINT_MAX
# endif

/* fac similis boolean type */
typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_idx
{
	size_t		start;
	size_t		end;
}	t_idx;

typedef struct s_chk_str
{
	t_bool		ks;
	size_t		idx;
}	t_chk_str;

typedef struct s_chk_str_e
{
	t_bool		ks;
	t_chk_str	s;
}	t_chk_str_e;

typedef struct s_str
{
	char	*str;
	size_t	size;
	size_t	idx;
}	t_str;

typedef struct s_res
{
	t_bool	ks;
	void	*ret;
}	t_res;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// isxx func
int			ft_isalnum(int c);
t_bool		ft_isalnum_var(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_ishexa(int c);
int			ft_isprint(int c);
int			ft_iswhite_space(char str);

// mem func
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t number, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memcpy_idx(void *dest, const void *src, size_t idx, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

// char func
int			ft_toupper(int c);
int			ft_tolower(int c);

// string func
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strcpy(char *dest, const char *src);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *str);
void		ft_putchar(char c);
void		ft_putstr(char *str);
void		ft_putnbr(int nb);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *str, const char *sbstr, size_t len);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
t_bool		ft_strjcat(char **dst, char *src);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t len);
size_t		ft_skip_whitespace(const char *str, register size_t idx);
t_chk_str	ft_skip_whitespace_s(const char *str, register size_t idx);
char		*ft_trim_white_space(char *src);
char		*ft_clean_white_space(char *src);

// pointer func
void		ft_striteri(char *s, void (*f)(unsigned int, char*));

// num func
int			ft_atoi(const char *nptr);
int			ft_atoi_m(const char *nptr);
long		ft_atol(const char *nptr);
double		ft_atof(const char *nptr);
int			ft_atoh(const char *nptr);
char		*ft_itoa(int n);
char		*ft_ftoa(double n, unsigned int p);
char		*ft_lltoa( t_lssize_t n);

//list func
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
int			ft_lstsize(t_list *lst);

#endif
