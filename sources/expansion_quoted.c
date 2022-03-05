#include "minishell.h"

static void	s_quoted(char **tkn)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tkn[i][j + 1] != '\'')
	{
		tkn[i][j] = tkn[i][j + 1];
		j++;
	}
	tkn[i][++j] = '\0';
	tkn[i][++j] = '\0';
}

static void	d_quoted(char **tkn)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tkn[i][j + 1] != '\"')
	{
		tkn[i][j] = tkn[i][j + 1];
		j++;
	}
	tkn[i][++j] = '\0';
	tkn[i][++j] = '\0';
}

void	expansion_quote(t_tkn *tkn)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	while (tkn->tokens[i])
	{
		if (tkn->tokens[i][0] == '\"')
		{
			flag = 0;
			j = 1;
			while (tkn->tokens[i][j] != '\"')
			{
				if (tkn->tokens[i][j] == '$')
					flag = 1;
				j++;
			}
			if (flag == 0)
				d_quoted(&tkn->tokens[i]);
			else
				quoted_envp(&tkn->tokens[i]);
		}
		if (tkn->tokens[i][0] == '\"')
			s_quoted(&tkn->tokens[i]);
		i++;
	}
}