/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:44:30 by abaioumy          #+#    #+#             */
/*   Updated: 2022/08/15 16:07:30 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_pwd(t_exec *line)
{
	char	*s;
	char	*ret;

	s = NULL;
	ret = getcwd(s, PATH_MAX);
	if (line->argv[1])
	{
        g.exit_status = EXIT_FAILURE;
		ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (ret == NULL)
	{
		perror("pwd");
		g.exit_status = EXIT_FAILURE;
		return (1);
	}
	printf("%s\n", ret);
	g.exit_status = EXIT_SUCCESS;
	return (1);
}
