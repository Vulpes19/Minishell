/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:01:08 by abaioumy         #+#    #+#              */
/*   Updated: 2022/09/25 19:07:26 by abaioumy        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	export_checkop(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
		{
			if (str[i + 1])
			{
				ft_putstr_fd("export: not valid in this context\n",
					NULL, STDERR_FILENO);
				return (EXIT_SUCCESS);
			}
		}
		i++;
	}
	return (EXIT_FAILURE);
}

void	ft_check_cmd(t_cmd *cmd, t_env **env_list)
{
	int	fds[2];
	int	in;

	in = 0;
	fds[0] = 0;
	fds[1] = 1;
	if (!cmd)
		return ;
	if (cmd->type != PIPE)
	{
		handle_one_command(cmd, env_list);
		return ;
	}
	ft_start_pipe(cmd, &in, fds, env_list);
	if (fds[1] != 1)
		close(fds[1]);
	if (in != 0)
		close(in);
}
