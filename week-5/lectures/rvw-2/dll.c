#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

typedef struct dllist
{
    int value;
    struct dllist *left;
    struct dllist *right;
}
node;

void print_list(node *list);
bool search_list(node *list, int num);
void free_list(node *list);

int main(void)
{
    node *tree = NULL;

    node *n = malloc(sizeof(node));

    if (n == NULL)
    {
        return 1;
    }

    n->value = 2;
    n->left = NULL;
    n->right = NULL;
    tree = n;

    n = malloc(sizeof(node));

    if (n == NULL)
    {
        free_list(tree);
        return 1;
    }

    n->value = 1;
    n->left = NULL;
    n->right = NULL;
    tree->left = n;

    n = malloc(sizeof(node));

    if (n == NULL)
    {
        free_list(tree);
        return 1;
    }

    n->value = 3;
    n->left = NULL;
    n-> right = NULL;
    tree->right = n;

    print_list(tree);

    int search = 5;
    printf("search %i: %i\n", search, search_list(tree, search));
    search = 1;
    printf("search %i: %i\n", search, search_list(tree, search));

    free_list(tree);

    return 0;
}

void print_list(node *root)
{
    if (root == NULL)
    {
        return;
    }

    print_list(root->left);
    printf("%i\n", root->value);
    print_list(root->right);
}

bool search_list(node *root, int num)
{
    if (root == NULL)
    {
        return false;
    }
    else if (num < root->value)
    {
        return search_list(root->left, num);
    }
    else if (num > root->value)
    {
        return search_list(root->right, num);
    }
    else
    {
        return true;
    }
}

void free_list(node *root)
{
    if (root == NULL)
    {
        return;
    }

    free_list(root->left);
    free_list(root->right);
    free(root);
}
