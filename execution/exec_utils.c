/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:08:57 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/16 02:43:58 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_isdir(char *cmd)
{
	struct stat	path_stat;

	stat(&cmd[2], &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

void	ft_check_cmd(t_cmd *cmd, t_env **env_list)
{
	if (cmd == NULL)
		return ;
	if (cmd->type == EXEC)
		ft_exec((t_exec *)cmd, env_list);
	if (cmd->type == REDIR)
		if (ft_redirect((t_redir *)cmd, env_list) == -1)
			return ;
	if (cmd->type == PIPE)
		ft_pipes((t_pipe *)cmd, env_list);
}

char	*exec_ifaccess(char *cmd)
{
	char	**path;
	char	*join;
	int		i;

	i = 0;
	path = ft_find_path();
	while (path[i])
	{
		join = ft_strjoin(path[i], cmd);
		if (access(join, X_OK) == 0)
		{
			ft_free_doubleptr(path);
			g.exit_status = EXIT_SUCCESS;
			return (join);
		}
		free(join);
		i++;
	}
	return (NULL);
}
