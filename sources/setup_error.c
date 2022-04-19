#include "minishell.h"

void	setup_error(char *arg, int flag)
{
	if (flag == 1)
	{
		printf("bash: %s: Arquivo ou diretório inexistente\n", arg);
		global_exit = 1;

	}
	if (flag == 2)
	{
		write(2, "Quote missing\n", 14);
		global_exit = 10000000;

	}
	if (flag == 3)
	{
		printf("bash: erro de sintaxe próximo ao token inesperado '%s'\n", arg);
		global_exit = 2;
	}
	if (flag == 4)
	{
		printf("bash: erro de sintaxe próximo ao token inesperado `newline'\n");
		global_exit = 2;
	}
	if (flag == 5)
	{
		printf("bash: erro de sintaxe próximo ao token inesperado `%s'\n", arg);
		global_exit = 2;
	}
}