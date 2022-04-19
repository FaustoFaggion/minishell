#include "minishell.h"

/*
static void	not_found(t_tkn *tkn, int i)
{
	write(2, "bash: ", 6);
	write(2, tkn->tokens[i], ft_strlen(tkn->tokens[i]));
	write(2, ": Arquivo ou diretório inexistente\n", 37);
}

static int	cmd_check(t_tkn *tkn, char *cmd, int i)
{
	int		x;
	char	*temp;

	x = 0;
	if (tkn->path_0 != NULL)
		free(tkn->path_0);
	while (tkn->path[x] != NULL)
	{
		tkn->path_0 = ft_strjoin(tkn->path[x], "/");
		if (tkn->path_0 == NULL)
			exit(1);
		temp = tkn->path_0;
		tkn->path_0 = ft_strjoin(temp, cmd);
		free(temp);
		if (tkn->path_0 == NULL)
			exit(1);
		if (access(tkn->path_0, F_OK) == 0)
			return (0);
		free(tkn->path_0);
		tkn->path_0 = NULL;
		x++;
	}
	not_found(tkn, i);
	return (1);
}
*/
int	exec_cmd_path_ck(t_tkn *tkn, int i)
{
	int		x;
	char	*temp;
	x = -1;
	if (ft_strncmp(tkn->tokens[i], "/usr/bin/", 9) == 0)
	{
		temp = ft_substr(tkn->tokens[i], 9, ft_strlen(tkn->tokens[i]) - 9);
		while (tkn->tokens[i][++x + 9] != '\0')
			tkn->tokens[i][x] = tkn->tokens[i][x + 9];
		tkn->tokens[i][x] = '\0';
		while (tkn->tokens[i][++x] != '\0')
			tkn->tokens[i][x] = '\0';
		free(temp);
		return (0);
	}
	else if (ft_strncmp(tkn->tokens[i], "/bin/", 5) == 0)
	{
		temp = ft_substr(tkn->tokens[i], 5, ft_strlen(tkn->tokens[i]) - 5);
		while (tkn->tokens[i][++x + 5] != '\0')
			tkn->tokens[i][x] = tkn->tokens[i][x + 5];
		tkn->tokens[i][x] = '\0';
		while (tkn->tokens[i][++x] != '\0')
			tkn->tokens[i][x] = '\0';
		free(temp);
		return (0);
	}
	else if (ft_strncmp(tkn->tokens[i], "/usr/bin/", 9) != 0
			&& ft_strncmp(tkn->tokens[i], "/bin/", 5) != 0)
		return (0);
	return (1);
}