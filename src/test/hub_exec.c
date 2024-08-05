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
	printf("start hub\n");
	if (init_ex_utils(data, env) == 1)
	{
		//perror();
		//ms_exit(0); //a refaire pour tout free
		return ;// ou juste return pour pas ferme le program
	}
	exec(data);
	/*if ()
	{

	}*/
	printf("finish total\n");
	
	return ;
}

int	init_ex_utils(t_parser *data, char **env)
{
	init_envp(data, env);
	if (pipe(data->pipefd) == -1)
		return (write(1, "error pipe", 10), 1);
	data->index = 0;
	//data->tab_path = finding_path(data->envp);
	data->tab_path = NULL;
	//data->size_li = 0;
	data->status = 0;
	data->size_li = ft_size(&data->command_table);

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

int	exec(t_parser *data)
{
	pid_t	pid;
	int		size;
	//data->size_li = ft_size(&data->command_table);
	size = ft_size(&data->command_table);
	//int 	status;// a test si ont peut le mettre dans la structure
	printf("start exec\n");
	printf("ft_size %d\n", ft_size(&data->command_table));
	printf("wait = %d\n", data->status);
	//while (data->command_table->next != NULL)//&& data->index < ft_lstsize(data->command_table)
	//while(data->index <= ft_size(&data->command_table))
	while(data->index != data->size_li)// sinon faut bascule en double pointeur pour evite que le size - 1 a chaque boucle
	{
		printf("index = %d\n", data->index);
		printf("children wait = %d\n", data->status);
		data->tab_path = finding_path(data);
		//if (cmd_builtin() == 1)// si cmd == builtin , exec builtin -> next
		//	data->command_table = data->command_table->next;
		//	data->index++; peu etre pas metre l'index a jour pour pas avoir a gere les wait enfant?
		// trouvé comment gere , sinon enleve les cmd build du total dans le parent avant le wait ?
		pid = fork();
		if (pid == -1)
			return (perror("fork faillure"), 0);//ms_exit();
		if (pid == 0)
		{
			printf("before children %d\n", data->index);
			if (children(data) == 1)
				exit(1);
				//break ;
				//return (1);//close_pipe(data), fonction free ou break et le parent s'occupe de sa
			//close_pipe(data);//PROBLEME REDIR PIPE
		}
		//if (data->index < ft_lstsize(data->command_table))
		data->command_table = data->command_table->next;
		data->index++;
	}
	if (pid > 0)// || wait(&data->status) == 256
	{
		printf("index parent %d\n", data->index);
		//wait(NULL);
		//close_pipe(data);
		printf("size = %d\n", ft_size(&data->command_table));
		//while(data->index != data->size_li)
		while(data->index-- != 0)
		{
			printf("boucle wait %d index\n", data->index);
			//if (wait(&data->status) == 256)
			//	return (1);
			wait(&data->status);
		}
		printf("wait parent = %d\n", data->status);
		printf("parent\n");
		
		if (WIFEXITED(data->status))
        {
            printf("Child exited with status %d\n", WEXITSTATUS(data->status));
        }
        else
        {
            printf("Child terminated abnormally\n");
        }
		//exit(0);
		//return (0);
		//parent(data); TODO peu etre pas besoin juste free ?
	}
	printf("return 0 fin \n");
	return (0);
}

//prendre en compte le cas ou erreur cmd , sa dois effectue les autres cmd mais pas les affiches ou dans des redir si y a

//process pour les exec built-in
//probleme struct en attente de la struc final 
/*int	cmd_builtin()
{
	//pipe_redir(t_parser data, int i)
	if (compare_str(argv[1], "env") == 0)
		ms_env(&data);
	if (compare_str(argv[1], "pwd") == 0)
	{
		ms_pwd();
		return (1);
		//ou test return(ms_pwd(), 1);
	}
	if (compare_str(argv[1], "export") == 0)
		ms_export(&data, argv);
	if (compare_str(argv[1], "echo") == 0)// complique a finir sans la structure avec le parsing
		ms_echo(argv, &data);
	if (compare_str(argv[1], "cd") == 0)
		ms_cd(argv);
	if (compare_str(argv[1], "unset") == 0)
		ms_unset(argv, &data, 0);
	return (0);
}*/

int	children(t_parser *data)
{
	//int	fd;//a test dans la struct ?
	//gere les redirections , open
	printf("start children %d\n", data->index);
//	if (pipe_redir(data) == -1)//				probleme ICI affiche plus apres sans redirect
//		return (perror("fd"), 1);
	//divise par 2 , cmd built-in ou cmd env
	//printf("before checkaccess\n%s\n", data->validpath);
	data->validpath = checkaccess(data->command_table->command->command, data->tab_path);
	//printf("after checkaccess\n%s\n", data->validpath);
	if (data->validpath == NULL)
	{
		//printf("validpath == null : %s\n", data->validpath);
		return (perror("access"), 1);
	}
	//if (checkaccess(data->command_table->command->command, data->tab_path) == NULL)
	//	return (perror("access"), 1);//close_pipe possible fuite de fd ?
	//else
	//	data->validpath = checkaccess(data->command_table->command, data->tab_path);
	init_cmdtab(data);
	printf("finish children %d\n", data->index);
	execve(data->validpath, data->command_table->command->cmd_ex, data->envp);
	//close_pipe(data);
	return (0);
}

//if (data->validpath == NULL)//acces introuvable ou sans perm

//char	**init_cmdtab(char *cmd, char *args)
void	init_cmdtab(t_parser *data)
{
	char	*str;

	str = NULL;
	//iter_list(data);
	if (data->command_table->command->arguments != NULL)
	{
		str = joinspace(data->command_table->command->command,
			data->command_table->command->arguments);
		data->command_table->command->cmd_ex = split_str(str, ' ');
	}
	else
		data->command_table->command->cmd_ex = split_str(data->command_table->command->command, ' ');
	if (str != NULL)
		free(str);
}


//verifie peut etre besoin d'utilise des **pointeur pour ouvrir et ferme les fd
//les doubles permetron de d'avance dans la list sans importe la list general
/*void	iter_list(t_parser *data)
{
	int	i;

	i = -1;
	while (++i != data->index)
	{
		data->command_table = data->command_table->next;
	}
}*/

char	*checkaccess(char *cmd, char **split_path)
{
	int		i;
	char	*test;

	i = 0;
	printf("checkaccess start\n");
	printf("cmd : %s\n", cmd);
	while (split_path[i] != NULL)
	{
		//printf("path : %s\n", split_path[i]);
		test = ft_strjoin(split_path[i], cmd, 1);
		//printf("test : %s\n", test);
		if (access(test, X_OK) == 0)
			return (test);
		free(test);
		i++;
	}
	return (NULL);
}

//la gestion des fichiers , dois pouvoir prendre plusieurs imput & output
//mais l'imput le dernier comme entré mais essaye d'ouvrir les imputs (while entrefd)
//si l'un est introuvable , return (erreur) 
//L'output est pareil , ouvre tout les fd redirect (introuvable egal creat) 
//, envoye tout dans le dernier fd redirect

int	pipe_redir(t_parser *data)//int i;
{
	//int	fd_in;
	//int	fd_out;

	//redirection_in
	printf("start piperedir\n");
	if (data->redirection_in != NULL)
	{
		printf("redir in != NULL\n");
		printf("redir in : %s\n", data->redirection_in);
		//while (++i != data->index)
		//	data->
		//while ()data->redirection_in != NULL
		//{
		//	
		//}

		//if (lst_size(data->command_table->command->redirection_table > 1))
			//fd_in = multi_redir_in theoriquement plus besoin
		//else
		data->fd_in = open(data->redirection_in, O_RDONLY);
		if (data->fd_in < 0)
			return (-1);//perror() fd introuvable
		dup2(data->fd_in, 0);
		//close(data->pipefd[0]); directement ?
	}
	else//pas de redirect
	{
		printf("pas de redir in\n");
		dup2(data->pipefd[0], 0);
	}
	//redirect out
	if (data->redirection_out != NULL)
	{
		printf("redir out != NULL\n");
		printf("redir out : %s\n", data->redirection_out);
		//if (lst_size(data->command_table->command->redirection_table > 1))
			//fd_out = multi_redir_out
		data->fd_out = open(data->redirection_out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (data->fd_out < 0)
			return (-1);
		dup2(data->fd_out, 1);
		//close(data->pipefd[1]);
	}
	else
	{
		printf("pas de redir out\n");
		if (dup2(data->pipefd[1], STDOUT_FILENO) < 0)
        	perror("dup2 pipefd[1]");
		//dup2(data->pipefd[1], 1);
	}
	printf("piperedir finish\n");
	return (0);//valeur pour le fd
}

void	close_pipe(t_parser *data)
{
	//int	i;

	//i = 0;
	if (data->redirection_in != NULL)
	{
		printf("close redir in");
		close(data->pipefd[0]);
		//while (fd_in[i] != NULL)
		close(data->fd_in);
	}
	else
		close(data->pipefd[0]);
	if (data->redirection_out != NULL)
	{
		printf("close redir out");
		//close(data->fd_out);
		close(data->pipefd[1]);// je sais plus si on a besoin
	}
	//else
	//	close(data->pipefd[1]);
}

//void	parent(t_parser data) dernier execve

char	**finding_path(t_parser *data)
{
	int		i;
	char	*path;
	char	**tab_path;

	i = 0;
	if (data->tab_path != NULL)
		freetab_path(data);
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], 4) == 1)
			break ;
		i++;
	}
	//TODO : gere le cas ou le path est supr
	path = ft_strdup(data->envp[i] + 5);
	tab_path = split_str(path, ':');
	free(path);
	return (tab_path);
}

void	freetab_path(t_parser *data)
{
	int	i;

	i = 0;
	while (data->tab_path[i] != NULL)
	{
		free(data->tab_path[i]);
		i++;
	}
	free(data->tab_path);
}

char	*joinspace(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*dup;

	i = 0;
	j = 0;
	dup = (char *)malloc((sizeof (char)) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = ' ';
	i++;
	while (s2[j] != '\0')
	{
		dup[i] = s2[j];
		i++;
		j++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_strncmp(char *str, int n)
{
	int		i;
	char	*cmp;

	cmp = "PATH";
	i = 0;
	while ((str[i] != '\0' && cmp[i] != '\0') || i < n)
	{
		if (str[i] == cmp[i])
			i++;
		else if (str[i] != cmp[i])
			return (0);
	}
	return (1);
}

int	ft_size(t_command_table **li)
{
	int		i;
	t_command_table	*temp;

	i = 0;
	temp = *li;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
