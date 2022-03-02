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