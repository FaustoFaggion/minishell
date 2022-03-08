#include "minishell.h"

static void	exec_cmd_less(t_tkn *tkn, int i)
{
	if (ft_strncmp(tkn->cmd_lex[i][1], "WORD", 4) == 0)
		tkn->fd = open(tkn->cmd[i][1], O_RDONLY);
	if (tkn->fd < 0)
	{
		printf("bash: %s: Arquivo ou diretório inexistente\n", tkn->cmd[i][1]);
		return ;
	}
	else
		dup2(tkn->fd, STDIN_FILENO);
}

static void	exec_cmd_great(t_tkn *tkn, int i)
{
	printf(".......");
	if (ft_strncmp(tkn->cmd_lex[i][1], "WORD", 4) == 0)
		tkn->fd = open(tkn->cmd[i][1], O_RDWR | O_APPEND | O_CREAT, 0777);
	if (tkn->fd < 0)
	{
		printf("bash: %s: Arquivo ou diretório inexistente\n", tkn->cmd[i][1]);
		return ;
	}
	else
	{
		//dup2(tkn->fd, STDOUT_FILENO);
	}
}

static void	wr_line(char *tkn, int limiter, int fd[])
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		line = ft_get_next_line(STDIN_FILENO);
		if (ft_strncmp(tkn, line, limiter) == 0)
		{
			if (line[limiter] == '\n')
			{
				free(line);
				ft_get_next_line(-1);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
		}
		else
		{
			write(fd[1], line, ft_strlen(line));
		}
		free(line);
	}
}

static int	exec_cmd_dless(t_tkn *tkn, int i)
{
	int	fd[2];
	int		limiter;

		if (pipe(fd) == -1)
			exit(write(1, "pipe error\n", 11));
		limiter = ft_strlen(tkn->cmd[i][1]);
		wr_line(tkn->cmd[i][1], limiter, fd);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		return (2);
}

void	exec_cmd_redirect(t_tkn *tkn, int i)
{
	if (ft_strncmp(tkn->cmd_lex[i][0], "LESS", 4) == 0)
		exec_cmd_less(tkn, i);
	else if (ft_strncmp(tkn->cmd_lex[i][0], "GREAT", 5) == 0)
		exec_cmd_great(tkn, i);
	else if (ft_strncmp(tkn->cmd_lex[i][0], "DLESS", 5) == 0)
		exec_cmd_dless(tkn, i);
}
