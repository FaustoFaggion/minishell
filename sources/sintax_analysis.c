#include "minishell.h"

void	sintax_analysis(t_tkn *tkn)
{
	int	i;

	i = 0;
	if (ft_strncmp(tkn->lexemas[i], "PIPE", 4) == 0)
	{
		printf("bash: erro de sintaxe próximo ao token inesperado '|'\n");
		exit_shell(tkn);
		exit(1);
	}
	while (tkn->lexemas[i] != NULL)
	{
		if (ft_strncmp(tkn->lexemas[i], "LESS", 4) == 0)
		{
			if (tkn->lexemas[++i] == NULL)
			{
				printf("bash: erro de sintaxe próximo ao token inesperado '<'\n");
				exit_shell(tkn);
				exit(1);
			}
			else
			{
				if (ft_strncmp(tkn->lexemas[i], "WORD", 4) == 0)
					i++;
				else
				{
					printf("bash: erro de sintaxe próximo ao token inesperado '<'\n");
					exit_shell(tkn);
					exit(1);
				}
			}
//			printf("LESS\n");
		}
		else if (ft_strncmp(tkn->lexemas[i], "DLESS", 5) == 0)
		{
			if (tkn->lexemas[++i] == NULL)
			{
				printf("bash: erro de sintaxe próximo ao token inesperado '<<'\n");
				exit_shell(tkn);
				exit(1);
			}
			else
			{
				if (ft_strncmp(tkn->lexemas[i], "WORD", 4) == 0)
					i++;
				else
				{
					printf("bash: erro de sintaxe próximo ao token inesperado '<<'\n");
					exit_shell(tkn);
					exit(1);
				}
			}
//			printf("DLESS\n");
		}
		else if (ft_strncmp(tkn->lexemas[i], "GREAT", 5) == 0)
		{
			if (tkn->lexemas[++i] == NULL)
			{
				printf("bash: erro de sintaxe próximo ao token inesperado '>'\n");
				exit_shell(tkn);
				exit(1);
			}
			else
			{
				if (ft_strncmp(tkn->lexemas[i], "WORD", 4) == 0)
					i++;
				else
				{
					printf("bash: erro de sintaxe próximo ao token inesperado '>'\n");
					exit_shell(tkn);
					exit(1);
				}
			}
//			printf("GREAT\n");
		}
		else if (ft_strncmp(tkn->lexemas[i], "DGREAT", 6) == 0)
		{
			if (tkn->lexemas[++i] == NULL)
			{
				printf("bash: erro de sintaxe próximo ao token inesperado '>>'\n");
				exit_shell(tkn);
				exit(1);
			}
			else
			{
				if (ft_strncmp(tkn->lexemas[i], "WORD", 4) == 0)
					i++;
				else
				{
					printf("bash: erro de sintaxe próximo ao token inesperado '>>'\n");
					exit_shell(tkn);
					exit(1);
				}
			}
//			printf("DGREAT\n");
		}
		else if (ft_strncmp(tkn->lexemas[i], "ASSIGNMENT_WORD", 15) == 0)
		{
			i++;
//			printf("ASSIGNMENT_WORD\n");
		}
		else if (ft_strncmp(tkn->lexemas[i], "WORD", 4) == 0)
		{
			i++;
//			printf("WORD\n");
		}
		else if (ft_strncmp(tkn->lexemas[i], "PIPE", 4) == 0)
		{
			if (tkn->lexemas[++i] == NULL)
			{
				printf("bash: erro de sintaxe próximo ao token inesperado '|'\n");
				exit_shell(tkn);
				exit(1);
			}
//			printf("PIPE_\n");
		}
		else
			break ;
	}
}
