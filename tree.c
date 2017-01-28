#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *link[2];
};

struct node *create_node(int x)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));

    if (new_node)
    {
        new_node->data = x;
        new_node->link[0] = NULL;
        new_node->link[1] = NULL;
    }
    return new_node;
}

void insert(struct node **root, int x)
{
    if (*root == NULL)
    {
        *root = create_node(x);
        return;
    }

    int dir = x > (*root)->data;

    insert( &((*root)->link[dir]), x );

    return;
}

void preorder(struct node *root)
{
    if (root == NULL)
        return;

    printf("%d ", root->data);
    preorder(root->link[0]);
    preorder(root->link[1]);
}

int main()
{
    struct node *my_tree = NULL;

    insert(&my_tree, 5);
    insert(&my_tree, 3);
    insert(&my_tree, 23);
    insert(&my_tree, 19);
    insert(&my_tree, 54);
    insert(&my_tree, 12);
    insert(&my_tree, 53);
    insert(&my_tree, 83);
    insert(&my_tree, 1);
    insert(&my_tree, 39);
    insert(&my_tree, 50);

    preorder(my_tree);
    printf("\n");

    return 0;
}
