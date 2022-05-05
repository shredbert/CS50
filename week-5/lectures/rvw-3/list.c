#include <stdio.h>
#include <stdlib.h>

typedef struct sllist
{
    int val;
    struct sllist *next;
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

    n->val = 1;
    n->next = NULL;
    list = n;

    n = malloc(sizeof(node));

    if (n == NULL)
    {
        free(list);
        return 1;
    }

    n->val = 2;
    n->next = NULL;
    list->next = n;

    n = malloc(sizeof(node));

    if (n == NULL)
    {
        free(list->next);
        free(list);
        return 1;
    }

    n->val = 3;
    n->next = NULL;
    list->next->next = n;

    n = malloc(sizeof(node));

    if (n == NULL)
    {
        free(list->next->next);
        free(list->next);
        free(list);
        return 1;
    }

    n->val = 4;
    n->next = NULL;
    list->next->next->next = n;

    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->val);
    }

    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }

    return 0;
}
