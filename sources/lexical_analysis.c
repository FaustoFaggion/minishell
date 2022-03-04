#include "minishell.h"

static void	word_rules(t_tkn *tkn, int x)
{
	
	tkn->lexemas[x] = ft_strdup("WORD");
}


static void	token_to_lexema(t_tkn *tkn, int x)
{
	if (ft_strncmp(tkn->tokens[x], "|", 1) == 0)
		tkn->lexemas[x] = ft_strdup("PIPE");
/*	else if (ft_strncmp(tkn->tokens[x], "\'", 1) == 0)
		tkn->lexemas[x] = ft_strdup("SQUOTE");
	else if (ft_strncmp(tkn->tokens[x], "\"", 1) == 0)
		tkn->lexemas[x] = ft_strdup("DQUOTE");
*/	else if (ft_strncmp(tkn->tokens[x], "<\0", 2) == 0)
		tkn->lexemas[x] = ft_strdup("LESS");
	else if (ft_strncmp(tkn->tokens[x], "<<", 2) == 0)
		tkn->lexemas[x] = ft_strdup("DLESS");
	else if (ft_strncmp(tkn->tokens[x], ">\0", 2) == 0)
		tkn->lexemas[x] = ft_strdup("GREAT");
	else if (ft_strncmp(tkn->tokens[x], ">>", 2) == 0)
		tkn->lexemas[x] = ft_strdup("DGREAT");
	else if (ft_strncmp(tkn->tokens[x], "$", 1) == 0)
		tkn->lexemas[x] = ft_strdup("ASSIGNMENT_WORD");
	else
		word_rules(tkn, x);
}

void	lexical_analysis(t_tkn *tkn)
{
	int	i;

	tkn->lexemas = (char **) malloc(sizeof(char *) * (tkn->count + 1));
	if (!tkn->lexemas)
		return ;
	i = 0;
	while (tkn->tokens[i])
	{
		token_to_lexema(tkn, i);
		i++;
	}
	tkn->lexemas[i] = NULL;
}