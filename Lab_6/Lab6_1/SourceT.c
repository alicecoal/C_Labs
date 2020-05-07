#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
};

struct Node* MakeNode(struct Node* root, int key)
{
    struct Node* current = malloc(sizeof(struct Node));
    current->key = key;
    current->parent = NULL;
    current->left = current->right = NULL;
    root = current;
    return root;
}

struct Node* AddNode(struct  Node* root, int key)
{
    struct Node* current_parent = root, * position = NULL;
    struct Node* current = malloc(sizeof(struct Node));
    current->key = key;
    while (current_parent != NULL)
    {
        position = current_parent;
        if (key < current_parent->key)
            current_parent = current_parent->left;
        else
            current_parent = current_parent->right;
    }
    current->parent = position;
    current->left = NULL;
    current->right = NULL;
    if (key < position->key) position->left = current;
    else position->right = current;
    return root;
}

struct Node* SearchNode(struct Node* root, int key)
{
    if ((root == NULL) || (root->key == key))
        return root;
    if (key < root->key)
        return SearchNode(root->left, key);
    else return SearchNode(root->right, key);
}

struct Node* min1(struct Node* root)
{
    struct Node* current = root;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct Node* find(struct Node* root)
{
    struct Node* p = root, * current = NULL;
    if (p->right != NULL)
        return min1(p->right);
    current = p->parent;
    while ((current != NULL) && (p == current->right))
    {
        p = current;
        current = current->parent;
    }
    return current;
}

struct Node* DeleteNode(struct Node* root, int key)
{
    struct Node* target = NULL, * parentx = NULL;
    target = SearchNode(root, key);
    if (target->parent == NULL && target->left == NULL && target->right == NULL)
    {
        free(target);
        return NULL;
    }
    else if (target->parent == NULL && (target->left != NULL && target->right == NULL)) {
        struct Node* z;
        z = target->left;
        free(target);
        return z;
    }
    else if (target->parent == NULL && (target->left == NULL && target->right != NULL)) {
        struct Node* z;
        z = target->right;
        free(target);
        return z;
    }
    else if (target->parent == NULL && (target->left != NULL && target->right != NULL)) {
        parentx = find(target);
        target->key = parentx->key;
        if (parentx->right == NULL) {
            parentx->parent->left = NULL;
        }
        else {
            parentx->right->parent = parentx->parent;
            parentx->parent->left = parentx->right;
        }
        free(parentx);
        return target;
    }
    else if ((target->left == NULL) && (target->right == NULL))
    {
         parentx = target->parent;
         if (target == parentx->right) parentx->right = NULL;
         else parentx->left = NULL;
         free(target);
    }
    else if ((target->left == NULL) && (target->right != NULL))
    {
        parentx = target->parent; 
        //target->right->parent = parentx;
        if (target == parentx->right) parentx->right = target->right;
        else parentx->left = target->right;
        free(target);
    }
    else if ((target->left != NULL) && (target->right == NULL))
    {
        parentx = target->parent;
        //target->left->parent = parentx;
        if (target == parentx->right) parentx->right = target->left;
        else parentx->left = target->left;
         free(target);
    }
    else if ((target->left != NULL) && (target->right != NULL))
    {
        parentx = find(target);
        target->key = parentx->key;
        if (parentx->right == NULL) {
            if (parentx->parent->right!=NULL)
                if (parentx->parent->right->key != parentx->key) parentx->parent->left = NULL;
                else parentx->parent->right = NULL;
            else parentx->parent->left = NULL;
        }
        else {
            //parentx->right->parent = parentx->parent;
            parentx->parent->left = parentx->right;
        }
        free(parentx);
    }
    return root;
}

void Info(struct Node* root)
{
    if (root == NULL)
        return;
    if (root->key)
        printf("%d ", root->key);
    Info(root->left);
    Info(root->right);
}

struct queue {
    int index[100];
    char orders[100];
    int values[100];
    int end, begin;
};

void Init(struct queue* q) {
    q->begin = 1;
    q->end = 0;
    return;
}

void Insert(struct queue* q, int a, char c, int x) {
    if (q->end < 99) {
        q->end++;
        q->index[q->end] = a;
        q->orders[q->end] = c;
        q->values[q->end] = x;
    }
    else
        printf("Очередь полна!\n");
    return;
}

void Insert_char(struct queue* q, char x, int line) {
    if (q->end < 99) {
        q->end++;
        
    }
    else
        printf("Очередь полна!\n");
    return;
}

int main(void)
{
    struct queue* q;
    int a, x, n, i, n1;
    char c,c0,c1;
    struct Node* tree[100];
    int kol[100];
    for (i = 0; i < 100; i++) kol[i] = 0;
    printf("Enter the number of binary trees: ");
    scanf("%d", &n);
    q = (struct queue*)malloc(sizeof(struct queue));
    Init(q);
    printf("Enter the length of the queue:  ");
    scanf("%d", &n1);
    for (i = 0; i < n1; i++) {
        printf("Enter %d queue element (tree number, operation and data) : ", i+1);
        scanf("%d%c%c%c%d", &a, &c0, &c, &c1, &x);
        if (a<1 || a>n || ((c != 'A') && (c != 'D')))
            printf("ERROR!");
        else {
            Insert(q, a, c, x);
        }
    }

    while (q->begin <= q->end)
    {
        a = q->index[q->begin]; a--;
        c = q->orders[q->begin];
        x = q->values[q->begin];
        q->begin++;
        if (c == 'A') {
            if (kol[a] == 0)
            {
                tree[a] = MakeNode(tree[a], x); 
                kol[a]++;
            }
            else {
                tree[a] = AddNode(tree[a], x); 
                kol[a]++;
            }
        }
        else if (c == 'D') {
            if (kol[a] == 0) {
                printf("This tree is already empty!");
            }
            else {
                tree[a] = DeleteNode(tree[a], x);
                kol[a]--;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        if (tree[i]->key) Info(tree[i]);
        printf("\n");
    }
    return 0;
}
