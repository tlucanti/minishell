#ifndef PARSER_H
# define PARSER_H
#define PIPE_OUT	0
#define PIPE_IN		1

#define STDIN		0
#define STDOUT		1

#define OUT_APPEND	(char *)1
#define OUT_WRITE	(char *)2
#define HEREDOC		(char *)3
#define INPUT		(char *)4
#define PIPE		(char *)5
#define UNO_QUOTE	(char *)6
#define DBL_QUOTE	(char *)7

void	print_my_cool_split(char **p);
int		ft_strhaschr(const char *str, int ch);
char	**ft_split_special(char const *s, int (*f)(int));
char	*ft_strjoin_s1free(char const *s1, char const *s2);
char	 *get_all_env(char *arr);
void 	expand_env(char **arr);
int		complex_parser(const char *input);
#endif
