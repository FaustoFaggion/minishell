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
#define PIPE "PIPE"
#define LESS "LESS"
#define DLESS "DLESS"
#define GREAT "GREAT"
#define DGREAT "DGREAT"

typedef struct s_tkn
{
	char	***cmd;
	char	***cmd_lex;
	char	*line;
	char	**lexemas;
	char	**tokens;
	int		tkn_count;
	int		cmd_count;
	int		len;
	int		fd;
	char	**envp;
	int		envp_count;
	char	**path;
	int		path_count;
	char	*path_0;
	int		exp_start;
	int		exp_flag;
}	t_tkn;

typedef struct s_filename
{
	int	fd;
}	t_filename;

int		token_analysis(t_tkn *tkn);

void	lexical_analysis(t_tkn *tkn);

void	sintax_analysis(t_tkn *tkn);

void	expansion_envp(t_tkn *tkn);

void	expansion(t_tkn *tkn);

int		prepare_quote(t_tkn **tkn, char **token, int j, int i);

int		prepare_envp(t_tkn **tkn, char **quote, int j);

int		join_token(char **quote, char **temp, char **exp_envp, char **temp_2);

void	quoted_envp(char **tkn);

void	cmd_tab(t_tkn *tkn);

void	exec_cmd_tab(t_tkn *tkn);

void	exec_simple_cmd(t_tkn *tkn, int i);

int		cmd_setup(t_tkn *tkn, int i);

void	cmd_not_found(t_tkn *tkn, int i);

void	exec_cmd_pipe(t_tkn *tkn, int i);

void	exec_cmd_d_great(t_tkn *tkn, int i);

void	exec_cmd_d_less(t_tkn *tkn, int i);

int		built_in_cmd(t_tkn *tkn, int i);

void	exec_cmd_echo(t_tkn *tkn, int i);

void	exec_cmd_pwd(void);

void	exec_cmd_cd(t_tkn *tkn, int i);

void	exec_cmd_export(t_tkn *tkn, int i);

void	exec_cmd_unset(t_tkn *tkn, int i);

void	exec_cmd_envp(t_tkn *tkn);

void	exit_shell(t_tkn *tkn);

void	exit_shell_quote(t_tkn *tkn, int i);

//char	***parse_cmd_tab(t_cmd *cmd);

//int		metachar_check(t_cmd *cmd, int i);

//int		quotes_check(t_cmd *cmd, int i, char c);

//void	parse_cmd_tab_count(t_cmd *cmd);

//int		parse_cmd_tab_len(t_cmd *cmd, int i);

//char	**parse_cmd_tab_malloc(t_cmd *cmd);

void	free_tab(char ***tab, int i);

#endif