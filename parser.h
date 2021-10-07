#ifndef PARSER_H
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

typedef struct	s_list
{
	char			**args;
	int				len;
	char 			*token;
	int				pipe[2];
	struct s_list	*previous;
	struct s_list	*next;
}				t_list;

char		*ft_strcpy(char *dest, const char *src);
char			*ft_strdup(const char *src);
int		ft_strhaschr(const char *str, int ch);
char	*ft_strjoin_s1free(char const *s1, char const *s2);
static char *make_dollar_great_again(char *src);
static int is_token(char *arr);
static int is_env_token(int c);
char *get_all_env(char *arr);
void expand_env(char **arr);
int	not_so_simple_parser(const char *input);
void setup_pipeline(t_list **pipeline,	char **arr);
#endif
