/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:10:52 by bde-wits          #+#    #+#             */
/*   Updated: 2024/07/20 02:44:03 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*recupere l'envp et la structure du parser fini 
/ init / divise / envoi a l'execution*/

// fonction central manage les données
void	hub_exec(t_parser *data, char **env)
{
	if (init_ex_utils(data, env) == 1)
	{
		//perror();
		//ms_exit(0); //a refaire pour tout free
	}
	/*if ()
	{

	}
	if ()
	{

	}*/

}

int	init_ex_utils(t_parser *data, char **env)
{
	init_envp(data, env);

	return (0);
}

void	init_envp(t_parser *data, char **env)
{
	int	i;
	int	len;
	//char **copyenv;

	i = -1;
	len = 0;
	while (env[len] != NULL)
		len++;
	data->envp = (char **)malloc(sizeof (char *) * (len + 1));
	while (env[++i] != NULL)
		data->envp[i] = ft_strdup(env[i]);
	data->envp[len] = NULL;
	//printf("START DATA ENVP\n");
	i = 0;
	while(data->envp[i] != NULL)
	{
		//printf("%s\n", data->envp[i]);
		i++;
	}
	//printf("FINISH DATA ENVP %d i %d len\n", i, len);
}