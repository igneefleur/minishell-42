/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcavaill < tcavaill@student.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:17:22 by tcavaill          #+#    #+#             */
/*   Updated: 2024/06/10 12:17:22 by tcavaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	TODO: A REAL PARSER
*/
t_minishell	parser(t_minishell minishell, char *line)
{
	char	**words;

	words = split(line, ' ');

	if (!compare_str(words[0], "cd", MAX_WORD_LENGTH))
		minishell = ms_cd(minishell, words);
	else if (!compare_str(words[0], "echo", MAX_WORD_LENGTH))
		minishell = ms_echo(minishell, words);
	else if (!compare_str(words[0], "env", MAX_WORD_LENGTH))
		minishell = ms_env(minishell, words);
	else if (!compare_str(words[0], "exit", MAX_WORD_LENGTH))
		minishell = ms_exit(minishell, words);
	else if (!compare_str(words[0], "export", MAX_WORD_LENGTH))
		minishell = ms_export(minishell, words);
	else if (!compare_str(words[0], "pwd", MAX_WORD_LENGTH))
		minishell = ms_pwd(minishell, words);
	else if (!compare_str(words[0], "unset", MAX_WORD_LENGTH))
		minishell = ms_unset(minishell, words);
	free_split(words);
	return (minishell);
}