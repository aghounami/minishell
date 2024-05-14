/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:52:51 by hel-magh          #+#    #+#             */
/*   Updated: 2024/05/12 11:51:00 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	terrible(char c)
{
	return (c == '_' );
}

int	equal(char c)
{
	return (c == '=');
}

int	plus(char c)
{
	return (c == '+');
}

int	string_chcker(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) || terrible(str[i]))
	{
		while (str[i])
		{
			if ((str[i + 1] != '\0' && plus(str[i])
					&& !equal(str[i + 1])))
				return(0);
			else if (ft_isalpha(str[i]) || ft_isdigit(str[i])
				|| plus(str[i]) || equal(str[i])
				|| terrible(str[i]))
				i++;
			else
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

void	ft_adder(t_env **envex, char *str, char *value)
{
	t_env	*adder;

	adder = *envex;
	while (adder)
	{
		if (ft_strncmp(str, adder->vari, ft_strlen(adder->vari)) == 0)
		{
			adder->q = 1;
			free(adder->value);
			adder->value = ft_strdup(value);
		}
		adder = adder->next;
	}
}

char	*list_check(t_env **envex, char *str)
{
	t_env	*check;
	int		i;

	check = *envex;
	i = ft_strlen(check->vari);
	while (check)
	{
		if (check->vari && ft_strncmp(check->vari, str, i) == 0)
			return ("");
		check = check->next;
	}
	return (NULL);
}

int	double_check(char *str)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == '+')
			pos++;
		if (pos > 1)
			return (0);
		i++;
	}
	return (1);
}


void	export_printer(t_env **env)
{
	t_env	*p;

	p = *env;
	while (p)
	{
		if (p->q == 1 && p->value != NULL)
			printf("declare -x %s=\"%s\"\n", p->vari, p->value);
		else
			printf("declare -x %s\n", p->vari);
		p = p->next;
	}
}

int	cheking(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (plus(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	problem(char *str)
{
	printf("export: `%s': not a valid identifier\n", str);
}

void fc(char **value, char **vari, int *len, char *str)
{
	(*value) = ft_strdup(ft_strstr(str, "=") + 1);
	(*len) =  ft_strlen(str) - ft_strlen((*value)) - 1;
	(*vari) = ft_substr(str, 0, (*len));
}
int	v_check(char *str)
{
	t_exec	var;
	int		i;

	i =0;
	ft_memset(&var, 0, sizeof(var));
	if (ft_strchr(str, '='))
	{
		i = 1;
		var.value = ft_strstr(str, "=") + 1;
		var.len = ft_strlen(str) - ft_strlen(var.value) - 1;
		var.vari = ft_substr(str, 0, var.len);
	}
	else
		var.vari = ft_strdup(str);
	if ((string_chcker(var.vari) && double_check(var.vari)))
	{
		if (i)
			free(var.vari);
		return (1);
	}
	free(var.vari);
	return (problem(str), 0);
}
// char *value_add(char *str)
// {
// 	int i;
// 	int j;
// 	char *d;

// 	(1) && (i = -1, j = 0);
// 	while(str[++i])
// 	{
// 		if (str[i] == '"')
// 			j++;
// 	}
// 	d = malloc(sizeof(char) * (i+j+1));
// 	if (!d)
// 		return(NULL);
// 	(1) && (i = -1, j = 0);
// 	while(str[++i])
// 	{
// 		if (str[i] == '"')
// 			d[j++] ='\\';
// 		d[j++] = str[i];
// 	}
// 	d[j] = '\0';
// 	return(d);
// }
void	ft_ex_filler(char *str, t_exec *var, t_env **ev)
{
	if (ft_strchr(str, '='))
	{
		fc(&var->value, &var->vari, &var->len, str);
		// var->value = value_add(ft_strstr(str, "=") + 1);
		if (var->vari[ft_strlen(var->vari) - 1] == '+')
		{
			var->vari = ft_substr(str, 0, ft_strlen(var->vari) - 1);
			if (list_check(ev, var->vari))
				var->value = ft_strjoin(list_check(ev, var->vari), var->value);
		}
		if (!list_check(ev, var->vari))
			ft_lstadd_back_exec(ev, ft_lstnew_exec(var->value, var->vari, 1));
		else
			ft_adder(ev, str, var->value);
	}
	else
	{
		if (cheking(str))
			return (problem(str));
		var->vari = ft_strdup(str);
		if (!list_check(ev, var->vari))
			ft_lstadd_back_exec(ev, ft_lstnew_exec("", var->vari, 0));
	}
		(free(var->value), free(var->vari));
}

void	ft_export(t_command **command, t_env **envex)
{
	t_command	*exp;
	t_exec		var;
	int			f;
	int			j;

	ft_memset(&var, 0, sizeof(var));
	exp = *command;
	f = 1;
	while (exp->args[f])
	{
		j = 0;
		if (v_check(exp->args[f]))
				ft_ex_filler(exp->args[f], &var, envex);
		f++;
	}
	if (!exp->args[1])
		export_printer(envex);
}
