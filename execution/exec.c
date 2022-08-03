/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:47:51 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/03 22:22:30 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "exec.h"

void	ft_check_cmd(t_cmd *cmd)
{
	if (cmd->type == EXEC)
		ft_exec((t_exec *)cmd);
}

void	ft_exec(t_exec *line)
{
	char **path;
	char *cmd;
	int	i;
	int	exit_status;

	i = 0;
	path = ft_find_path();
	cmd = ft_strdup(line->argv[0]);
	cmd = ft_strjoin("/", cmd);
	if (fork() == 0)
	{	while (path[i])
		{
			if (access(ft_strjoin(path[i], cmd), X_OK) == 0)
			{
				execve(ft_strjoin(path[i], cmd), line->argv, NULL);
				perror("execve");
				break ;
			}
		i++;
		}
	}
	wait(&exit_status);
	return ;
}