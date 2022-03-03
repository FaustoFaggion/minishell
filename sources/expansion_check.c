#include "minishell.h"

void	quote_removal(t_tkn *tkn)
{
	int	i;
	int	j;

	i = 0;
	if (tkn->tokens[i][0] == '"')
	{
		j = 0;
		while (tkn->tokens[i][j + 1] != '"')
		{
			tkn->tokens[i][j] = tkn->tokens[i][j + 1];
			j++;
		}
		tkn->tokens[i][++j] = '\0';
		tkn->tokens[i][++j] = '\0';
		i++;
	}
}

void	check_envp(t_tkn *tkn, char *envp[])
{
	int		i;
	int		j;
	int		len;
	char	*swap;

	i = 0;
	while (tkn->tokens[i])
	{
		if (ft_strncmp(tkn->tokens[i], "$", 1) == 0)
		{
			swap = tkn->tokens[i];
			swap++;
			len = ft_strlen(swap);
			j = 0;
			while (envp[j])
			{
				if (ft_strnstr(envp[j], swap, len))
					printf("%s\n",envp[j]);
				j++;
			}
			swap--;
		}
		i++;
	}
}