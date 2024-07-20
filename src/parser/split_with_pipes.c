/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcavaill < tcavaill@student.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:21:57 by tcavaill          #+#    #+#             */
/*   Updated: 2024/07/20 12:21:57 by tcavaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command_table	*split_with_pipes(t_string_table *string_table)
{
	t_command_table	*command_table;

	while (string_table->next != NULL)
	{
		if (string_table->string != NULL)
		{

		}
		string_table = string_table->next;
	}
	if (string_table->string != NULL)
	{
		
	}
	command_table = new_command_table();
	return (command_table);
}