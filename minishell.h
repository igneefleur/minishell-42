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
# include <readline/readline.h>
# include <readline/history.h>

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
	t_command_table	*command_table;
} t_parser;

int			compare_str(const char *s1, const char *s2, int n);

// utils/get_str_len.c
int	get_str_len(char *str);

// utils/duplicate_str.c
char	*duplicate_str(char *s);

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
t_minishell		parser(t_minishell minishell, char *line);

#endif