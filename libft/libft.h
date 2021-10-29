/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:08:10 by tlucanti          #+#    #+#             */
/*   Updated: 2021/10/29 18:29:46 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <zconf.h>
# include <stdlib.h>
# include <unistd.h>
# define NULLPTR 0

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

unsigned char	*ft_memset_fast(unsigned char *s, size_t xlen,
					unsigned long long cccc);
void			ft_memcpy_fast_fwd(unsigned char **dst, unsigned char **src,
					size_t xlen);
void			ft_memcpy_fast_bkw(unsigned char **dst, unsigned char **src,
					size_t xlen);
void			*ft_memchr_fast(unsigned char **ptr, unsigned char ch,
					size_t xlen);
int				ft_memcmp_fast(unsigned char **s1, unsigned char **s2,
					size_t xlen);
int				ft_64cmp_fast(unsigned long long *s1_ll,
					unsigned long long *s2_ll);
int				ft_8cmp_fast(unsigned long long s1_ll,
					unsigned long long s2_ll);
size_t			ft_strnlen(const char *s, size_t maxlen);
long long		ft_maxl(long long a1, long long a2);
int				ft_max(int __a1, int __a2);
long long		ft_minl(long long __a1, long long __a2);
int				ft_min(int __a1, int __a2);
size_t			ft_absl(size_t __a);
int				ft_abs(int __a);
int				ft_isspace(int __c);
int				ft_isdigit(int __c);
int				ft_isupper(int __c);
int				ft_islower(int __c);
int				ft_isalpha(int __c);
int				ft_isalnum(int __c);
int				ft_isascii(int __c);
int				ft_isprint(int __c);
int				ft_toupper(int __c);
int				ft_tolower(int __c);
long long		ft_atol(const char *str);
double			ft_atod_noexp(const char **str, double *sgn);
double			ft_powd_fast(double n, int exp);
double			ft_atod_frac(const char **str);
char			**ft_str_append_sized(char **arr, char *str, size_t size,
					size_t arrlen);
char			**ft_push_back_char_ss(char **arr, char *new_s, size_t arrlen);
char			**ft_error_test_ft_split(char **ret);
void			*ft_arr_clear(char **arr);
int				ft_digit_num(int n);
int				ft_lstpushfront(t_list **lst, void *content);
t_list			*ft_lstend(t_list *lst);
int				ft_lstpushback(t_list **lst, void *content);
void			ft_lstfree(t_list *lst);
int				ft_free(void *ptr);

void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t maxlen);
int				ft_atoi(const char *str);
double			ft_atod(const char *str);
float			ft_atof(const char *str);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *s);

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, int (*f)(int));
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new_l);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new_l);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
void			*xmalloc(size_t size);

#endif // LIBFT_H
