/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcavaill < tcavaill@student.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:28:10 by tcavaill          #+#    #+#             */
/*   Updated: 2024/07/19 10:28:10 by tcavaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection_table	*new_redirection_table(void)
{
	t_redirection_table	*table;

	table = malloc(sizeof(t_redirection_table));
	table->redirection = NULL;
	table->next = NULL;
	return (table);
}

void add_redirection(t_redirection_table *redirection_table, t_redirection *redirection)
{
	t_redirection_table	*temp;

	temp = redirection_table;
	if (redirection_table->redirection == NULL)
	{
		redirection_table->redirection = redirection;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_redirection_table();
	add_redirection(temp->next, redirection);
}

void	print_redirection_table(t_redirection_table *redirection_table)
{
	while (redirection_table->next != NULL)
	{
		if (redirection_table->redirection != NULL)
			print_redirection(redirection_table->redirection);
		redirection_table = redirection_table->next;
	}
	if (redirection_table->redirection != NULL)
		print_redirection(redirection_table->redirection);
}