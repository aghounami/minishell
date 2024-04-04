/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:52:51 by hel-magh          #+#    #+#             */
/*   Updated: 2024/04/03 17:58:33 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// khass ikon awal 7aref alpaghbet tab3o alpha numerikm or '_'
// kha ikon = awla +=
// ila knet += kan9alab wax kayen ila kan kandir lih join ila makanex kandzido;

// void ft_check_exist(t_command **command, t_)
// {
	
// }
int plus_equal(char c)
{
	return( c == '+' || c == '=');
}

int string_chcker(char *str)
{
	int i;
	
	i =0;
	if(ft_isalpha(str[0]) )
	{
		while(str[i])
		{
			if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || plus_equal(str[i]))
				i++;
			else
				return (0);
		}
		
	}
	else
		return (0);
	return (1);
}
int list_vcheck(t_env **envex, char *str)
{
    t_env *check;
    check = *envex;
    int i = ft_strlen(str);
    while (check)
    {
        if (check->variable && ft_strncmp(check->variable, str, i) == 0)
			 return (1);
        check = check->next;
    }
    return (0);
}

char *list_check(t_env **envex, char *str)
{
    t_env *check;
    check = *envex;
    int i = ft_strlen(str);
    while (check)
    {
        if (check->variable && ft_strncmp(check->variable, str, i) == 0)
			 return (check->value);
        check = check->next;
    }
    return (NULL);
}

void ft_export(t_command **command)
{
	t_command	*exp;
	static t_env *envex = NULL ;
	t_env		*envexeex;
	t_exec		var;
	static int 	i ;

	ft_memset(&var, 0, sizeof(var));
	exp = *command;

	
	if(!envex)
	{
		
		while(exp->evr[var.i])
		{
			var.value = ft_strstr(exp->evr[var.i], "=") + 1;
			var.len = ft_strlen(exp->evr[var.i]) - ft_strlen(var.value) - 1;
			var.variable = ft_substr(exp->evr[var.i], 0 ,var.len);
			if(i == 0)
			{
				envex = ft_lstnew_exec(var.value, var.variable);
				i = 1;
			}
			else
				ft_lstadd_back_exec(&envex, ft_lstnew_exec(var.value, var.variable));

			var.i++;
		}
		
	}
	int f =1;
	int s =0;
	
	
	while(exp->args[f])
	{
		if(string_chcker(exp->args[f]) )
		{
			
			 s = 0;
			if(ft_strstr(exp->args[f], "="))
			{	
				var.value = ft_strstr(exp->args[f], "=") + 1;
				var.len = ft_strlen(exp->args[f]) - ft_strlen(var.value) - 1;
				var.variable = ft_substr(exp->args[f], 0 ,var.len);
				if(var.variable[ft_strlen(var.variable) - 1] == '+')
				{
					var.variable = ft_substr(exp->args[f], 0 ,ft_strlen(var.variable) - 1);
					if(list_check(&envex, var.variable))
						var.value = ft_strjoin(list_check(&envex, var.variable), var.value);
					
				}
				if(!list_check(&envex, var.variable))
					ft_lstadd_back_exec(&envex, ft_lstnew_exec(var.value, var.variable));
				else
				{
					envexeex = envex;
					while(envexeex)
					{
						if (ft_strncmp(exp->args[f], envexeex->variable, ft_strlen( envexeex->variable)) == 0)
						{
							envexeex->value = var.value;
						}
							envexeex = envexeex->next;
					}
				}
					
			}
			else
			{
				envexeex = envex;
				while(envexeex)
				{
					if (ft_strncmp(exp->args[f], envexeex->variable, ft_strlen( envexeex->variable)) == 0)
					{
						break ;
						s =1;
					}
						envexeex = envexeex->next;
				}
				if(s == 0)
				{
					var.variable = exp->args[f];
					if(!list_check(&envex, var.variable))
						ft_lstadd_back_exec(&envex, ft_lstnew_exec("", var.variable));
					
				}
			}
		f++;
		}
		else
		{
			printf("export: `%s': not a valid identifier\n", exp->args[f]);
			break ;
		}
	}
	
	if(!exp->args[1])
	{
		
		envexeex = envex;
		while(envexeex)
		{
			if(envexeex->variable)
				printf("%s=\"%s\"\n", envexeex->variable, envexeex->value);
			envexeex = envexeex->next;
		}
	}
	
}



