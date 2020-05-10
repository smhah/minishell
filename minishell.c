#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"



void	ft_putchar(char a)
{
	write(1, &a, 1);
}

void	ft_putstr(char *s)
{
	int i;

	i = 0;
	while(s[i])
		ft_putchar(s[i++]);
}

int		ft_strcmpr(char *s1, char *s2)
{
	int i;

	i = 0;
	while(s1[i] || s2[i])
	{
		if(s1[i] != s2[i])
		{
			//printf("i find the problem, s1[i] = %c | s2[i] = %c, i = %d\n", s1[i], s2[i], i);
			return(0);
		}
		i++;
	}
	return(1);
}

// int 	ft_strlen(char *s)
// {
// 	int i;

// 	i = 0;
// 	while(s[i])
// 		i++;
// 	return(i);
// }




void	ft_echo(void)
{
	int i;
	i = 0;
	int one;
	int two;
	int indice;
	int j;

	j = 0;
	one = 0;
	two = 0;
	while(command_info.string[i])
	{
		indice = 0;
		if(command_info.string[i] == '\'')
		{
			if(one == 0 && two == 0)
			{
				one = 1;
				indice = 1;
			}
			else if(one == 1 && two == 0)
			{
				one = 0;
				indice = 1;
			}
			else if(two == 1)
			{
				indice = 0;
			}
		}
		if(command_info.string[i] == '"')
		{
			if(two == 0 && one == 0)
			{
				two = 1;
				indice = 1;
			}
			else if(two == 1 && one == 0)
			{
				two = 0;
				indice = 1;
			}
			else if(one == 1)
				indice = 0;
		}
		if(!indice)
			ft_putchar(command_info.string[i]);
		indice = 0;
		i++;
	}
	ft_putchar('\n');
	if(one == 1 || two == 1)
		ft_putstr("CHNO KATKHWER\n");
}

// void		check_command(char *buf)
// {
// 	int i;
// 	char cmd[1024];
// 	int j;


// 	j = 0;
// 	i = 0;
// 	while(buf[i] == ' ')
// 		i++;
// 	while(buf[i] && buf[i] != ' ' && buf[i] != '\n')
// 		cmd[j++] = buf[i++];
// 	cmd[j] = '\0';
// 	if(ft_strcmpr("echo", cmd))
// 	{
// 		while(buf[i] == ' ')
// 			i++;
// 		if(buf[i] == '\n')
// 		{
// 			ft_putchar('\n');
// 		}
// 		else
// 			ft_echo(&buf[i]);
// 	}
// 	else if(ft_strcmpr("pwd", cmd))
// 	{
// 		char cwd[1024];

// 		//ft_putstr("hehoo");
// 		getcwd(cwd, sizeof(cwd));
// 		ft_putstr(cwd);
// 		ft_putchar('\n');
// 	}
// 	else
// 	{
// 		ft_putstr("sh: ");
// 		ft_putstr(cmd);
// 		ft_putstr(": command not found\n");
// 	}
// }

int		ft_read_line(char **buf)
{
	int j;

	*buf = malloc(1024);
	j = read(0,*buf, 1024);
	(*buf)[j] = '\0';
	//ft_putstr(buf);
	if(j >= 0)
		return(1);
	else
	{
		ft_putstr("error in reading");
		exit(-1);
	}	
}

