#include "minishell.h"

void	sintax_check(t_tkn *tkn)
{
	int	i;

	i = 0;
	if (ft_strncmp(tkn->lexemas[i], "PIPE", 4) == 0)
		printf("bash: erro de sintaxe próximo ao token inesperado '|'\n");
	while (tkn->lexemas[i] != NULL)
	{
		if (ft_strncmp(tkn->lexemas[i], "LESS", 4) == 0)
		{
			if (ft_strncmp(tkn->lexemas[++i], "WORD", 4) == 0)
				i++;
			else
				printf("bash: erro de sintaxe próximo ao token inesperado '<'\n");
			printf("LESS\n");
		}
		else if (ft_strncmp(tkn->lexemas[i], "DLESS", 5) == 0)
		{
			if (ft_strncmp(tkn->lexemas[++i], "WORD", 4) == 0)
				i++;
			else
				printf("bash: erro de sintaxe próximo ao token inesperado '<<'\n");
			printf("DLESS\n");
		}
		else if (ft_strncmp(tkn->lexemas[i], "GREAT", 5) == 0)
		{
			if (ft_strncmp(tkn->lexemas[++i], "WORD", 4) == 0)
				i++;
			else
				printf("bash: erro de sintaxe próximo ao token inesperado '>'\n");
			printf("GREAT\n");
		}
		else if (ft_strncmp(tkn->lexemas[i], "DGREAT", 6) == 0)
		{
			if (ft_strncmp(tkn->lexemas[++i], "WORD", 4) == 0)
				i++;
			else
				printf("bash: erro de sintaxe próximo ao token inesperado '>>'\n");
			printf("DGREAT\n");
		}
		else if (ft_strncmp(tkn->lexemas[i], "ASSIGNMENT_WORD", 15) == 0)
		{
			i++;
			printf("ASSIGNMENT_WORD\n");
		}
		else if (ft_strncmp(tkn->lexemas[i], "WORD", 4) == 0)
		{
			i++;
			printf("WORD\n");
		}
		else if (ft_strncmp(tkn->lexemas[i], "PIPE", 4) == 0)
		{
			if (tkn->lexemas[++i] == NULL)
				printf("bash: erro de sintaxe próximo ao token inesperado '|'\n");
			printf("PIPE\n");
		}
		else
			break ;
	}
}


