#include "minishell.h"

void	exec_cmd_pwd(void)
{
	char		dir[1024];

	getcwd(dir, sizeof(dir));
	printf("%s", dir);
}