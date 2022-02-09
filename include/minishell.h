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
	char	**tab;
	int		x_tab;
	int		y_tab;
}	t_cmd;

char	**split_minishell(t_cmd *cmd);

#endif