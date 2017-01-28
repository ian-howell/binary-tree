#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct node
{
    int data;
    struct node *l;
    struct node *r;
};

struct node *create_node(int d);
void delete_node(struct node **old_node);

struct node *add_node(struct node *head, int x);

void print_tree(struct node *head);

int main()
{
    struct node *my_tree = NULL;

    srand(time(NULL));

    int i = 0;
    for (i = 0; i < 10; i++) {
        int rand_num = rand() % 10;
        my_tree = add_node(my_tree, rand_num);
        printf("\n");
    }

    print_tree(my_tree);
    printf("\n");

    delete_node(&my_tree);
    my_tree = NULL;

    return 0;
}

struct node *add_node(struct node *head, int x)
{
    if (head == NULL)
    {
        printf("Adding node %d\n", x);
        return create_node(x);
    }
    else if (x > head->data)
    {
        printf("Going right\n");
        head->r = add_node(head->r, x);
    }
    else
    {
        printf("Going left\n");
        head->l = add_node(head->l, x);
    }
    return head;
}

void print_tree(struct node *head)
{
    if (head == NULL) {
        return;
    }

    print_tree(head->l);
    printf("%d ", head->data);
    print_tree(head->r);
}

struct node *create_node(int d)
{
    struct node *new_node = (struct node*)malloc(sizeof(struct node));

    new_node->data = d;
    new_node->l = NULL;
    new_node->r = NULL;

    return new_node;
}

void delete_node(struct node **old_node)
{
    if ((*old_node)->l != NULL) {
        delete_node(&(*old_node)->l);
    }

    if ((*old_node)->r != NULL) {
        delete_node(&(*old_node)->r);
    }

    printf("Deleting %d\n", (*old_node)->data);
    free(*old_node);
    *old_node = NULL;


    return;
}
