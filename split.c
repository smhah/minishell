/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:17:26 by smhah             #+#    #+#             */
/*   Updated: 2019/10/20 22:20:04 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>

int g_one;
int g_two;

static int	ft_countwords(const char *str, char c)
{
	int i;
	int compteur;

	g_one = 0;
	g_two = 0;
	compteur = 0;
	i = 0;
	while (str[i] != '\0')
	{
			if(str[i] == '"')
				g_two = 1;
			if(str[i] == '\'')
				g_one = 1;
		while (str[i] == c)
			i++;
		if (str[i] == '\0')
			break ;
		compteur++;
		while ((g_one == 1 || g_two == 1 || str[i] != c) && str[i] != '\0')
		{
			if(str[i] == '"')
				g_two = (g_two == 1 ? 0 : 1);
			if(str[i] == '\'')
				g_one = (g_one == 1 ? 0 : 1);
			i++;
		}
		if (str[i] == '\0')
			break ;
	}
	return (compteur);
}

static int	ft_countlen(const char *str, char c, int *i)
{
	int len;

	g_one = 0;
	g_two = 0;
	len = 0;
	while (str[*i] != '\0')
	{
		if(str[*i] == '"')
			g_two = 1;
		if(str[*i] == '\'')
			g_one = 1;
		while (str[*i] == c)
			*i = *i + 1;
		if (str[*i] == '\0')
			return (len);
		while ((g_one == 1 || g_two == 1 || str[*i] != c) && str[*i] != '\0')
		{
			if(str[*i] == '"')
				g_two = (g_two == 1 ? 0 : 1);
			if(str[*i] == '\'')
				g_one = (g_one == 1 ? 0 : 1);
			*i = *i + 1;
			len++;
		}
		return (len);
		if (str[*i] == '\0')
			return (len);
	}
	return (len);
}

static char	**result(char **tab, const char *str, char c)
{
	int a;
	int b;
	int i;

	i = 0;
	a = 0;
	g_one = 0;
	g_two = 0;
	while (str[i] != '\0')
	{
		if(str[i] == '"')
			g_two = 1;
		if(str[i] == '\'')
			g_one = 1;
		while (str[i] == c)
			i++;
		if (str[i] == '\0')
			break ;
		b = 0;
		while ((g_one == 1 || g_two == 1 || str[i] != c ) && str[i] != '\0')
		{
			if(str[i] == '"')
				g_two = (g_two == 1 ? 0 : 1);
			if(str[i] == '\'')
				g_one = (g_one == 1 ? 0 : 1);
			tab[a][b] = str[i];
			i++;
			b++;
		}
		tab[a][b] = '\0';
		a++;
	}
	tab[a] = 0;
	return (tab);
}

static char	**freetab(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (0);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		casee;
	char	**tab;
	int		*p;
	int		len;

	i = 0;
	if (s)
		casee = ft_countwords(s, c);
	else
		return (0);
	if (!(tab = (char **)malloc(sizeof(char*) * (casee + 1))))
		return (0);
	casee = 0;
	p = &casee;
	while (i < ft_countwords(s, c))
	{
		len = ft_countlen(s, c, p);
		if (!(tab[i] = (char *)malloc(sizeof(char) * (len + 1))))
			return (freetab(tab, i));
		i++;
	}
	tab = result(tab, s, c);
	return (tab);
}

// int main()
// {
//     char **tab;
//     char *str = "test1\" hello  man\"  hehe2    he'h'e3\"mayami   i love it\"    congraaaaadz";

//     tab = ft_split(str, ' ');
//     int i = 0;

//     while(tab[i])
//     {
//         printf("%s;", tab[i]);
//         i++;
//     }
// }