#include "minishell.h"

t_list_env		*ft_lstlast(t_list_env *lst)
{
	t_list_env	*loop;

	loop = lst;
	if (loop)
		while (loop->next)
			loop = loop->next;
	return (loop);
}


void		ft_lstadd_front(t_list_env **alst, t_list_env *new)
{
	if (new)
	{
		new->next = *alst;
		*alst = new;
	}
}

void		ft_lstadd_back(t_list_env **alst, t_list_env *new)
{
	t_list_env	*temp;

	if (alst && *alst && new)
	{
		temp = ft_lstlast(*alst);
		temp->next = new;
		new->next = NULL;
	}
	else if (!*alst)
	{
		*alst = new;
		new->next = NULL;
	}
}

// void		ft_lstadd_back(t_list_env **alst, t_list_env *new)
// {
//     t_list_env *tmp;

//     tmp = *alst;
//     while(tmp->next)
//         tmp = tmp->next;
//     tmp->next = new;
//     new->next = NULL;
// }

t_list_env		*ft_lstnew(char *name, char *content)
{
	t_list_env	*list;

	list = malloc(sizeof(t_list_env));
	if (list)
	{
		list->content = content;
		list->name = name;
		list->next = NULL;
		return (list);
	}
	return (NULL);
}

void	add_back(t_list_env **head, char *name, char *content)
{
	ft_lstadd_back(head, ft_lstnew(name, content));
}

// int main()
// {
// 	char *s1 = "salah";
//     char *s2 = "eddine";
//     char *s3 = "mhah";
//     char *s4 = "last";
// 	char *s01 = "solohos";
//     char *s02 = "eddinos";
//     char *s03 = "mhahos";
//     char *s04 = "lastos";

// 	t_list_env *list;

//     list = malloc(sizeof(t_list_env));

// 	list = ft_lstnew(s1, s01);
//     add_back(&list, s2, s02);
//     add_back(&list, s3, s03);
//     add_back(&list, s4, s04);
//     while(list)
//     {
//         printf("name = %s|content = %s|\n", list->name, list->content);
//         list = list->next;
//     }
// }