#include "minishell.h"

void    *ft_realloc(void *ptr, int size)
{
    void *tmp;

    tmp = ptr;
    ptr = malloc(size);
    ptr = ft_strcpy(ptr, tmp);
    free(tmp);
    return(ptr);
}