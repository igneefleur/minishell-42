/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcavaill < tcavaill@student.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 08:39:43 by tcavaill          #+#    #+#             */
/*   Updated: 2024/07/20 08:39:43 by tcavaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_string_table	*new_string_table(void)
{
	t_string_table	*table;

	table = malloc(sizeof(t_string_table));
	table->string = NULL;
	table->next = NULL;
	return (table);
}

void add_string(t_string_table *string_table, t_string *string)
{
	t_string_table	*temp;

	temp = string_table;
	if (string_table->string == NULL)
	{
		string_table->string = string;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_string_table();
	add_string(temp->next, string);
}

void	print_string_table(t_string_table *string_table)
{
	while (string_table->next != NULL)
	{
		if (string_table->string != NULL)
			print_string(string_table->string);
		string_table = string_table->next;
	}
	if (string_table->string != NULL)
		print_string(string_table->string);
}