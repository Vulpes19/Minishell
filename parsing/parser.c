/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaioumy <mbaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:51:27 by mbaioumy          #+#    #+#             */
/*   Updated: 2022/09/05 22:25:00 by mbaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parse.h"
#include <unistd.h>

int	num_words(char *str, int quote_flag)
{
	int		words;
	char	**split;
	int		i;

	words = 1;
	i = 0;
	if (quote_flag)
		split = ft_split(str, ' ');
	else
	{
		split = ft_split_quotes(str, ' ');
	}
	while(split[i++])
		words++;
	return (words);
}

int	is_whitespace(char *str, char *es)
{
	char	*whitespaces;
	int		i;
	int		j;

	whitespaces = ft_strdup("\n\t\r\v ");
	i = 0;
	es = NULL;
	while (str[i])
	{
		j = 0;
		while (whitespaces[j])
		{
			if (whitespaces[j] == str[i])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

t_cmd	*ft_parse_heredoc(char **ps, t_env **env_list, t_cmd *cmd, char **env)
{
	while (next(ps, "<<"))
	{
		get_token(ps, 0);
		ft_heredoc(env_list, cmd, env);
	}
	return (cmd);
}

t_cmd	*parseexec(char **ps, t_env_p *env_list, char **env)
{
	char	*q;
	int		tok;
	int		argc;
	t_exec	*cmd;
	int		words;
	t_cmd	*ret;
	char	**split;
	t_env	**env_lst;

	env_lst = malloc(sizeof(t_env **));
	if (*ps[0] == '"')
		words = num_words(*ps, 0);
	else
		words = num_words(*ps, 1);
	ret = execcmd(words);
	cmd = (t_exec *)ret;
	argc = 0;
	ret = parseredir_test(ret, ps, env_list, env);
	while (!next(ps, "|") && !next(ps, "<<"))
	{
		tok = get_token(ps, &q);
		// printf("tok: %c\n", tok);
		if (tok == 0 || tok == 'H')
			break ;
		split = ft_split(q, ' ');
		if (tok != 'c')
			printf("syntax error\n");
		// printf("q: %s\n", q);
		cmd->argv[argc] = ft_string_examiner(split[0], env_list);
		// printf("cmd: %s\n", cmd->argv[argc]);
		argc++;
		if (argc >= words || split[1] == NULL)
			break ;
		ret = parseredir_test(ret, ps, env_list, env);
	}
	cmd->argv[argc] = NULL;
	return (ret);
}

t_cmd	*parseredir_test(t_cmd *cmd, char **ps, t_env_p *env_list, char **env_arr)
{
	int		tok;
	char	*q;
	char	**split;
	t_env	**env;

	env = malloc(sizeof(t_env **));
	if (next(ps, "<>") && !next(ps, "<<"))
	{
		tok = get_token(ps, 0);
		if (get_token(ps, &q) != 'c')
		{
			ft_putstr_fd("syntax error\n", NULL, STDERR_FILENO);
			cmd->type = 0;
			return (cmd);
		}
		split = ft_split(q, ' ');		
		if (tok == '<')
			cmd = redircmd_test(cmd, parseredir_test(cmd, ps, env_list, env_arr), split[0], O_RDONLY, STDIN_FILENO);
		else if (tok == '>')
			cmd = redircmd_test(cmd, parseredir_test(cmd, ps, env_list, env_arr), split[0], O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
		else if (tok == 'A')
			cmd = redircmd_test(cmd, parseredir_test(cmd, ps, env_list, env_arr), split[0], O_WRONLY | O_CREAT | O_APPEND, 1);
		// else if (tok == 'H')
		// {
		// 	*env = (t_env *)env_list;
		// 	ft_heredoc(env, cmd, env_arr);
		// }
		// uncomment this if you wanna check whats inside
		// printf("%d\n", cmd->type);
		// t_redir *redir = (t_redir *)cmd;
		// printf("cmd: %s\n", redir->file);
	}
	return (cmd);
}

t_cmd	*parsepipe(char **ps, t_env_p *env_list, char **env)
{
	t_cmd	*cmd;
	t_env	**env_lst;

	env_lst = malloc(sizeof(t_env **));
	cmd = parseexec(ps, env_list, env);
	while (next(ps, "<<"))
		cmd = ft_parse_heredoc(ps, env_lst, cmd, env);
	if (next(ps, "|"))
	{
		get_token(ps, 0);
		cmd = pipecmd(cmd, parsepipe(ps, env_list, env));
	}
	return (cmd);
}

int	ft_strchr(char s, char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == s)
			return (1);
		i++;
	}
	return (0);
}
// looks past any whitespace character and stops at first non whitespace char
int	next(char **ps, char *toks)
{
	char	*s;

	s = *ps;
	while (s && ft_strchr(*s, " \t\r\v\n\f"))
		s++;
	*ps = s;
	// if the char we stopped in at s, one of the chars we scanning for, if its true it returns true
	return (*s && ft_strchr(*s, toks));
}

int	is_symbol(char *str, char *es)
{
	char	*symbols;
	char	*temp;
	int		i;
	int		j;
	
	symbols = ft_strdup("<>|");
	temp = symbols;
	i = 0;
	es = NULL;
	while (str[i])
	{
		j = 0;
		symbols = temp;
		while (symbols[j])
		{
			if (str[i] == symbols[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	get_token(char **ps, char **q)
{
	char	*s;
	int		tok;

	s = *ps;
	while (s && ft_strchr(*s, " \t\f\n\v\r"))
		s++;
	if (q)
		*q = s;
	tok = *s;
	if (*s == '|')
		s++;
	else if (*s == '<')
	{
		s++;
		if (*s == '<')
		{
			tok = 'H';
			s++;
		}
	}
	else if (*s == '>')
	{
		s++;
		if (*s == '>')
		{
			tok = 'A';
			s++;
		}
	} 
	else if (*s == 0)
		return (0);
	else
	{
		tok = 'c';
		while (*s != '\0' && !ft_strchr(*s, " \t\f\n\v\r") && !ft_strchr(*s, "|<>"))
			s++;
	}
	while (s && ft_strchr(*s, " \t\f\n\v\r"))
		s++;
	*ps = s;
	return (tok);
}
// #include "exec.h"
// #include "parse.h"
// #include <unistd.h>

// int	num_words(char *str, int quote_flag)
// {
// 	int		words;
// 	char	**split;
// 	char	**temp;
// 	int		i;

// 	words = 1;
// 	i = 0;
// 	if (quote_flag)
// 	{	
// 		split = ft_split(str, ' ');
// 		temp = split;
// 	}
// 	else
// 	{
// 		split = ft_split_quotes(str, ' ');
// 		temp = split;
// 	}
// 	while(temp[i++])
// 		words++;
// 	freethis(temp);
// 	return (words);
// }

// int	is_whitespace(char *str, char *es)
// {
// 	char	*whitespaces;
// 	int		i;
// 	int		j;

// 	whitespaces = ft_strdup("\n\t\r\v ");
// 	i = 0;
// 	es = NULL;
// 	while (str[i])
// 	{
// 		j = 0;
// 		while (whitespaces[j])
// 		{
// 			if (whitespaces[j] == str[i])
// 				return (1);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// t_cmd	*parseexec(char **ps, t_env_p *env_list, char **env)
// {
// 	char	*q;
// 	int		tok;
// 	int		argc;
// 	t_exec	*cmd;
// 	int		words;
// 	t_cmd	*ret;
// 	char	**split;

// 	if (*ps[0] == '"')	
// 		words = num_words(*ps, 0);
// 	else
// 		words = num_words(*ps, 1);

// 	ret = execcmd(words);
// 	cmd = (t_exec *)ret;
// 	argc = 0;
// 	ret = parseredir_test(ret, ps, env_list, env);
// 	while (!next(ps, "|"))
// 	{
// 		tok = get_token(ps, &q);
// 		if (tok == 0)
// 			break ;
// 		split = ft_split(q, ' ');
// 		if (tok != 'c')
// 			printf("syntax error\n");
// 		cmd->argv[argc] = ft_string_examiner(split[0], env_list);
// 		argc++;
// 		if (argc >= words || split[1] == NULL)
// 			break ;
// 		ret = parseredir_test(ret, ps, env_list, env);
// 		freethis(split);
		
// 	}
// 	cmd->argv[argc] = NULL;
// 	return (ret);
// }

// // t_cmd	*parseredir(t_cmd *cmd, char **ps)
// // {
// // 	int		tok;
// // 	char	*q;
// // 	char	**split;

// // 	while (next(ps, "<>"))
// // 	{
// // 		tok = get_token(ps, 0);
// // 		if (get_token(ps, &q) != 'c')
// // 		{
// // 			ft_putstr_fd("syntax error\n", NULL, STDERR_FILENO);
// // 			cmd->type = 0;
// // 			return (cmd);
// // 		}
// // 		split = ft_split(q, ' ');
// // 		null_terminate(&split[0]);
// // 		split[1] = NULL;
// // 		if (tok == '<')
// // 			cmd = redircmd(cmd, split[0], O_RDONLY, STDIN_FILENO);
// // 		else if (tok == '>')
// // 			cmd = redircmd(cmd, split[0], O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
// // 		else if (tok == 'A')
// // 			cmd = redircmd(cmd, split[0], O_WRONLY | O_CREAT | O_APPEND, 1);
// // 		// uncomment this if you wanna check whats inside
// // 		t_redir *redir = (t_redir *)cmd;
// // 		printf("cmd: %s\n", redir->file);
// // 	}

// // 	return (cmd);
// // }

// t_cmd	*parseredir_test(t_cmd *cmd, char **ps, t_env_p *env_list, char **env_arr)
// {
// 	int		tok;
// 	char	*q;
// 	char	**split;
// 	t_env	**env;

// 	env = malloc(sizeof(t_env **));
// 	if (next(ps, "<>"))
// 	{
// 		tok = get_token(ps, 0);
// 		if (get_token(ps, &q) != 'c')
// 		{
// 			ft_putstr_fd("syntax error\n", NULL, STDERR_FILENO);
// 			cmd->type = 0;
// 			return (cmd);
// 		}
// 		split = ft_split(q, ' ');		
// 		if (tok == '<')
// 			cmd = redircmd_test(cmd, parseredir_test(cmd, ps, env_list, env_arr), split[0], O_RDONLY, STDIN_FILENO);
// 		else if (tok == '>')
// 			cmd = redircmd_test(cmd, parseredir_test(cmd, ps, env_list, env_arr), split[0], O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
// 		else if (tok == 'A')
// 			cmd = redircmd_test(cmd, parseredir_test(cmd, ps, env_list, env_arr), split[0], O_WRONLY | O_CREAT | O_APPEND, 1);
// 		else if (tok == 'H')
// 		{
// 			*env = (t_env *)env_list;
// 			ft_heredoc(env, cmd, env_arr);
// 		}
// 		// uncomment this if you wanna check whats inside
// 		// printf("%d\n", cmd->type);
// 		t_redir *redir = (t_redir *)cmd;
// 		printf("cmd: %s\n", redir->file);
// 	}
// 	free(env);
// 	return (cmd);
// }

// t_cmd	*parsepipe(char **ps, t_env_p *env_list, char **env)
// {
// 	t_cmd	*cmd;

// 	cmd = parseexec(ps, env_list, env);
// 	if (next(ps, "|"))
// 	{
// 		get_token(ps, 0);
// 		cmd = pipecmd(cmd, parsepipe(ps, env_list, env));
// 	}
// 	return (cmd);
// }

// int	ft_strchr(char s, char *buf)
// {
// 	int	i;

// 	i = 0;
// 	while (buf[i])
// 	{
// 		if (buf[i] == s)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
// // looks past any whitespace character and stops at first non whitespace char
// int	next(char **ps, char *toks)
// {
// 	char	*s;

// 	s = *ps;
// 	while (s && ft_strchr(*s, " \t\r\v\n\f"))
// 		s++;
// 	*ps = s;
// 	// if the char we stopped in at s, one of the chars we scanning for, if its true it returns true
// 	return (*s && ft_strchr(*s, toks));
// }

// int	is_symbol(char *str, char *es)
// {
// 	char	*symbols;
// 	char	*temp;
// 	int		i;
// 	int		j;
	
// 	symbols = ft_strdup("<>|");
// 	temp = symbols;
// 	i = 0;
// 	es = NULL;
// 	while (str[i])
// 	{
// 		j = 0;
// 		symbols = temp;
// 		while (symbols[j])
// 		{
// 			if (str[i] == symbols[j])
// 				return (1);
// 			j++;
// 		}
// 		i++;
// 	}
// 	free(temp);
// 	return (0);
// }

// int	get_token(char **ps, char **q)
// {
// 	char	*s;
// 	int		tok;

// 	s = *ps;
// 	while (s && ft_strchr(*s, " \t\f\n\v\r"))
// 		s++;
// 	if (q)
// 		*q = s;
// 	tok = *s;
// 	if (*s == '|')
// 		s++;
// 	else if (*s == '<')
// 	{
// 		s++;
// 		if (*s == '<')
// 		{
// 			tok = 'H';
// 			s++;
// 		}
// 	}
// 	else if (*s == '>')
// 	{
// 		s++;
// 		if (*s == '>')
// 		{
// 			tok = 'A';
// 			s++;
// 		}
// 	} 
// 	else if (*s == 0)
// 		return (0);
// 	else
// 	{
// 		tok = 'c';
// 		while (*s != '\0' && !ft_strchr(*s, " \t\f\n\v\r") && !ft_strchr(*s, "|<>"))
// 			s++;
// 	}
// 	while (s && ft_strchr(*s, " \t\f\n\v\r"))
// 		s++;
// 	*ps = s;
// 	return (tok);
// }