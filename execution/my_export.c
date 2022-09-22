/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:29:25 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/22 22:12:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	export_checkpathname(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 65 && str[i] <= 90) && !(str[i] >= 97
				&& str[i] <= 122) && str[i] != '_' && str[i] != ' ')
		{
			ft_putstr_fd("export: '", str, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", NULL, STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

int	export_ifexists(char *name, char *path, t_env **env)
{
	int		i;
	t_env	*lst;

	i = 0;
	lst = *env;
	while (lst)
	{
		if (ft_strncmp(name, lst->name, ft_strlen(name)) == 0)
		{
			if (path[0] == 0)
				return (1);
			free(lst->path);
			lst->path = ft_strdup(path);
			free(name);
			free(path);
			return (1);
		}
		i++;
		lst = lst->next;
	}
	return (0);
}

int	export_checkav(char *str, char **ptr, int n)
{
	if (n == NAME)
		return (export_checkname(str));
	else
	{
		if (str[0] == 0)
		{
			ptr[1] = NULL;
			return (1);
		}
		return (2);
	}
	return (1);
}

int	ft_export(t_env **env, t_exec *line)
{
	if (!line->argv[1])
		return (ft_env(*env, EXP));
	export_addvar(line->argv, env);
	return (1);
}
