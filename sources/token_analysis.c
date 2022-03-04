#include "minishell.h"

static int	metachar_check(t_tkn *tkn, int i)
{
	if (tkn->line[i] == '|')
		i++;
	else if (tkn->line[i] == '<')
	{
		i++;
		if (tkn->line[i] == '<')
			i++;
	}
	else if (tkn->line[i] == '>')
	{
		i++;
		if (tkn->line[i] == '>')
			i++;
	}
	return (i);
}

static int	quotes_check(t_tkn *tkn, int i, char c)
{
	i++;
	while (tkn->line[i] != c)
	{
		if (tkn->line[i] == '\0')
		{
			exit_shell(tkn);
			exit(1);
		}
		i++;
	}	
	i++;
	return (i);
}

static int	count_char(t_tkn *tkn, int i)
{
	while (ft_strchr("|<> ", tkn->line[i]) == NULL)
		i++;
	return (i);
}

void	token_count(t_tkn *tkn)
{
	int	i;

	i= 0;
	tkn->count = 0;
	while (tkn->line[i] != '\0')
	{
		while (tkn->line[i] == ' ' && tkn->line[i] != '\0')
			i++;
		if (ft_strchr("|<>", tkn->line[i]) != NULL)
			i = metachar_check(tkn, i);
		else if (ft_strchr("\'\"", tkn->line[i]) != NULL)
			i = quotes_check(tkn, i, tkn->line[i]);
		else
			i = count_char(tkn, i);		
		tkn->count++;
	}
}

static void	scan_cmd_line(t_tkn *tkn)
{
	int	i;
	int	x;
	int	start;

	i = 0;
	x = 0;
	while (tkn->line[i] != '\0')
	{
		while (tkn->line[i] == ' ' && tkn->line[i] != '\0')
			i++;
		start = i;
		if (ft_strchr("|<>", tkn->line[i]) != NULL)
			i = metachar_check(tkn, i);
		else if (ft_strchr("\'\"", tkn->line[i]) != NULL)
			i = quotes_check(tkn, i, tkn->line[i]);
		else
			i = count_char(tkn, i);
		tkn->len = i - start;
		tkn->tokens[x] = ft_substr(tkn->line, start, tkn->len);
		x++;
	}
	tkn->tokens[x] = NULL;
}

void	token_analysis(t_tkn *tkn)
{
	token_count(tkn);
	tkn->tokens = (char **) malloc(sizeof(char *) * (tkn->count + 1));
	if (!tkn->tokens)
		return ;
	scan_cmd_line(tkn);
		return ;
}