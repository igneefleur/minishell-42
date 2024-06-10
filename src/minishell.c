/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcavaill < tcavaill@student.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:57:59 by tcavaill          #+#    #+#             */
/*   Updated: 2024/06/10 11:57:59 by tcavaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_minishell	minishell;
	char		*line;

	minishell.flag_exit = FALSE;
	minishell.flag_error = NO_ERROR;
	while(!minishell.flag_exit)
	{
		line = readline("TEST:");
		if (line == NULL)
		{
			minishell.flag_exit = TRUE;
			minishell.flag_error = ERROR_NULL_LINE;
		}
		else
		{
			add_history(line);
			minishell = parser(minishell, line);
		}
	}
	return (minishell.flag_error);
}