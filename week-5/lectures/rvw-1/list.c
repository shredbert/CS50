#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    node *list = NULL;
    
    node *tmp = malloc(sizeof(node));
    if (tmp == NULL)
    {
        return 1;
    }

    tmp->number = 1;
    tmp->next = NULL;
    list = tmp;
    
    tmp = malloc(sizeof(node));
    if (tmp == NULL)
    {
        free(list);
        return 1;
    }

    tmp->number = 2;
    tmp->next = NULL;
    list->next = tmp;
    
    tmp = malloc(sizeof(node));
    if (tmp == NULL)
    {
        free(list->next);
        free(list);
        return 1;
    }

    tmp->number = 3;
    tmp->next = NULL;
    list->next->next = tmp;

    tmp = malloc(sizeof(node));
    if (tmp == NULL)
    {
        free(list->next->next);
        free(list->next);
        free(list);
        return 1;
    }

    tmp->number = 4;
    tmp->next = NULL;
    list->next->next->next = tmp;

    for (node *n = list; n != NULL; n = n->next)
    {
        printf("%i\n", n->number);
    }

    while (list != NULL)
    {
        node *n = list->next;
        free(list);
        list = n->next;
    }

    return 0;
}
