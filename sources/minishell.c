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
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
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
			{
				if (line[i] == '$')
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
				i++;
			}
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
static size_t	count_tab_y(char const *s, char c)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] == '\'')
		{
			nb++;
			i++;
			while (s[i] != '\'' && s[i] != '\0')
				i++;
			i++;
		}
		if (s[i] != c && s[i] != '\0' && (s[i] != '\''))
		{	
			nb++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (nb);
}
*/
static void ms_parse(char *line)
{
	int		i;
	int		flag;
	int		x;
//	int		y;

	flag = 0;
	i = 0;
	x = count_tab_x(line);
//	y = count_tab_y(line, ' ');
	printf("count tab_x %d\n", x);
//	printf("count tab_y %d\n", y);
	while (line[i] != '\0')
	{
		
		if (line[i] == '<')
			printf("1");
		else if (line[i] == '>')
			printf("2");
		else if (line[i] == '\'')
			printf("3");
		else if (line[i] == '"')
			printf("4");
		else if (line[i] == '|')
			printf("5");
		else if (line[i] == '$')
			printf("6");
		i++;
	}
}

int main()
{
	static char	*line;
//	char		**tab_cmd;

	while(1)
	{	
		print_dir();
		line = readline("$ ");
		add_history(line);
		ms_parse(line);
		printf("%s\n", line);
		free(line);
	}
}