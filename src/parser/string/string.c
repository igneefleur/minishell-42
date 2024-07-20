/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcavaill < tcavaill@student.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:34:28 by tcavaill          #+#    #+#             */
/*   Updated: 2024/07/20 10:34:28 by tcavaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_string	*new_string(char *text, int is_quote, int is_double)
{
	t_string	*new_str;

	new_str = malloc(sizeof(t_string));
	new_str->text = text;
	new_str->is_quote = is_quote;
	new_str->is_double = is_double;
	return (new_str);
}

void	print_string(t_string	*string)
{
	printf("{\n");
	printf("\t              text : %s\n", string->text);
	if (string->is_quote)
		printf("\tis_in_quote        ? TRUE\n");
	else
		printf("\tis_in_quote        ? FALSE\n");
	if (string->is_double)
		printf("\tis_in_double_quote ? TRUE\n");
	else
		printf("\tis_in_double_quote ? FALSE\n");
	printf("}\n");
}