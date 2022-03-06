#include "minishell.h"

void	cmd_tab(t_tkn *tkn)
{
	int		x;
	int		i;
	int		j;
	int		count;
	char	**temp;

	count = 0;
	i = 0;
	while (i < tkn->count)
	{
		if (ft_strncmp(tkn->lexemas[i], "WORD", 4) != 0 &&
			ft_strncmp(tkn->lexemas[i], "ASSIGNMENT_WORD", 15) != 0)
			count = count + 3;
		i++;
		count++;
	}
	tkn->cmd = (char ***)malloc((sizeof(char **) * sizeof(tkn->tokens) * 2) + (sizeof(char **) * 2));
	x = 0;
	i = 0;
	while (i < tkn->count)
	{

		if (ft_strncmp(tkn->lexemas[i], "WORD", 4) != 0 &&
			ft_strncmp(tkn->lexemas[i], "ASSIGNMENT_WORD", 15) != 0)
		{
			count = 0;
			while (ft_strncmp(tkn->lexemas[i + count], "WORD", 4) != 0 &&
				ft_strncmp(tkn->lexemas[i + count], "ASSIGNMENT_WORD", 15) != 0)
				count++;
			temp = (char **) malloc(sizeof(char *) * (count + 1));
			j = 0;
			while (count > 0)
			{
				temp[j] = tkn->tokens[i];
				j++;
				i++;
				count--;
			}
			temp[j] = NULL;
			tkn->cmd[x] = temp;
			x++;
			temp = NULL;
		}
		else
		{
			count = 0;
			while (ft_strncmp(tkn->lexemas[i + count], "WORD", 4) == 0 ||
				ft_strncmp(tkn->lexemas[i + count], "ASSIGNMENT_WORD", 15) == 0)
			{
				count++;
				if (tkn->lexemas[i + count] == NULL)
					break ;
			}
			temp = (char **) malloc(sizeof(char *) * (count + 1));
			j = 0;
			while (count > 0)
			{
				temp[j] = tkn->tokens[i];
				j++;
				i++;
				count--;
			}
			temp[j] = NULL;
			tkn->cmd[x] = temp;
			x++;
			temp = NULL;
		}
	}
	tkn->cmd[x] = NULL;
}