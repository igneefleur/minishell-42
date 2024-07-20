/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcavaill < tcavaill@student.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:27:18 by tcavaill          #+#    #+#             */
/*   Updated: 2024/06/10 12:27:18 by tcavaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words_simple(const char *s, char c)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	if (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		if (s[i] && s[i] == c)
			i++;
		n++;
	}
	return (n);
}

int	count_word_simple(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**split_simple_str(char const *s, char c)
{
	char	**tab;
	int	n;
	int	i;
	int	j;

	tab = malloc(sizeof(char *) * (count_words_simple(s, c) + 1));
	i = 0;
	n = 0;
	if (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		tab[n] = malloc(sizeof(char) * (count_word_simple(s + i, c) + 1));
		j = 0;
		while (s[i] && s[i] != c)
			tab[n][j++] = s[i++];
		tab[n][j] = '\0';
		if (s[i] && s[i] == c)
			i++;
		n++;
	}
	tab[n] = NULL;
	return (tab);
}