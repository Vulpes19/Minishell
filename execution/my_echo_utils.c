/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaioumy <abaioumy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:30:38 by abaioumy          #+#    #+#             */
/*   Updated: 2022/09/11 20:14:15 by abaioumy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	echo_case1(char *str)
{
	if (!str)
	{
		g.exit_status = EXIT_SUCCESS;
		printf("\n");
		return (1);
	}
	if (!ft_strncmp(str, "$?", 2))
	{
		printf("%d\n", g.exit_status);
		g.exit_status = EXIT_SUCCESS;
		return (1);
	}
	return (0);
}