int		test(void)
{
	tests.echo = ft_strcmpr(command_info.command, "echo");
	tests.cd = ft_strcmpr(command_info.command, "cd");
	tests.pwd = ft_strcmpr(command_info.command, "pwd");
	tests.env = ft_strcmpr(command_info.command, "env");
	tests.exit = ft_strcmpr(command_info.command, "exit");
	tests.export_t = ft_strcmpr(command_info.command, "export_t");
	tests.unset = ft_strcmpr(command_info.command, "unset");
	tests.ls = ft_strcmpr(command_info.command, "ls");
	if (!tests.echo || !tests.cd || !tests.env || !tests.exit 
	|| !tests.export_t || !tests.pwd || !tests.unset || !tests.ls)
		return (0);
	return (1);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int i;

	i = -1;
	while(s2[++i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return(s1);
}

char	*ft_check_cpy(char *s1, char *s2)
{
	int i;

	i = -1;
	while(s2[i])
	{
		if(s2[i] == '$')
		{

		}
		s1[i] = s2[i];
	}
	s1[i] = '\0';
	return(s1);
}

int		is_alpha_digit(char a)
{
	if ((a <= 'Z' && a >= 'A') || (a <= 'z' && a >= 'a' )|| (a <= '9' && a >= '0'))
		return (1);
	return(0);
}

void	ft_cpy_env(t_list_env *read_env)
{
	int e ;

	e = 0;
	while(read_env->content[e])
		command_info.string[command_info.string_len++] = read_env->content[e++];
	command_info.string[command_info.string_len] = '\0';
}

void	compare_var(char *var, char *arg)
{
	int			i;
	int			j;
	t_list_env	*read_env;

	read_env = list_env;
	i = 0;
	while(read_env)
	{
		if(ft_strcmpr(read_env->name, var))
		{
			command_info.string  = ft_realloc(command_info.string ,ft_strlen(command_info.string) + ft_strlen(arg) + ft_strlen(read_env->content) + 1 + g_two); // + g_two prsq si kant two mfto7a ("") khas n2aloki liha blastha;
			ft_cpy_env(read_env);
			break;
		}
		read_env = read_env->next;
	}
}

void	fill_command_string(char a)
{
	command_info.string[command_info.string_len++] = a;
	if(a == '\'')
		g_one = g_one == 1 ? 0 : 1;
	if(a == '"')
		g_two = g_two == 1 ? 0 : 1;
	command_info.string[command_info.string_len] = '\0';
}

void	init_one_two()
{
	g_one = 0;
	g_two = 0;
}

void	change_one_two(char a)
{
	if (a == '"')	
		g_two = g_two == 1 ? 0 : 1;
	if (a == '\'')	
		g_one = g_one == 1 ? 0 : 1;
}

void	check_env(char	**args, int i, char **env)
{
	int j;
	char *var;
	int k;
	char *buf;
	(void)env;

	j = 0;
	command_info.string  = ft_strdup(args[i]);
	while(args[i])
	{
		init_one_two();
		if(j != 0)    // to not realloc for the first time !
			command_info.string = ft_realloc(command_info.string, ft_strlen(command_info.string) + ft_strlen(args[i]) + 1);
		j = 0;
		while(args[i][j])
		{
			if((args[i][j] == '$' && args[i][j + 1] && g_one != 1 )|| (args[i][j] == '$' && args[i][j + 1] && g_one == 1 && g_two == 1))
			{
				j++;
				var = malloc(ft_strlen(args[i]));
				k = 0;
				while(is_alpha_digit(args[i][j]) && args[i][j] != '$' && args[i][j])
					var[k++] = args[i][j++];
				var[k] = '\0';
				printf("var:%s\n", var);
				compare_var(var, args[i]);
				if(args[i][j] == '"' || args[i][j] == '\'')
					fill_command_string(args[i][j]);
				free(var);
				printf("|%s|\n", command_info.string);
			}
			else
				fill_command_string(args[i][j]);
			if(args[i][j] && (args[i][j] != '$' || (g_one == 1 && args[i][j] == '$')))
				j++;
		}
		if(args[i] && args[i + 1])
		{
			command_info.string = ft_realloc(command_info.string, ft_strlen(command_info.string) + 2);
			fill_command_string(' ');
		}
		i++;
	}
	command_info.string[command_info.string_len++] = '\0';
}

void	stock_env(char **env)
{
	list_env  = NULL;
	int i;
	char *tmp1;
	char *tmp2;
	int j;

	i = 0;
	while(env[i])
	{
		j = 0;
		tmp1 = malloc(ft_strlen(env[i]));
		// tmp2 = malloc(ft_strlen(env[i]));
		while(env[i][j] != '=')
		{
			tmp1[j] = env[i][j];
			j++;
		}
		tmp1[j] = '\0';
		tmp2 = &env[i][j] + 1;
		add_back(&list_env, tmp1,tmp2);
		i++;
		// list_env = ft_lstnew(str);
	}
	// t_list_env *read;
	// read = list_env;
    // while(read)
    // {
    //     printf("name = %s|content = %s|\n", read->name, read->content);
    //     read = read->next;
    // }
}

void	fill_cmd(char **args, char **env)
{
	int j;
	int len;
	int i;

	(void)env;
	j = 0;
	i = 0;
	len = 0;
	if(!args[i])
		return;
	command_info.command = malloc(ft_strlen(args[i]) + 1);
	ft_strcpy(command_info.command, args[i]);
	i++;
	if(args[i] && args[i][0] == '-')
	{
		command_info.options = malloc(ft_strlen(args[i]));
		ft_strcpy(command_info.options, args[i]);
		i++;
	}
	if(args[i])
	{
		check_env(args, i, env);
	}
}

void	init_all()
{
	free(command_info.string);
	command_info.string = NULL;
	command_info.string_len = 0;
}
void	fill_buf(char **buf)
{
	*buf = malloc(100);
	*buf = ft_strcpy(*buf, "echo \"$HOME\"");
}

void	ft_shell(char **env)
{
	char **split;
	char *buf;
	int j;
	int i;
	char *bin = "/bin/";
	int debug;
	int ret_fork;
	char *args[200];
	char *tmp;
	int i_env = 0;

	variables.num = 0;
	debug = 0;
	i = 0;
	(void)env;

	stock_env(env);
	while(1)
	{
		init_all();
		ft_putstr("salah@minishell : ");
		if(debug == 0)
		{
			j = get_next_line(0, &buf);
			//j = ft_read_line(&buf);
		}
		else
			fill_buf(&buf);
		if(j >= 0 || debug == 1)
		{
			split = ft_split(buf, ' ');
			fill_cmd(split, env);
			printf("command : %s\noptions : %s\nstring : %s\n", command_info.command, command_info.options, command_info.string);
			test();
			//ret_fork = fork();
			// if(ret_fork < 0)
			// {
			// 	printf("error\n");
			// }
			// else if (ret_fork == 0)
			// {
				//char *bin = "/bin/";
				//char *my_command = ft_strjoin(bin, command_info.command);
				//printf("|%s|\n", my_command);
				if(tests.echo == 1)
				{
					if(command_info.string)
						ft_echo();
					else
						ft_putchar('\n');
				}
				// if (command_info.options)
				// {
				// 	args[0] = command_info.command;
				// 	args[1] = command_info.options;
				// 	args[2] = command_info.string;
				// 	args[3] = NULL;
				// }
				// else
				// {
				// 	args[0] = command_info.command;
				// 	args[1] = command_info.string;
				// 	args[2] = NULL;
				// }
				//execve(my_command, args, env);
			//}
			// else
			// {
			// 	wait(NULL);
			// }
			// while(split[i])
			// {
			// 	printf("%s\n", args[i++]);
			// }
			// ft_putstr("buf is:");
			// ft_putstr(buf);
			// ft_putchar('\n');
			//check_command(buf);

		}
		else
		{
			ft_putstr("no input");
		}
		free(buf);
		if(debug == 1)
			break;
	}
}

int main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	ft_shell(env);
}