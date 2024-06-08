/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:38:37 by hel-magh          #+#    #+#             */
/*   Updated: 2024/06/05 15:02:17 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	string_chcker(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		while (str[i])
		{
			if ((str[i + 1] != '\0' && str[i] == '+'
					&& str[i + 1] != '='))
				return (0);
			else if (ft_isalpha(str[i]) || ft_isdigit(str[i])
				|| str[i] == '+' || str[i] == '='
				|| str[i] == '_')
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
			free(adder->vari);
			adder->vari = ft_strdup(str);
			free(adder->value);
			adder->value = ft_strdup(value);
			break ;
		}
		adder = adder->next;
	}
}

char	*list_check(t_env **envex, char *str)
{
	t_env	*check;

	check = *envex;
	while (check)
	{
		if (check->vari && (ft_strlen(check->vari) == ft_strlen(str)) \
			&& ft_strncmp(check->vari, str, ft_strlen(str)) == 0)
			return (check->value);
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
	int		a;

	p = *env;
	if (!p)
		return ;
	a = p->empty;
	while (p)
	{
		if (p->q == 1 && p->value != NULL)
		{
			if (a == 0)
				printf("declare -x %s=\"%s\"\n", p->vari, p->value);
			else
				if (ft_strncmp("PATH", p->vari, ft_strlen(p->vari)) != 0)
					printf("declare -x %s=\"%s\"\n", p->vari, p->value);
		}
		else
			printf("declare -x %s\n", p->vari);
		p = p->next;
	}
}
