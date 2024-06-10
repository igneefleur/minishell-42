/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcavaill < tcavaill@student.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:41:19 by tcavaill          #+#    #+#             */
/*   Updated: 2024/06/10 12:41:19 by tcavaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	ms_echo(t_minishell minishell, char **words)
{
	int	i;

	i = 0;
	while(words[++i])
		printf("%s ", words[i]);
	printf("\n");
	return (minishell);
}