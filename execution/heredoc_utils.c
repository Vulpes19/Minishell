/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:10:51 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/21 18:30:35 by abaioumy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>

static	char	*heredoc_normalcase(char *line, char *str)
{
	line = ft_strjoin(line, "\n");
	str = ft_strjoin(str, line);
	return (str);
}

void	heredoc_writefile(char *delimiter, int fd, t_env **env_list)
{
	t_write	w;

	w.line = NULL;
	w.ret = NULL;
	w.str = NULL;
	w.index = -1;
	while (TRUE)
	{
		w.line = readline(YELLOW"heredoc> " RESET);
		if (!w.line)
			break ;
		if (ft_strcmp(w.line, delimiter) == 0)
		{
			free(w.line);
			break ;
		}
		w.index = heredoc_findsign(w.line);
		if (w.index != -1)
			heredoc_specialcase(&w, env_list);
		else
			w.str = heredoc_normalcase(w.line, w.str);
	}
	ft_putstr_fd(w.str, NULL, fd);
	free(w.str);
}
