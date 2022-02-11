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

typedef struct s_cmd
{
	char	*line;
	char	***tab_x;
	char	**tab_y;
	int		x_tab;
	int		y_tab;
	int		count_y;
	int		flag;
	int		len_ptr;
	int		x;
	int		y;
	int		z;
}	t_cmd;

char	***parse_cmd_tab(t_cmd *cmd);

int		metachar_check(t_cmd *cmd, int i);

int		quotes_check(t_cmd *cmd, int i, char c);

void	parse_cmd_tab_count(t_cmd *cmd);

int		parse_cmd_tab_len(t_cmd *cmd, int i);

char	**parse_cmd_tab_malloc(t_cmd *cmd);

void	exit_shell(t_cmd *cmd);

void	free_tab(t_cmd *cmd, size_t i);

#endif