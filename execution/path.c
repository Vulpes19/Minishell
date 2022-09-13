/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:17:08 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/13 17:42:09 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**split_specialcase(char *str, char **ret)
{
	printf("hello\n");
	ret[0] = ft_strdup(str);
	ret[1] = NULL;
	return (ret);
}

int	ft_envcmp(char *s1, char *s2)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = 0;
	while (s1[name_len] != '=' && s1[name_len])
		name_len++;
	if (ft_strchr('=', s2))
		return (0);
	while (s1[i] != '=' && s2[i] && s1[i] == s2[i])
		i++;
	if (i == name_len)
		return (1);
	else
		return (0);
}

void	ft_copy(char **ret, char *str, int sublen, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < sublen)
	{
		ret[0][i] = str[i];
		i++;
	}
	ret[0][i++] = '\0';
	if (export_checkname(ret[0]) == 0)
	{
		ret[0] = NULL;
		ret[1] = NULL;
		return ;
	}
	while (i < len && str[i])
	{
		ret[1][j] = str[i];
		i++;
		j++;
	}
	ret[1][j] = '\0';
}

char	**ft_split_namecont(char *str)
{
	int		sublen;
	int		len;
	char	**ret;

	len = 0;
	sublen = 0;
	ret = (char **)malloc(sizeof(char *) * 2);
	// if (str[ft_strlen(str) - 1] == '=')
	// 	return (split_specialcase(str, ret));
	while (str[len])
		len++;
	while (str[sublen] != '=' && str[sublen])
		sublen++;
	ret[0] = (char *)malloc(sublen + 1);
	if (!ret[0])
		return (NULL);
	ret[1] = (char *)malloc(len - sublen + 1);
	if (!ret[1])
		return (NULL);
	ft_copy(ret, str, sublen, len);
	return (ret);
}

char	**ft_find_path(void)
{
	return (ft_split(getenv("PATH"), ':'));
}
