/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:12:41 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/13 14:15:05 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_get_env(char **env, t_env **env_list)
{
	int i;
	char	**str;

	i = 0;
	while (env[i])
	{
		str = ft_split_typecont(env[i]);
		ft_lstadd_back(env_list, ft_lstnew(str[1], str[0]));
		i++;
	}
	return ;
}

int	ft_env(t_env *env_list)
{
	while (env_list)
	{
		printf("%s", env_list->type);
		printf("=");
		printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
	g.exit_status = EXIT_SUCCESS;
	return (1);
}
