/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:34:01 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/25 10:06:04 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expansion_envp(t_tkn *tkn)
{
	int		i;
	int		j;
	char	*temp;
	char	**temp_2;

	i = 0;
	while (tkn->tokens[i])
	{
		if (ft_strncmp(tkn->tokens[i], "$", 1) == 0)
		{
			temp = tkn->tokens[i];
			j = 0;
			while (tkn->tokens[i][j + 1] != '\0')
			{
				tkn->tokens[i][j] = tkn->tokens[i][j + 1];
				j++;
			}
			tkn->tokens[i][j] = '\0';
			j = 0;
			while (tkn->envp[j] != NULL)
			{
				if (ft_strncmp(tkn->envp[j], tkn->tokens[i], ft_strlen(tkn->tokens[i])) == 0)
				{
					temp_2 = ft_split(tkn->envp[j], '=');
					tkn->tokens[i] = ft_strdup(temp_2[1]);
					free_tab(&temp_2, 2);
					break ;
				}
				j++;
			}
			
			/*
			if (getenv(tkn->tokens[i]) == NULL)
				tkn->tokens[i] = ft_strdup(" ");
			else
				tkn->tokens[i] = ft_strdup(getenv(tkn->tokens[i]));
			*/
			free(temp);
		}
		i++;
	}
}

static char	*quoted_envp_line(char **tkn, char *line, int start, int i)
{
	int		len;
	char	*swap;
	char	*temp;

	len = i - start;
	if (line == NULL)
		line = ft_substr(*tkn, start, len);
	else
	{
		swap = ft_substr(*tkn, start, len);
		temp = line;
		line = ft_strjoin(line, swap);
		free(swap);
		free(temp);
	}
	return (line);
}

static char	*quoted_envp_var(char **tkn, char *line, int start, int i)
{
	int		len;
	char	*swap;
	char	*var;

	len = i - start;
	swap = ft_substr(*tkn, start, len);
	if (getenv(swap) == NULL)
		var = ft_strdup(" ");
	else
		var = ft_strdup(getenv(swap));
	free(swap);
	swap = line;
	line = ft_strjoin(swap, var);
	free(swap);
	free(var);
	return (line);
}

static void	free_line(char **tkn, char *line)
{
	char	*swap;

	swap = *tkn;
	*tkn = line;
	free(swap);
}

void	quoted_envp(char **tkn)
{
	int		i;
	int		start;
	char	*line;

	i = 1;
	line = NULL;
	while ((*tkn)[i] != '\0' && (*tkn)[i] != '\'')
	{
		start = i;
		while ((*tkn)[i] != '$' && (*tkn)[i] != '\"')
			i++;
		line = quoted_envp_line(tkn, line, start, i);
		if ((*tkn)[i] == '\"')
			break ;
		i++;
		start = i;
		while ((*tkn)[i] != ' ' && (*tkn)[i] != '\"')
			i++;
		line = quoted_envp_var(tkn, line, start, i);
		if ((*tkn)[i] == '\"')
			break ;
	}
	free_line(tkn, line);
}
