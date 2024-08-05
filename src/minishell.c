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

//int	g_sign = 0;
/*int	main(void)
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
}*/

void	sigint()//ctrl-C
{
//	g_sign = 1;
	printf("\n");
	rl_on_new_line();  // Réinitialiser la ligne
    rl_replace_line("", 0);  // Effacer la ligne en cours dans `readline`
    rl_redisplay();
}

void	init_sign()
{
	struct sigaction sa;

	sa.sa_handler = sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGQUIT, &sa, NULL);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	char		*line;

	(void)argc;
	(void)argv;
	init_sign();
	minishell.flag_exit = FALSE;
	minishell.flag_error = NO_ERROR;
	while(!minishell.flag_exit)
	{
		//g_sign = 0;
		line = readline("TEST:");
		if (line == NULL)
		{
			printf("exit\n");
			minishell.flag_exit = TRUE;
			minishell.flag_error = ERROR_NULL_LINE;//ctrl d du coup 
		}
		else// if (g_sign == 0)
		{
			//printf("passe par else");
			add_history(line);
			minishell = parser(minishell, line, env);
		}
		//hub_init()?
	}
	return (minishell.flag_error);
}