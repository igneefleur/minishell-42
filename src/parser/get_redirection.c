/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcavaill < tcavaill@student.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:56:00 by tcavaill          #+#    #+#             */
/*   Updated: 2024/07/19 14:56:00 by tcavaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*get_input_redirection(char *command_text)
{
	int	i;
	
	i = -1;
	while (command_text[++i] && command_text[i] != '<')
		continue ;
	if (command_text[++i] == '<')
		return (NULL);
	while (command_text[++i] && command_text[i] == ' ')
		continue ;
	// START
	while (command_text[++i] && command_text[i] != ' ' && command_text[i] != '<' && command_text[i] != '>' && command_text[i] != ' ' && command_text[i] != '|')
}

char	*get_output_redirection(char *command_text)
{
	
}

char	*get_append_input_redirection(char *command_text)
{
	
}

char	*get_append_output_redirection(char *command_text)
{
	
}