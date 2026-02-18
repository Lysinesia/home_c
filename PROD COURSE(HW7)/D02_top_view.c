#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct tree
{
    int key;
    struct tree *left, *right;
} tree;

// Очередь BFS
typedef struct QueueNode
{
    tree *node;
    int hd;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
    QueueNode *front, *rear;
} Queue;

// хранение
typedef struct 
{
    int hd;
    int key;
} MapEntry;

// Созд очереди
Queue* createQueue()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// Добавление в очередь
void enqueue(Queue *q, tree *node, int hd)
{
    QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->hd = hd;
    newNode->next = NULL;
    if (q->rear == NULL)
    {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

// Удаление из очереди
QueueNode* dequeue(Queue *q)
{
    if (q->front == NULL) return NULL;
    QueueNode *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    return temp;
}

// Проверка на пустоту
int isEmpty(Queue *q)
{
    return q->front == NULL;
}

tree* createNode(int key)
{
    tree* newNode = (tree*)malloc(sizeof(tree));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

tree* insert(tree* root, int key)
{
    if (root == NULL)
    {
        return createNode(key);
    }
    if (key < root->key)
    {
        root->left = insert(root->left, key);
    } else if (key > root->key)
    {
        root->right = insert(root->right, key);
    }
    return root;
}

void freeTree(tree* root)
{
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void btUpView(tree *root)
{
    if (root == NULL) return;

    Queue *q = createQueue();
    enqueue(q, root, 0);

    MapEntry topView[1000];
    int topCount = 0;
    int minHd = INT_MAX, maxHd = INT_MIN;

    while (!isEmpty(q)) {
        QueueNode *curr = dequeue(q);
        tree *node = curr->node;
        int hd = curr->hd;

        int found = 0;
        for (int i = 0; i < topCount; i++)
        {
            if (topView[i].hd == hd)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            topView[topCount].hd = hd;
            topView[topCount].key = node->key;
            topCount++;
            if (hd < minHd) minHd = hd;
            if (hd > maxHd) maxHd = hd;
        }

        if (node->left) enqueue(q, node->left, hd - 1);
        if (node->right) enqueue(q, node->right, hd + 1);

        free(curr);
    }

    free(q);

    for (int hd = minHd; hd <= maxHd; hd++)
    {
        for (int i = 0; i < topCount; i++)
        {
            if (topView[i].hd == hd)
            {
                printf("%d ", topView[i].key);
                break;
            }
        }
    }
    printf("\n");
}

int main()
{
    tree* root = NULL;
    char line[1000];
    int value;

    fgets(line, sizeof(line), stdin);
    
    char *token = strtok(line, " \n");
    while (token != NULL)
    {
        value = atoi(token);
        root = insert(root, value);
        token = strtok(NULL, " \n");
    }
    
    btUpView(root);
    freeTree(root);
    
    return 0;
}