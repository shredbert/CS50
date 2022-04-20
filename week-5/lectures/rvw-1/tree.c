#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
}
node;

void print_tree(node *tree);
bool search_tree(node *tree, int number);
void free_tree(node *tree);

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
        free_tree(tree);
        return 1;
    }

    n->value = 1;
    n->left = NULL;
    n->right = NULL;
    tree->left = n;

    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free_tree(tree);
        return 1;
    }

    n->value = 3;
    n->left = NULL;
    n->right = NULL;
    tree->right = n;

    print_tree(tree);

    int search_int = 2;
    printf("val found: %s\n", search_tree(tree, search_int) ? "true" :
           "false");

    free_tree(tree);
}

void print_tree(node *tree)
{
    if (tree == NULL)
    {
        return;
    }
    print_tree(tree->left);
    printf("%i\n", tree->value);
    print_tree(tree->right);
}

bool search_tree(node *tree, int number)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (number < tree->value)
    {
        return search_tree(tree->left, number);
    }
    else if (number > tree->value)
    {
        return search_tree(tree->right, number);
    }
    else
    {
        return true;
    }
}

void free_tree(node *tree)
{
    if (tree == NULL)
    {
        return;
    }
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}
