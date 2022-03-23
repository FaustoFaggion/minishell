#include "minishell.h"

static void	steup_old_pwd(t_tkn *tkn, char *old_dir)
{
	int		x;
	char	**temp;
	x = 0;
	while (tkn->envp[x] != NULL)
	{
		if (ft_strncmp(tkn->envp[x], "OLDPWD=", 7) == 0)
		{
			tkn->envp[x] = ft_strjoin("OLDPWD=", old_dir);
			break ;
		}
		x++;
	}
	temp = tkn->envp;
	tkn->envp = NULL;
	tkn->envp = (char **)malloc(sizeof(char *) * (tkn->envp_count + 2));
	x = 0;
	while (temp[x] != NULL)
	{
		tkn->envp[x] = temp[x];
		x++;
	}
	tkn->envp[x] = ft_strjoin("OLDPWD=", old_dir);
	tkn->envp[++x] = NULL;
	tkn->envp_count++;
}

static void	steup_pwd(t_tkn *tkn)
{
	int		x;
	char	dir[1024];

	x = 0;
	while (tkn->envp[x] != NULL)
	{
		if (ft_strncmp(tkn->envp[x], "PWD=", 4) == 0)
		{
			getcwd(dir, sizeof(dir));
			tkn->envp[x] = ft_strjoin("PWD=", dir);
			break ;
		}
		x++;
	}
}

void	exec_cmd_cd(t_tkn *tkn, int i)
{
	char	old_dir[1024];

	getcwd(old_dir, sizeof(old_dir));
	if (tkn->cmd[i][1] == NULL)
		chdir("/home");
	else if (tkn->cmd[i][2] != NULL)
	{
		printf("bah: cd: número excessivo de argumentos\n");
		return ;
	}
	else
	{
		if (chdir(tkn->cmd[i][1]) == -1)
		{
			printf("bash: %s: Arquivo ou diretório inexistente\n", tkn->cmd[i][1]);
			return ;
		}
	}
	steup_pwd(tkn);
	steup_old_pwd(tkn, old_dir);
}