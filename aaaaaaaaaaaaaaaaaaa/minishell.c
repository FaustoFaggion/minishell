#include "minishell.h"

static void print_dir()
{
	char		*user;
//	char		*host;
	char		dir[1024];

	user = getenv("USER");
	printf("%s@ ", user);
	getcwd(dir, sizeof(dir));
	printf("%s", dir);
}

static int	count_tab_x(char *line)
{
	int	i;
	int	nb;
	int	flag;

	i = 0;
	nb = 0;
	flag = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] != '\0')
	{
		 (line[i] == ' ')
			i++;
		else if (line[i] == '<')
		{
			flag = 0;
			nb++;
			i++;
			if (line[i] == '<')
				i++;
		}
		else if (line[i] == '>')
		{
			flag = 0;
			nb++;
			i++;
			if (line[i] == '>')
				i++;
		}
		else if (line[i] == '\'')
		{
			if (flag == 0)
				nb++;
			flag = 1;
			i++;
			while (line[i] != '\'' && line[i] != '\0')
				i++;
			if (line[i] == '\'')
				i++;
		}
		else if (line[i] == '"')
		{
			if (flag == 0)
				nb++;
			flag = 1;
			i++;
			while (line[i] != '"' && line[i] != '\0')
				i++;
			if (line[i] == '"')
				i++;
		}
		else if (line[i] == '|')
		{
			flag = 0;
			nb++;
			i++;
		}
		else if (line[i] == '$')
		{
			nb++;
			i++;
			if (line[i] == '{')
			{
				while (line[i] != '}')
					i++;
			}
			else
			{
				while (line[i] != ' ')
					i++;
			}
		}
		else
		{
			if (flag == 0)
				nb++;
			flag = 1;
			i++;
		}
	}
	return (nb);
}

/*
static int	count_tab_y(char *line)
{
	int	i;
	int x;
	int	nb;
	int	flag;

	i = 0;
	x = 0;
	nb = 0;
	flag = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			flag = 0;
			i++;
		}
		else if (line[i] == '<')
		{
			flag = 0;
			if (x > nb)
				nb = x;
			x = 0;
			i++;
			if (line[i] == '<')
				i++;
		}
		else if (line[i] == '>')
		{
			flag = 0;
			if (x > nb)
				nb = x;
			x = 0;
			i++;
			if (line[i] == '>')
				i++;
		}
		else if (line[i] == '\'')
		{
			if (flag == 0)
				x++;
			if (x > nb)
				nb = x;
			flag = 1;
			i++;
			while (line[i] != '\'' && line[i] != '\0')
				i++;
			if (line[i] == '\'')
				i++;
		}
		else if (line[i] == '"')
		{
			if (flag == 0)
				x++;
			if (x > nb)
				nb = x;
			flag = 1;
			i++;
			while (line[i] != '"' && line[i] != '\0')
			{
				if (line[i] == '$')
				{
					i++;
					x++;
					if (x > nb)
						nb = x;
					flag = 2;
					if (line[i] == '{')
					{
						while (line[i] != '}' && line[i] != '\0')
							i++;
					}
					else
					{
						while (line[i] != ' ' && line[i] != '\0')
							i++;
					}
				}
				if (flag == 2)
				{
					x++;
					if (x > nb)
						nb = x;
					flag = 1;
				}
				i++;
			}
			if (line[i] == '"')
				i++;
		}
		else if (line[i] == '|')
		{
			flag = 0;
			if (x > nb)
				nb = x;
			x = 0;
			i++;
		}
		else if (line[i] == '$')
		{
			if (x == 0)
				x++;
			if (x > nb)
				nb = x;
			i++;
			if (line[i] == '{')
			{
				while (line[i] != '}' && line[i] != '\0')
					i++;
				i++;
			}
			else
			{
				while (line[i] != ' ' && line[i] != '\0')
					i++;
			}
		}
		else
		{
			if (flag == 0)
				x++;
			if (x > nb)
				nb = x;
			flag = 1;
			i++;
		}
	}
	return (nb);
}
*/

