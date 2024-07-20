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

/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* */// QUOTES STRUCTS

typedef struct s_string
{
	char	*text;
	int		is_quote;
	int		is_double;
} t_string;

typedef struct s_string_table
{
	t_string				*string;
	struct s_string_table	*next;
}	t_string_table;

/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* */// COMMAND STRUCTS

typedef struct s_redirection
{
	char	*filename;
	int		is_output;
	int		is_append;
}	t_redirection;

typedef struct s_redirection_table
{
	t_redirection				*redirection;
	struct s_redirection_table	*next;
}	t_redirection_table;

typedef struct s_command
{
	char				*command;
	char				*arguments;
	t_redirection_table	*input_redirection_table;
	t_redirection_table	*output_redirection_table;
}	t_command;

typedef struct s_command_table
{
	t_command				*command;
	struct	s_command_table	*next;
}	t_command_table;

typedef struct s_parser
{
	t_command_table	*command_table;
}	t_parser;

/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* */// FUNCTIONS

int			compare_str(const char *s1, const char *s2, int n);

// utils/get_str_len.c
int	get_str_len(char *str);

// utils/find_char_in_str.c
char	*find_char_in_str(int c, char *s);

// utils/duplicate_str.c
char	*duplicate_str(char *s);

// utils/join.c
char		*join_str(char **table, char c);

// utils/split_simple_str.c
char	**split_simple_str(char const *s, char c);


// utils/split_str.c
char		**split_str(char const *s, char c);
void		free_split_str(char **words);

t_minishell	ms_cd(t_minishell minishell, char **words);
t_minishell	ms_echo(t_minishell minishell, char **words);
t_minishell	ms_env(t_minishell minishell, char **words);
t_minishell	ms_exit(t_minishell minishell, char **words);
t_minishell	ms_export(t_minishell minishell, char **words);
t_minishell	ms_pwd(t_minishell minishell, char **words);
t_minishell	ms_unset(t_minishell minishell, char **words);



//// MODIFS THEO

// parser/string/string.c
t_string		*new_string(char *text, int is_quote, int is_double);
void			print_string(t_string	*string);
// parser/string/string_table.c
t_string_table	*new_string_table(void);
void 			add_string(t_string_table *string_table, t_string *string);
void			print_string_table(t_string_table *string_table);

// parser/command/command.c
t_command		*new_command(char *command_text, char *arguments, t_redirection_table *input_redirection_table, t_redirection_table *output_redirection_table);
void			print_command(t_command *command);
// parser/command/command_table.c
t_command_table	*new_command_table(void);
void			add_command(t_command_table *command_table, t_command *command);
void			print_command_table(t_command_table *command_table);

// parser/redirection/redirection.c
t_redirection	*new_redirection(char *filename, int is_output, int is_append);
void			print_redirection(t_redirection *redirection);
// parser/redirection/redirection_table.c
t_redirection_table	*new_redirection_table(void);
void			add_redirection(t_redirection_table *redirection_table, t_redirection *redirection);
void			print_redirection_table(t_redirection_table *redirection_table);

// parser/split_with_quotes.c
t_string_table	*split_with_quotes(t_string_table *string_table, char *line);
// parser/transform_variables.c
t_string_table	*transform_variables(t_string_table *string_table);
// parser/split_with_pipes.c
t_command_table	*split_with_pipes(t_string_table *string_table);

// parser/parser.c
t_minishell		parser(t_minishell minishell, char *line);

#endif