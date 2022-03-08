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

void	exec_cmd_redirect(t_tkn *tkn, int i)
{
	if (ft_strncmp(tkn->cmd_lex[i][0], "LESS", 4) == 0)
		exec_cmd_less(tkn, i);
	
}
