#include "minishell.h"

void	exec_cmd_pwd(t_tkn *tkn)
{
	printf("%s\n", tkn->pwd);
}