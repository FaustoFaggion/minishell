#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "libft.h"
#include <fcntl.h>

#define DEBUG 1
/*
typedef struct s_cmd
{
	char	*line;
	char	***tab_x;
	char	**tab_y;
	int		size_tab_x;
	int		size_tab_y;
	int		count_y;
	int		flag;
	int		len_ptr;
	int		x;
	int		y;
	int		z;
	char	**grammar;
	int		size_grammar;
}	t_cmd;
*/
typedef struct s_tkn
{
	char	***cmd;
	char	*line;
	char	**lexemas;
	char	**tokens;
	int		tkn_count;
	int		cmd_count;
	int		len;
	int		fd;
	char	*path;
}	t_tkn;

typedef struct s_filename
{
	int	fd;
}	t_filename;

void	token_analysis(t_tkn *tkn);

void	lexical_analysis(t_tkn *tkn);

void	sintax_analysis(t_tkn *tkn);

void	expansion_envp(t_tkn *tkn);

void	expansion_quote(t_tkn *tkn);

void	quoted_envp(char **tkn);

void	exit_shell(t_tkn *tkn);

void	cmd_tab(t_tkn *tkn);

void	exec_cmd_tab(t_tkn *tkn);

//char	***parse_cmd_tab(t_cmd *cmd);

//int		metachar_check(t_cmd *cmd, int i);

//int		quotes_check(t_cmd *cmd, int i, char c);

//void	parse_cmd_tab_count(t_cmd *cmd);

//int		parse_cmd_tab_len(t_cmd *cmd, int i);

//char	**parse_cmd_tab_malloc(t_cmd *cmd);

//void	free_tab(char ** tab, size_t i);

#endif