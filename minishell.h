#ifndef MINI_SHELL_H
#define MINI_SHELL_H

// #include "gnl/get_next_line.h"
// #include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "get_next_line.h"

typedef	struct		s_list_env
{
	char				*content;
	char				*name;
	struct s_list_env	*next;
}					t_list_env;

void			*ft_realloc(void *ptr, int size);
char			*ft_strcpy(char *s1, char *s2);
void			add_back(t_list_env **head, char *name, char *content);
char			**ft_split(char const *s, char c);;
t_list_env		*ft_lstlast(t_list_env *lst);
void			ft_lstadd_front(t_list_env **alst, t_list_env *new);
void			ft_lstadd_back(t_list_env **alst, t_list_env *new);
t_list_env		*ft_lstnew(char *name, char *content);
int				g_one;
int				g_two;

typedef struct	s_command_info {
	char		*command;
	char		*options;
	char		*string;
	int			string_len;
}				t_command_info;

typedef struct	s_variables {
	int			num;
	char		*buffer;
}				t_variables;


typedef struct	s_tests {
	int			echo;
	int			cd;
	int			pwd;
	int			export_t;
	int			unset;
	int			env;
	int			exit;
	int			ls;
}				t_tests;

t_list_env		*list_env;
t_command_info	command_info;
t_tests			tests;
t_variables		variables;

#endif