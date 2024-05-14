#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#include <dirent.h>
# include "./libf/libft.h"

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};

enum e_token
{ 
	WORD = -1,
	WHITE_SPACE = ' ',
	QOUTE = '\'',
	SLASH = '/',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
	BACK_SLASH,
	NEW_WORD,
};

enum e_new_token
{
	YES = 1,
	NO = 0,
};

typedef struct s_redirection
{
	int		redir_in;
	int		redir_out;
	int		here_doc;
	int		dredir_out;
}	t_redirection;

typedef struct s_command
{
	char	*cmd;
	char	**args;
	char	**redirection;
	int		redir_in;
	int		redir_out;
	int		here_doc;
	int		dredir_out;
	int		pipe;
	int		redir;
	char 	*exec_path;
	char	*content;
	char	**evr;
	struct s_command	*next;
	int					check_expand;
}	t_command;

typedef struct s_env
{
	struct s_env	*next;
	char *value;
	char *vari;
	int	i;
	int q;

}	t_env;


typedef struct s_exec
{
	int index;
	int i;
	int j;
	int len;
	char *name;
	char *value;
	char *vari;
	char **spl;
	char *path_in;
    char **path_split;
    char *current_dir;
    char *path;
    char *exec_path;

} t_exec;


typedef struct s_elem
{
	char			*content;
	int				len;
	enum e_state	state;
    struct s_elem	*next;
	enum e_token	token;
	struct s_elem	*prev;
	enum e_new_token	flag_env;
	char			*env_var;
	int					expand;
}	t_elem;

typedef struct s_lexer
{
	int i;
	int j;
	char *str;
	int				quote;
	int				d_quote;
	int 			here_doc;
	t_elem *prev;
	char *var_name;
}	t_lexer;

typedef struct s_cmd_utils
{
	int i;
	int index;
}	t_cmd_utils;

// lexer
void		*lexer(char *line, t_elem **elem, char **env);
void		case_escape(char *line, t_elem **elem, t_lexer *lexer);
void		case_herdoc_or_redir(char *line, t_elem **elem, t_lexer *lexer);
void		case_word(char *line, t_elem **elem, t_lexer *lexer);
void		case_redirect(char *line, t_elem **elem, t_lexer *lexer);
void		case_dollar(t_lexer *lexer, t_elem **elem, char *line, char **env);
void		case_one_char(t_lexer *lexer, t_elem **elem, char *line, int type);
void		state(t_elem **elem, char **env);
void		new_linked_list(t_elem **pars, t_elem **list);
// utils
void		syntax_error(t_elem **elem , int *flag);
void		stack_command(t_elem *elem, t_command **command, char **env);
void		without_quote(t_elem **elem, t_command **command, char **env, t_cmd_utils **utils);
void		with_d_quote(t_elem **elem, t_command **command, int *i, char **env);
void		with_quote(t_elem **elem, t_command **command, int *i);
void		stack_env(t_elem *elem, char **env);
char		*get_env(char *str, char **env);
void		ft_free_lexer(t_elem **pars);
void		ft_free_command(t_command **command);
void		case_single_quote(t_elem **tmp, char *str, t_elem **list);
void		case_double_quote(t_elem **tmp, char *str, t_elem **list);

// --------------------------------

// linked_list
t_command	*lstnew_command(t_command **new, int pipe, t_redirection *redir);
void		lstadd_back_command(t_command **lst, t_command *new);
t_elem		*lstnew(void *content, int token);
void		lstadd_back(t_elem **lst, t_elem *new);
t_elem		*lst_new(char *content, int token, int state, int flag_env);
void		ft_lstadd_back_new_list(t_elem **alst, t_elem *new);
t_elem		*lstlast(t_elem *lst);



// executers
char **exec_check(t_command **command, char **av);
void exec_path(t_command **command);
void cd_checker(t_command **command);
void ft_exit_fail(char *str);
char *get_env_exec(t_command **command);
void	ft_free_double(char **str);
void	ft_exit_fail(char *str);
int	command_check(t_command **command, t_env **envex);
void	ft_pwd(void);
void	ft_exit_mini(t_command **command);
void	ft_env(t_env **envex);
void	ft_echo(t_command **command);
void	ft_export(t_command **command, t_env **envex);
int ft_equal_finder(char *str);
t_env	*ft_lstnew_exec(char *value, char *variable, int i);
void	ft_lstadd_back_exec(t_env **lst, t_env *neww);
t_env	*ft_lstlast_exec(t_env *lst);
void	ft_lstdelone_exec(t_env *lst);
char	*ft_strstr(const char *s1, const char *s2);
void	search_exec(t_command **command, t_exec *execution);
void	one_cmd(t_command **commands, int pid, t_env **envex, char **env);
void	ft_unset(t_command **command, t_env **envexx);
void	ft_filler(t_env **env, char **envar);
void execution_cmd(t_command **commands, char **env, t_env **envex, int fd);
int	redire(t_command **command);
int	string_chcker(char *str);
int	terrible(char c);
int	equal(char c);
int	plus(char c);


#endif