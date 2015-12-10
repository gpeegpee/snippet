#include<stdlib.h>
#include<stdio.h>

#define MAX_SIZE (10)

typedef struct bin_tree {
	int data;
	struct bin_tree * left;
	struct bin_tree * right;
} node;

void insert(node ** tree, int val)
{
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

    if(val < (*tree)->data)
    {
        insert(&(*tree)->left, val);
    }
    else if(val > (*tree)->data)
    {
        insert(&(*tree)->right, val);
    }

}

void print_preorder(node * tree)
{
    if (tree)
    {
        printf("%d ",tree->data);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }
}

void print_inorder(node * tree)
{
    if (tree)
    {
        print_inorder(tree->left);
        printf("%d ",tree->data);
        print_inorder(tree->right);
    }
}

void print_postorder(node * tree)
{
    if (tree)
    {
        print_postorder(tree->left);
        print_postorder(tree->right);
        printf("%d ",tree->data);
    }
}

void deltree(node * tree)
{
    if (tree)
    {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}

node* search(node ** tree, int val)
{
    if(!(*tree))
    {
        return NULL;
    }

    if(val < (*tree)->data)
    {
        search(&((*tree)->left), val);
    }
    else if(val > (*tree)->data)
    {
        search(&((*tree)->right), val);
    }
    else if(val == (*tree)->data)
    {
        return *tree;
    }
}

void main()
{
    node *root;
    node *tmp;

    root = NULL;
    /* Inserting nodes into tree */

    for (int i = 0; i< MAX_SIZE; ++i)
    {
    	insert(&root, i);
    }

    /* Printing nodes of tree */
    printf("Pre Order Display\n");
    print_preorder(root);
    printf("\n");

    printf("In Order Display\n");
    print_inorder(root);
    printf("\n");

    printf("Post Order Display\n");
    print_postorder(root);
    printf("\n");

    /* Search node into tree */
    tmp = search(&root, 4);
    if (tmp)
    {
        printf("Searched node=%d\n", tmp->data);
    }
    else
    {
        printf("Data Not found in tree.\n");
    }

    /* Deleting all nodes of tree */
    deltree(root);
}
