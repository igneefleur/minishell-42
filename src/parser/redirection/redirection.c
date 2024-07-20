/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcavaill < tcavaill@student.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:00:02 by tcavaill          #+#    #+#             */
/*   Updated: 2024/07/19 11:00:02 by tcavaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*new_redirection(char *filename, int is_output, int is_append)
{
	t_redirection	*redirection;

	redirection = malloc(sizeof(t_redirection)); 
	if (redirection == NULL)
		return (NULL);
	redirection->filename = filename;
	redirection->is_output = is_output;
	redirection->is_append = is_append;
	return (redirection);
}

void	print_redirection(t_redirection *redirection)
{
	printf("{\n");
	printf("\tfilename  : %s\n", redirection->filename);
	printf("\tis_output : %d\n", redirection->is_output);
	printf("\tis_append : %d\n", redirection->is_append);
	printf("}\n");
}
