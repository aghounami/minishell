/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:23:41 by aghounam          #+#    #+#             */
/*   Updated: 2024/06/04 17:11:10 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <dirent.h>
# include "./libf/libft.h"

int	g_catch;

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};

typedef struct s_entier
{
	int			i;
	int			j;
	int			k;
	int			n;
}	t_entier;

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
	int					redir_in;
	int					redir_out;
	int					here_doc;
	int					dredir_out;
}	t_redirection;

typedef struct s_command
{
	char				*cmd;
	char				**args;
	char				**rdrect;
	int					redir_in;
	int					redir_out;
	int					here_doc;
	int					dredir_out;
	int					pipe;
	int					redir;
	char				*exec_path;
	char				*content;
	char				**evr;
	int					f;
	int					fd;
	int					ex;
	struct s_command	*next;
	int					check_expand;
	int					hrdoc_nbr;
}	t_command;

typedef struct s_env
{
	struct s_env		*next;
	char				*value;
	char				*vari;
	int					i;
	int					q;
	int					empty;
}	t_env;

typedef struct s_varr
{
	char				**envp;
	char				*line;
	int					a;
	int					b;
	int					flag;
	int					enp;
	int					nbr_hdoc;
}	t_varr;

typedef struct s_exec
{
	int					index;
	int					i;
	int					j;
	int					n;
	int					len;
	int					status;
	int					flag;
	int					*pid;
	int					fd;
	int					fd2[2];
	char				*name;
	char				*value;
	char				*vari;
	char				**spl;
	char				*path_in;
	char				**path_split;
	char				**name2;
	char				*current_dir;
	char				*path;
	char				*exec_path;
	char				*tmp;
	char				*t_path;
	char				*new;
}	t_exec;

typedef struct s_elem
{
	char				*content;
	int					len;
	enum e_state		state;
	struct s_elem		*next;
	enum e_token		token;
	struct s_elem		*prev;
	enum e_new_token	flag_env;
	char				*env_var;
	int					expand;
	int					e_status;
	int					i;
	int					j;
	int					k;
}	t_elem;

typedef struct s_lexer
{
	int					i;
	int					j;
	char				*str;
	int					quote;
	int					d_quote;
	int					here_doc;
	t_elem				*prev;
	char				*var_name;
	int					export;
	int					in_hrdc;
}	t_lexer;

typedef struct s_cmd_utils
{
	int					i;
	int					index;
	int					fd;
	int					ambigous;
}	t_cmd_utils;

// lexer
void		*lexer(char *line, t_elem **elem, char **env, int flag);
void		case_escape(char *line, t_elem **elem, t_lexer *lexer);
void		case_herdoc_or_redir(char *line, t_elem **elem, t_lexer *lexer);
void		case_word(char *line, t_elem **elem, t_lexer *lexer);
void		case_redirect(char *line, t_elem **elem, t_lexer *lexer);
void		case_dollar(t_lexer *lexer, t_elem **elem, char *line, char **env);
void		case_one_char(t_lexer *lexer, t_elem **elem, char *line, int type);
void		state(t_elem **elem, char **env, int flag);
void		new_linked_list(t_elem **pars, t_elem **list);
char		*ft_join(char const *s1, char const *s2);
int			check_if_pipe_line_first(t_elem **elem);
void		malloc_fail(void);

// utils
int			syntax_error(t_elem **elem, int *nbr_hdoc);
void		stack_command(t_elem *elem, t_command **command, char **env);
void		without_quote(t_elem **elem, t_command **command, \
	t_cmd_utils **utils);
void		stack_env(t_elem *elem, char **env, int flag);
char		*get_env(char *str, char **env);
void		ft_free_lexer(t_elem **pars);
void		ft_free_command(t_command **command);
void		case_single_quote(t_elem **tmp, t_elem **list);
void		case_double_quote(t_elem **tmp, t_elem **list);
void		special_case(t_elem **tmp, t_elem **list, char *tmp_str);
void		next_case(char *line, t_elem **elem, t_lexer *lexer);
int			exit_status(int status);
int			next_cnd_special(t_elem **tmp, char **tmp_str, int *k);
int			next_cnd(t_elem **tmp, char **tmp_str);
int			break_case(t_elem **tmp, t_elem **list, char **tmp_str, int k);
void		open_herdoc(t_command **command, char **envp, int *nbr_hdoc);
void		expanding(char **line, char **envp, int *fd2, t_command *cmd);
void		check_dlmtr(char **line, int fd2, t_command *cmd, int i);
void		over_write(t_elem **elem, char **line);
void		empty_line(t_varr **var);
void		free_all(t_elem **list, t_command **command, t_varr **var);
void		empty_env(t_varr **var);

// --------------------------------

// linked_list
t_command	*lstnew_command(t_command **new, int pipe);
void		lstadd_back_command(t_command **lst, t_command *new);
t_elem		*lstnew(void *content, int token);
void		lstadd_back(t_elem **lst, t_elem *new);
t_elem		*lst_new(char *content, int token, int state, int flag_env);
void		ft_lstadd_back_new_list(t_elem **alst, t_elem *new);
t_elem		*lstlast(t_elem *lst);
char		**ft_strdup_2d(char **str);
int			count_worlds(char *str);

// executers
char		**exec_check(t_command **command, char **av, int enp);
void		cd_checker(t_command **command, t_env **envex);
void		ft_exit_fail(char *str);
char		*get_envx(char *str, t_env **env);
void		ft_free_double(char **str);
void		ft_exit_fail(char *str);
int			command_check(t_command **command, t_env **envex);
void		ft_pwd(void);
void		ft_exit_mini(t_command **command);
void		ft_env(t_env **envex);
void		ft_echo(t_command **command);
void		ft_export(t_command **command, t_env **envex);
t_env		*ft_lstnew_exec(char *value, char *variable, int i);
void		ft_lstadd_back_exec(t_env **lst, t_env *new);
t_env		*ft_lstlast_exec(t_env *lst);
void		ft_lstdelone_exec(t_env *lst);
char		*ft_strstr(const char *s1, const char *s2);
void		one_cmd(t_command **commands, int pid, t_env **envex, char **env);
void		ft_unset(t_command **command, t_env **envexx);
void		ft_filler(t_env **env, char **envar);
void		execution_cmd(t_command **command, char **env, t_env **envex);
int			redire(t_command **command);
int			string_chcker(char *str);
int			herdoc(t_command **command, char **envp, int i, int pid);
void		sig_handler_her(int signo);
void		pwd_update(t_env **env, char *str);
void		fill_ter(char **str, t_env **envex, int l);
void		sig_handler(int signo);
char		**refiller(char **env, t_env **envex);
int			getcwd_check(t_command **command, t_exec *dir_cd, char *path, \
	t_env **envex);
int			path_cheker_cd(char *path, t_env **envex);
int			cd_dir(const char *path);
void		error_printer(char *str, char *str2, int i);
void		cd_changer(char **path, t_env **envex);
int			string_chcker(char *str);
void		ft_adder(t_env **envex, char *str, char *value);
char		*list_check(t_env **envex, char *str);
int			double_check(char *str);
void		export_printer(t_env **env);
void		problem(char *str);
int			cheking(char *str);
void		not_found(char *str);
void		search(t_command **command, t_exec *ex);
void		search_2(t_command **command, t_exec *ex);
int			search_3(t_command **command, t_exec *ex);
void		search_exec_2(t_command **command, t_env **env);
int			ft_lstsize_ex(t_command *lst);
void		ex_cmd(t_command **command, t_exec *ex, t_env **envex);
void		child_ex(t_command **command, t_exec *ex, t_env **envex, \
	char **env);
void		parent_ex(t_command **command, t_exec *ex, t_env **envex);
void		waiter(t_exec *ex);
void		execution_cmd(t_command **command, char **env, t_env **envex);
void		er_print(char *str, char *str2, int i);
#endif