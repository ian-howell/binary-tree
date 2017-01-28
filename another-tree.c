#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *create_node(int x);
void add_node(struct node **root, int x);
void delete_node(struct node **root, int x);

int get_max(struct node *root);
int get_min(struct node *root);

void print_tree(struct node *root);
void toDot(struct node *root);
void r_toDot(struct node *root);

void clear_tree(struct node **root);

int main()
{
    struct node *my_tree = NULL;

    srand(time(NULL));

    add_node(&my_tree, 5);
    add_node(&my_tree, 36);
    add_node(&my_tree, 6);
    add_node(&my_tree, 39);
    add_node(&my_tree, 50);

    //delete_node(&my_tree, 50);
    //delete_node(&my_tree, 36);
    //delete_node(&my_tree, 6);

    //toDot(my_tree);

    //print_tree(my_tree);
    //printf("\n");

    clear_tree(&my_tree);
    //my_tree = NULL;

    return 0;
}

struct node *create_node(int x)
{
    struct node *new_node = (struct node*)malloc(sizeof(struct node));

    new_node->data = x;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

void add_node(struct node **root, int x)
{
    if (*root == NULL)
        *root = create_node(x);
    else if (x > (*root)->data)
        add_node(&((*root)->right), x);
    else
        add_node(&((*root)->left), x);
    return;
}

void delete_node(struct node **root, int x)
{
    if (x == (*root)->data)
    {
        if ((*root)->left == NULL && (*root)->right == NULL)
        {
            // this node has no children, so delete it
            free(*root);
            *root = NULL;
            return;
        }
        else if ((*root)->left != NULL && (*root)->right != NULL)
        {
            // this node has 2 children. do magic
            (*root)->data = get_max((*root)->left);
            delete_node(&((*root)->left), (*root)->data);
        }
        else
        {
            // it has exactly one child
            struct node *child = NULL;
            if ((*root)->left != NULL) // its the left child
                child = (*root)->left;
            else // its the right child
                child = (*root)->right;
            free(*root);
            *root = child;
        }
    }
    else if (x > (*root)->data)
    {
        //printf("going right\n");
        delete_node(&((*root)->right), x);
    }
    else
    {
        //printf("going left\n");
        delete_node(&((*root)->left), x);
    }
}

int get_max(struct node *root)
{
    if (root == NULL)
        return 0;

    if (root->right == NULL)
        return root->data;
    else
        return get_max(root->right);
}

int get_min(struct node *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL)
        return root->data;
    else
        return get_min(root->left);

}

void print_tree(struct node *root)
{
    if (root == NULL)
        return;

    print_tree(root->left);
    printf("%d ", root->data);
    print_tree(root->right);
}

void clear_tree(struct node **root)
{
    /*
    if ((*root)->left != NULL)
        clear_tree(&(*root)->left);

    if ((*root)->right != NULL)
        clear_tree(&(*root)->right);
    */

    if (*root == NULL)
        return;

    clear_tree(&((*root)->left));
    clear_tree(&((*root)->right));

    free(*root);
    *root = NULL;

    return;
}

void toDot(struct node *root)
{
    printf("digraph tree {\n");
    r_toDot(root);
    printf("}\n");
    return;
}

void r_toDot(struct node *root)
{
    static int nullCount = 0;

    printf("\t%ld [label=\"%d\"];\n", root, root->data);

    if (root->left != NULL)
    {
        printf("\t%ld -> %ld;\n", root, root->left);
        r_toDot(root->left);
    }
    else
    {
        printf("\tnull%d [shape=point];\n", nullCount);
        printf("\t%ld -> null%d;\n", root, nullCount);
        nullCount++;
    }

    if (root->right != NULL)
    {
        printf("\t%ld -> %ld;\n", root, root->right);
        r_toDot(root->right);
    }
    else
    {
        printf("\tnull%d [shape=point];\n", nullCount);
        printf("\t%ld -> null%d;\n", root, nullCount);
        nullCount++;
    }
}
