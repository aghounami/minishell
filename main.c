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

int main(int argc, char **argv, char **envp)
{
    char *line;
    t_command *command;
    t_elem *pars = NULL;
    int flag = 0;
    (void)argv;
    (void)envp;
    (void)argc;
    command = malloc(sizeof(t_command));
    command->cmd = ft_strdup("");
    command->args = malloc(sizeof(char *) * 100);
    while (1)
    {
        pars = NULL;
        line = readline("\033[0;32m ➜ minishell ~ \033[0m");
        if (line && line[0] != '\0')
        {
            lexer(line, &pars);
            state(&pars);
            syntax_error(&pars, &flag);
            // print_lex(pars);
            if (flag == 0)
            {
                stack_command(pars, &command);
                // printf("command->cmd = [%s]\n", command->cmd);
               
                // for (int i = 0; command->args[i] != NULL; i++)
                //     printf("arg      :[%s]\n", command->args[i]);
                if (strncmp(command->cmd, "echo", 4) == 0)
                {
                    for (int i = 1; command->args[i] != NULL; i++)
                        printf("%s", command->args[i]);
                    printf("\n");
                }
                command->cmd = "";
            }
            flag = 0;
        }
        else if (!line)
            exit(0);
        add_history(line);
    }
    return (0);
}
// args = ft_split(line, ' ');
// if (args[0] != NULL)
// {
//     if (strcmp(args[0], "exit") == 0)
//     {
//         free(line);
//         free(args);
//         exit(0);
//     }
//     else if (strcmp(args[0], "cd") == 0)
//     {
//         if (args[1] == NULL)
//             chdir(getenv("HOME"));
//         else
//             chdir(args[1]);
//     }
//     else
//     {
//         pid_t pid = fork();
//         if (pid == 0)
//         {
//             execvp(args[0], args);
//             perror("minishell");
//             exit(1);
//         }
//         else
//             wait(NULL);
//     }
// }