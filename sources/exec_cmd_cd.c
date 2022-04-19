/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:14:38 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/19 11:21:00 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	steup_old_pwd(t_tkn *tkn, char *old_dir)
{
	int		x;
	char	**temp;
	char	*swap;

	x = 0;
	while (tkn->envp[x] != NULL)
	{
		if (ft_strncmp(tkn->envp[x], "OLDPWD=", 7) == 0)
		{
			swap = tkn->envp[x];
			tkn->envp[x] = ft_strjoin("OLDPWD=", old_dir);
			free(swap);
			break ;
		}
		x++;
	}
	temp = tkn->envp;
	tkn->envp = NULL;
	tkn->envp = (char **)malloc(sizeof(char *) * (tkn->envp_count + 2));
	x = 0;
	while (temp[x] != NULL)
	{
		tkn->envp[x] = temp[x];
		x++;
	}
	tkn->envp[x] = ft_strjoin("OLDPWD=", old_dir);
	tkn->envp[++x] = NULL;
	tkn->envp_count++;
	free(temp);
}

static void	steup_pwd(t_tkn *tkn)
{
	int		x;
	char	dir[1024];
	char	*swap;

	x = 0;
	while (tkn->envp[x] != NULL)
	{
		if (ft_strncmp(tkn->envp[x], "PWD=", 4) == 0)
		{
			getcwd(dir, sizeof(dir));
			swap = tkn->envp[x];
			tkn->envp[x] = ft_strjoin("PWD=", dir);
			free(swap);
			break ;
		}
		x++;
	}
}

void	exec_cmd_cd(t_tkn *tkn, int i)
{
	char	old_dir[1024];
	char	*user;
	char	*user_path;
	
	user = getenv("USER");
	getcwd(old_dir, sizeof(old_dir));
	if (tkn->cmd[i][1] == NULL)
		chdir("/home");
	else if (ft_strncmp(tkn->cmd[i][1], "~\0", 2) == 0
			|| ft_strncmp(tkn->cmd[i][1], "~/", 2) == 0)
		chdir("/home");
	else if (ft_strncmp(tkn->cmd[i][1], "-\0", 2) == 0)
	{
		user_path = ft_strjoin("/home/", user);
		chdir(user_path);
		free(user_path);
	}
	else if (tkn->cmd[i][2] != NULL)
	{
		setup_error(tkn->cmd[i][2], 9);
		return ;
	}
	else
	{
		if (chdir(tkn->cmd[i][1]) == -1)
		{
			setup_error(tkn->cmd[i][1], 1);
			return ;
		}
	}
	steup_pwd(tkn);
	steup_old_pwd(tkn, old_dir);
}
