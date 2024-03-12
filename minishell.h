#ifndef MINISHELL_H
# define MINISHELL_H

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
	NEW_LINE = '\n',
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

typedef struct s_elem
{
	char			    *content;
	int				    len;
	char				*type;
	enum e_state	state;
    struct s_elem	*next;
    struct s_elem	*prev;
	enum e_token	token;
	char *command;
	char *option;
}	t_elem;

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

void *lexer(char *line, t_elem **elem);
t_elem	*lstnew(void *content, int token);
t_elem    *lstlast(t_elem *lst);
void	lstadd_back(t_elem **lst, t_elem *new);
void    state(t_elem **elem);

#endif