/*
static int	tab_y(char *line, int x, int y)
{
	int		z;
	char	***tab_cmd;
	int		len_ptr;

	tab_cmd = (char ***)malloc(sizeof(char *) * (x + 1));
	i = 0;
	while (i < x)
	{
		tab_cmd[i] = (char **)malloc(sizeof(char *) * (y + 1));
		i++;
	}
	while (line == ' ')
		line++;
	while (line != '\0')
	{
		if (line == ' ')
			line++;
		else if (line == '<')
		{
			if (y != 0)
			{
				tab_cmd[x][y] = NULL;
				x++;
				y = 0;
			}
			len_ptr = 1;
			if (line[i] == '<')
				len_ptr++;
			tab_cmd[x][y] = ft_substr(line, 0, len_ptr);
			while (len_ptr != 0)
			{
				line++;
				len_ptr--;
			}
			y++;
			tab_cmd[x][y] = NULL;
			x++;
			y = 0;
		}
		else if (line == '>')
		{
			if (y != 0)
			{
				tab_cmd[x][y] = NULL;
				x++;
				y = 0;
			}
			len_ptr = 1;
			if (line[i] == '>')
				len_ptr++;
			tab_cmd[x][y] = ft_substr(line, 0, len_ptr);
			while (len_ptr != 0)
			{
				line++;
				len_ptr--;
			}
			y++;
			tab_cmd[x][y] = NULL;
			x++;
			y = 0;
		}
		else if (line == '\'')
		{
			len_ptr = 1;
			while (line[len_ptr] != '\'' && line[len_ptr] != '\0')
				len_ptr++;
			len_ptr++;
			tab_cmd[x][y] = ft_substr(line, 0, len_ptr);
			line = line + len_ptr;
			if (line == '\'')
				line++;
			y++;
		}
		else if (line == '"')
		{
			len_ptr = 1;
			while (line[len_ptr] != '"' && line[len_ptr] != '\0')
			{
				if (line[len_ptr] == '$')
				{
					z = 0;
					tab_cmd[x][y] = ft_substr(line, 0, len_ptr);
					while (tab_cmd[x][y][z] != '\0')
						z++;
					tab_cmd[x][y][z - 1] = '"';
					line = line + len_ptr;
					y++;
					len_ptr = 1;
					if (line[len_ptr] == '{')
					{
						while (line[len_ptr] != '}' && line[len_ptr] != '\0')
							len_ptr++;
					}
					else
					{
						while (line[len_ptr] != ' ' && line[len_ptr] != '\0')
							len_ptr++;
					}
					tab_cmd[x][y] = ft_substr(line, 0, len_ptr);
					line = line + len_ptr;
					y++;
				}
				len_ptr++;
			}
			len_ptr++;
			tab_cmd[x][y] = ft_substr(line, 0, len_ptr);
			line = line + len_ptr;
			if (line == '"')
				line++;
			y++;
		}
		else if (line[i] == '|')
		{
			flag = 0;
			if (x > nb)
				nb = x;
			x = 0;
			i++;
		}
		else if (line[i] == '$')
		{
			if (x == 0)
				x++;
			if (x > nb)
				nb = x;
			i++;
			if (line[i] == '{')
			{
				while (line[i] != '}' && line[i] != '\0')
					i++;
				i++;
			}
			else
			{
				while (line[i] != ' ' && line[i] != '\0')
					i++;
			}
		}
		else
		{
			if (flag == 0)
				x++;
			if (x > nb)
				nb = x;
			flag = 1;
			i++;
		}
	}
	if (line == '\0')
		tab_cmd[x][y] =	 NULL
	return (nb);
}
*/
static void ms_parse(char *line)
{
	int		x;
	int		y;
//	char	***tab_cmd;
	int		i;
	int 	j;
//	int		len_ptr;
	
	i = 0;
	j = 0;
	x = count_tab_x(line);
	y = count_tab_y(line);	
	printf("count tab_x %d\n", x);
	printf("count tab_y %d\n", y);
/*	tab_cmd = (char ***)malloc(sizeof(char *) * (x + 1));
	while (i < x)
	{
		tab_cmd[i] = (char **)malloc(sizeof(char *) * (y + 1));
		i++;
	}
	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			if (*line == ' ')
			line++;
			else if (*line != ' ')
			{
				len_ptr = 0;
				while (line[len_ptr] != ' ' && line[len_ptr] != 0)
					len_ptr++;
				tab_cmd[i][j] = ft_substr(line, 0, len_ptr);
				line = line + len_ptr;
				printf("%s ", tab_cmd[i][j]);
				j++;
			}
		}
		printf("\n");
		i++;
	}
*/
}

int main()
{
	static char	*line;

	while(1)
	{	
		print_dir();
		line = readline("$ ");
		add_history(line);
		ms_parse(line);
//		printf("%s\n", line);
		free(line);
	}

}