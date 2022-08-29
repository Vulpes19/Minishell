/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:58:53 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/29 02:18:49 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>

void	ft_redirect(t_redir *redir, char **env, t_env **env_list)
{
	int		fd_file;
	t_exec	*ex;
	int		pid;

	ex = (t_exec *)redir->cmd;
	// printf("redir->file: %s\n", redir->file);
	fd_file = open(redir->file, redir->mode, 0644);
	if (fd_file < 0)
	{
		ft_putstr_fd("no such file or directory: ", redir->file, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		g.exit_status = EXIT_NOTFOUND;
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		dup2(fd_file, redir->fd);
		ft_exec_nofork(ex, env, env_list);
		ft_putstr_fd(ex->argv[0], ": command not found\n", STDERR_FILENO);
		close(fd_file);
		exit(EXIT_FAILURE);
	}
	close(fd_file);
	wait(&g.exit_status);
	if (g.exit_status == 256)
		g.exit_status = EXIT_NOTFOUND;
	else
		g.exit_status = 0;
}
