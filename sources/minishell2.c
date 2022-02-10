#include "minishell.h"
/*
static void	free_tab_x(t_cmd *cmd)
{
	if (cmd->tab_x != NULL)
	{
		while ()
	}
}
*/
static void print_dir()
{
	char		*user;
//	char		*host;
	char		dir[1024];

	user = getenv("USER");
	printf("%s@ ", user);
	getcwd(dir, sizeof(dir));
	printf("%s", dir);
}

static void token_recog(t_cmd *cmd)
{
	int	x;
	int	y;
	
	split_minishell(cmd);
	x = 0;
	y = 0;
	printf("x = %d, y = %d\n", cmd->x_tab, cmd->y_tab);
	while (x < cmd->x_tab)
	{
		y = 0;
		while (y < cmd->y_tab)
		{
			printf("tab_x[%d][%d] %s  .  ", x, y, cmd->tab_x[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
	
}

int main(void)
{
	t_cmd cmd;
	
	while(1)
	{
		print_dir();
		cmd.line = readline("$ ");
		add_history(cmd.line);
		token_recog(&cmd);
//		printf("%s\n", line);
		//free_tab_x(cmd);
		free(cmd.line);
	}

}