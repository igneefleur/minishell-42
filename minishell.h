/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcavaill < tcavaill@student.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:05:09 by tcavaill          #+#    #+#             */
/*   Updated: 2024/06/10 12:05:09 by tcavaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
#include <fcntl.h>

# define FALSE 0
# define TRUE 1

# define MAX_WORD_LENGTH 99

# define NO_ERROR 0
# define ERROR_NULL_LINE 1

typedef struct s_minishell
{
	int	flag_exit;
	int	flag_error;
}	t_minishell;

typedef struct s_command
{
	char	*command;
	char	*arguments;
	char	**cmd_ex;
} t_command;

typedef struct s_command_table
{
	t_command				*command;
	struct	s_command_table	*next;
} t_command_table;

typedef struct s_parser
{
	char			*redirection_in;
	char			*redirection_out;
	char			**envp; //contient l'env parent
	char			**tab_path;//dois contenir les chemins d'access cmd
	char			*validpath;
	int				pipefd[2];//entre sortie standard
	int				status;
	int				fd_in;
	int				fd_out;
	int				index;//pos list
	int				size_li;//len de la list cmd
	int				cmd_builtin;//cmd builtin sans fork
	//env ici sa peut pose des problemes peu etre dans l'execution ?
	t_command_table	*command_table;
} t_parser;

int			compare_str(const char *s1, const char *s2, int n);

// utils/get_str_len.c
int			get_str_len(char *str);

// utils/duplicate_str.c
char		*duplicate_str(char *s);

// utils/join.c
char		*join_str(char **table, char c);

// utils/split.c
char		**split_str(char const *s, char c);
void		free_split_str(char **words);

t_minishell	ms_cd(t_minishell minishell, char **words);
t_minishell	ms_echo(t_minishell minishell, char **words);
t_minishell	ms_env(t_minishell minishell, char **words);
t_minishell	ms_exit(t_minishell minishell, char **words);
t_minishell	ms_export(t_minishell minishell, char **words);
t_minishell	ms_pwd(t_minishell minishell, char **words);
t_minishell	ms_unset(t_minishell minishell, char **words);


// parser/command.c
t_command		*new_command(char *command, char *arguments);
void			print_command(t_command *command);

// parser/command_table.c
t_command_table	*new_table(void);
void			add_command(t_command_table *command_table, t_command *command);
void			print_table(t_command_table *command_table);


// parser/parser.c
t_minishell		parser(t_minishell minishell, char *line, char **envp);


//exec/hub_exec.c/init
void	hub_exec(t_parser *data, char **env);
int		init_ex_utils(t_parser *data, char **env);
void	init_envp(t_parser *data, char **env);

//exec/hub_exec/exec
int		exec(t_parser *data);
int		children(t_parser *data);
void	init_cmdtab(t_parser *data);
char	*joinspace(char *s1, char *s2);
int		pipe_redir(t_parser *data);
void	close_pipe(t_parser *data);
char	**finding_path(t_parser *data);
char	*checkaccess(char *cmd, char **split_path);
void	freetab_path(t_parser *data);
char	*ft_strjoin(char *s1, char *s2, int slash);
char	*ft_strjoinslash(char *s1, char *s2);
int		ft_size(t_command_table **li);

//utils/ex
int		ft_strncmp(char *str, int n);
char	*ft_strdup(char *s);
int		ft_strlen(char *str);

#endif