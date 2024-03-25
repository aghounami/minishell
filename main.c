#include "minishell.h"

char *check_state(t_elem *elem)
{
    char *state = NULL;
    if (elem->state == IN_DQUOTE)
        state = "IN_DOUBLE_QUOTE";
    else if (elem->state == IN_QUOTE)
        state = "IN_QUOTE";
    else if (elem->state == GENERAL)
        state = "GENERAL";
    return (state);
}

char *find_token(t_elem *elem)
{
    char *str = NULL;
    if (elem->token == WORD)
        str = "WORD";
    else if (elem->token == WHITE_SPACE)
        str = "WHITE_SPACE";
    else if (elem->token == NEW_LINE)
        str = "NEW_LINE";
    else if (elem->token == QOUTE)
        str = "QOUTE";
    else if (elem->token == DOUBLE_QUOTE)
        str = "DOUBLE_QUOTE";
    else if (elem->token == ESCAPE)
        str = "ESCAPE";
    else if (elem->token == ENV)
        str = "ENV";
    else if (elem->token == PIPE_LINE)
        str = "PIPE_LINE";
    else if (elem->token == REDIR_IN)
        str = "REDIR_IN";
    else if (elem->token == REDIR_OUT)
        str = "REDIR_OUT";
    else if (elem->token == HERE_DOC)
        str = "HERE_DOC";
    else if (elem->token == DREDIR_OUT)
        str = "DREDIR_OUT";
    return (str);
}

int print_lex(t_elem *elem)
{
    printf("|                                         LEXER                                     |\n");
    printf("-------------------------------------------------------------------------------------\n");
    printf("|   Content          |   Length   |        state          |          token          |\n");
    printf("-------------------------------------------------------------------------------------\n");
    while (elem)
    {
        char *token = find_token(elem);
        char *state = check_state(elem);
        elem->len = strlen(elem->content);
        printf("|   '%s'     |    %d    |            %s          |           %s            \n", elem->content, elem->len, state, token);
        printf("-------------------------------------------------------------------------------------\n");
        elem = elem->next;
    }
    return (0);
}

void sig_handler(int signo)
{
    if (signo == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

int main(int argc, char **argv, char **env)
{
    char *line;
    t_command *command;
    t_elem *pars = NULL;
    int flag = 0;
    (void)argv;
    (void)argc;
    command = NULL;
    rl_catch_signals = 0;
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
    while (1)
    {
        pars = NULL;
        line = readline("\033[0;32m➜ minishell ~ \033[0m");
        if (line && line[0] != '\0')
        {
            lexer(line, &pars);
            state(&pars);
            syntax_error(&pars, &flag);
            // print_lex(pars);
            if (flag == 0)
            {
                // stack_env(&pars, env);
                stack_command(pars, &command, env);
                while (command != NULL)
                {
                    printf("command->cmd = [%s]\n", command->cmd);
                    for (int i = 0; command->args[i] != NULL; i++)
                        printf("arg      :[%s]\n", command->args[i]);
                    printf ("--\n");
                    command = command->next;
                }
                command = NULL;
                // if (strncmp(command->cmd, "echo", 4) == 0)
                // {
                //     if (i > 2 && strncmp(command->args[2], "-n", 2) == 0)
                //     {
                //         int i = 3;
                //         while (command->args[i] && (strncmp(command->args[i], "-n" , 2) == 0 || strncmp(command->args[i], " " , 2) == 0))
                //             i++;
                //         while (command->args[i])
                //         {
                //             if (strncmp(command->args[i], "-n", 2) != 0)
                //                 printf("%s", command->args[i]);
                //             i++;
                //         }
                //         printf("");
                //     }
                //     else
                //     {
                //         for (int i = 2; command->args[i] != NULL; i++)
                //             printf("%s", command->args[i]);
                //         printf("\n");
                //     }
                // }
            }
            flag = 0;
        }
        else if (!line)
        {
            printf("exit\n");
            exit(0);
        }
        add_history(line);
    }
    return (0);
}
