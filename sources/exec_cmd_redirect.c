#include "minishell.h"
/*
static int	d_great(t_tkn *tkn, char **next_cmd)
{
	if(tkn->fd_out != 0)
		close(tkn->fd_out);
	tkn->fd_out = open(next_cmd[1], O_RDWR | O_APPEND | O_CREAT, 0777);
	return(1);
}

static int	great(t_tkn *tkn, char **next_cmd)
{
	if(tkn->fd_out != 0)
		close(tkn->fd_out);
	tkn->fd_out = open(next_cmd[1], O_RDWR | O_TRUNC | O_CREAT, 0777);
	return (1);
}

static void	less(t_tkn *tkn, char **next_cmd)
{
	if(tkn->fd_in != 0)
		close(tkn->fd_in);
	tkn->fd_in = open(next_cmd[1], O_RDONLY);
	if (tkn->fd_in < 0)
	{
		printf("bash: %s: Arquivo ou diretório inexistente\n", next_cmd[1]);
		return ;
	}
	else
		dup2(tkn->fd_in, STDIN_FILENO);
}

void	redirect_std_fileno(t_tkn *tkn, int fd[], char **next_cmd)
{
	char	*temp;
	int		flag_fd_out;
	
	close(fd[0]);
	tkn->fd_out = 0;
	tkn->fd_in = 0;
	flag_fd_out = 0;
	while (next_cmd != NULL)
	{
		if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd + 1][0], "DGREAT", 6) == 0)
		{
			flag_fd_out = d_great(tkn, next_cmd);
		}
		else if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd + 1][0], "GREAT", 5) == 0)
		{
			flag_fd_out = great(tkn, next_cmd);

		}
		else if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd + 1][0], "LESS", 5) == 0)
		{
			less(tkn, next_cmd);
		}
		else
			break;
		tkn->i_cmd++;
		next_cmd = tkn->cmd_lex[tkn->i_cmd];
	}
	if (flag_fd_out == 1)
	{
		temp = ft_get_next_line(tkn->fd_out);
		if (tkn->fd_out < 0)
		{
			printf("bash: %s: Arquivo ou diretório inexistente\n", tkn->cmd[tkn->i_cmd][1]);
			return ;
		}
		else
			dup2(tkn->fd_out, STDOUT_FILENO);
		
	}
}
*/