#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

typedef struct dltree
{
    int val;
    struct dltree *left;
    struct dltree *right;
}
node;

void free_tree(node *root);
bool search_tree(node *tree, int num);
void print_tree(node *root);

int main(void)
{
    node *tree = NULL;

    node *n = malloc(sizeof(node));

    if (n == NULL)
    {
        return 1;
    }

    n->val = 2;
    n->left = NULL;
    n->right = NULL;

    tree = n;

    n = malloc(sizeof(node));

    if (n == NULL)
    {
        free_tree(tree);
        return 1;
    }

    n->val = 1;
    n->left = NULL;
    n->right = NULL;
    tree->left = n;

    n = malloc(sizeof(node));

    if (n == NULL)
    {
        free_tree(tree);
        return 1;
    }

    n->val = 3;
    n->left = NULL;
    n->right = NULL;
    tree->right = n;

    print_tree(tree);

    int search = 1;
    printf("searching %i: %i\n", search, search_tree(tree, search));
    search = 5;
    printf("searching %i: %i\n", search, search_tree(tree, search));

    free_tree(tree);

    return 0;
}

void print_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }

    print_tree(root->left);
    printf("%i\n", root->val);
    print_tree(root->right);
}

bool search_tree(node *tree, int num)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (num < tree->val)
    {
        return search_tree(tree->left, num);
    }
    else if (num > tree->val)
    {
        return search_tree(tree->right, num);
    }
    else
    {
        return true;
    }
}

void free_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
