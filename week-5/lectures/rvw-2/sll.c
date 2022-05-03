#include <stdio.h>
#include <stdlib.h>

typedef struct slnode
{
    int value;
    struct slnode *next;
}
node;

int main(void)
{
    node *list = NULL;

    node *n = malloc(sizeof(node));

    if (n == NULL)
    {
        return 1;
    }

    n->value = 1;
    n->next = NULL;
    list = n;

    n = malloc(sizeof(node));
    
    if (n == NULL)
    {
        free(list);
        return 1;
    }

    n->value = 2;
    n->next = NULL;
    list->next = n;

    n = malloc(sizeof(node));

    if (n == NULL)
    {
        free(list->next);
        free(list);
        return 1;
    }

    n->value = 3;
    n->next = NULL;
    list->next->next = n;

    n = malloc(sizeof(node));

    if (n == NULL) {
        free(list->next->next);
        free(list->next);
        free(list);
        return 1;
    }

    n->value = 4;
    n->next = NULL;
    list->next->next->next = n;

    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->value);
    }

    while (list != NULL)
    {
        node *tmp = list->next;
    }

    return 0;
}
