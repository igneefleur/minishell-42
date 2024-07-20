/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcavaill < tcavaill@student.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 08:34:20 by tcavaill          #+#    #+#             */
/*   Updated: 2024/07/20 08:34:20 by tcavaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_string_table	*split_with_quotes(t_string_table *string_table, char *line)
{
	char			*temp_line;
	char			**split_line;
	char			*end_line;

	if (!line || !get_str_len(line))
		return (string_table);
	if ((find_char_in_str('\'', line)) && ((!find_char_in_str('\"', line)) || (find_char_in_str('\'', line) < find_char_in_str('\"', line))))
	{
		temp_line = find_char_in_str('\'', line) + 1;
		if (find_char_in_str('\'', temp_line))
		{
			split_line = split_simple_str(line, '\'');
			end_line = join_str(split_line + 2, '\'');
			add_string(string_table, new_string(split_line[0], FALSE, FALSE));
			add_string(string_table, new_string(split_line[1], TRUE, FALSE));
			string_table = split_with_quotes(string_table, end_line);
		}
		else
			add_string(string_table, new_string(line, FALSE, FALSE));
	}
	else if ((find_char_in_str('\"', line)) && ((!find_char_in_str('\'', line)) || (find_char_in_str('\"', line) < find_char_in_str('\'', line))))
	{
		temp_line = find_char_in_str('\"', line) + 1;
		if (find_char_in_str('\"', temp_line))
		{
			split_line = split_simple_str(line, '\"');
			end_line = join_str(split_line + 2, '\"');
			add_string(string_table, new_string(split_line[0], FALSE, FALSE));
			add_string(string_table, new_string(split_line[1], TRUE, TRUE));
			string_table = split_with_quotes(string_table, end_line);
		}
		else
			add_string(string_table, new_string(line, FALSE, FALSE));
	}
	else
		add_string(string_table, new_string(line, FALSE, FALSE));
	return (string_table);
}

