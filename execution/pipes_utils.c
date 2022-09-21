/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:04:38 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:10 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ft_check_type(t_cmd *cmd, t_env **env_list, int n)
{
	if (cmd->type == EXEC)
		return (1);
	if (cmd->type == REDIR)
	{
		ft_redirect((t_redir *)cmd, env_list);
		return (2);
	}
	if (cmd->type == PIPE && n == 1)
	{
		ft_pipes((t_pipe *)cmd, env_list);
		return (0);
	}
	return (0);
}

static int	access_checktype(t_cmd *cmd, int n)
{
	if (cmd->type == EXEC)
		return (1);
	if (cmd->type == REDIR)
		return (0);
	if (cmd->type == PIPE && n == 1)
		return (0);
	return (0);
}

int	pipes_fork_left(t_pipe *pipes, int *fds, t_env **env_list)
{
	int	pid;
	int	iff;

	pid = 1;
	iff = 0;
	if (access_checktype((t_cmd *)pipes->left, 0))
		pipes_access((t_exec *)pipes->left);
	iff = ft_check_type((t_cmd *)pipes->left, env_list, 0);
	if (iff != 2 && iff == 1)
		pid = fork();
	if (pid == -1)
	{
		perror("fork");
		g_var.exit_status = EXIT_FAILURE;
		return (-1);
	}
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		ft_exec_nofork((t_exec *)pipes->left, env_list);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	pipes_fork_right(t_pipe *pipes, int *fds, t_env **env_list)
{
	int	pid;
	int	iff;

	iff = 0;
	pid = 1;
	if (access_checktype((t_cmd *)pipes->right, 1))
		pipes_access((t_exec *)pipes->right);
	iff = ft_check_type((t_cmd *)pipes->right, env_list, 1);
	if (iff != 2 && iff == 1)
		pid = fork();
	if (pid == -1)
	{
		perror("fork");
		g_var.exit_status = EXIT_FAILURE;
		return (-1);
	}
	if (pid == 0)
	{
		close(fds[1]);
		dup2(fds[0], 0);
		close(fds[0]);
		ft_exec_nofork((t_exec *)pipes->right, env_list);
		exit(EXIT_FAILURE);
	}
	return (0);
}
