#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "./libft/libft.h"

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
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
};


typedef struct s_command
{
	char	*cmd;
	char	**args;
	char	*redir_in;
	char	*redir_out;
	char	*here_doc;
	char	*dredir_out;
	int		pipe;
	int		redir;
	struct s_command	*next;
}	t_command;

typedef struct s_elem
{
	char			    *content;
	int				    len;
	enum e_state	state;
    struct s_elem	*next;
	enum e_token	token;
	struct s_elem	*prev;
}	t_elem;

typedef struct s_lexer
{
	int i;
	int j;
	char *str;
	t_elem *prev;
}	t_lexer;

// lexer
void		*lexer(char *line, t_elem **elem);
void		case_escape(char *line, t_elem **elem, t_lexer *lexer);
void		case_herdoc_or_redir(char *line, t_elem **elem, t_lexer *lexer);
void		case_word(char *line, t_elem **elem, t_lexer *lexer);
void		case_redirect(char *line, t_elem **elem, t_lexer *lexer);
void		case_dollar(t_lexer *lexer, t_elem **elem, char *line);
void		case_one_char(t_lexer *lexer, t_elem **elem, char *line, int type);
void		state(t_elem **elem);
// utils
t_elem		*lstnew(void *content, int token , t_elem **prev);
t_elem		*lstlast(t_elem *lst);
void		lstadd_back(t_elem **lst, t_elem *new);
void		syntax_error(t_elem **elem , int *flag);
void		stack_command(t_elem *elem, t_command **command, char **env);
t_command	*lstnew_command(char **agrs, char *cmd);
void		lstadd_back_command(t_command **lst, t_command *new);
void		stack_env(t_elem **elem, char **env);
// --------------------------------



// executers
void		exec_check(t_command **command);

#endif