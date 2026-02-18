#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree
{
    int key;
    struct tree *left, *right;
    struct tree *parent;
} tree;

// Создание нового узла
tree* createNode(int key, tree* parent)
{
    tree* node = (tree*)malloc(sizeof(tree));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    return node;
}

// Вставка в бинарное дерево поиска
tree* insert(tree* root, int key, tree* parent)
{
    if (root == NULL)
    {
        return createNode(key, parent);
    }
    
    if (key < root->key)
    {
        root->left = insert(root->left, key, root);
    }
    else if (key > root->key)
    {
        root->right = insert(root->right, key, root);
    }
    
    return root;
}

// Освобождение памяти
void freeTree(tree* root)
{
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}


tree* findBrother(tree* root, int key)
{
    if (root == NULL) return NULL;
    
    // Очередь BFS
    tree* queue[1000];
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear)
    {
        tree* current = queue[front++];
        

        if (current->left && current->left->key == key)
        {
            return current->right;
        }
        if (current->right && current->right->key == key)
        {
            return current->left;
        }

        if (current->left) queue[rear++] = current->left;
        if (current->right) queue[rear++] = current->right;
    }
    
    return NULL;
}

int main()
{
    tree* root = NULL;
    char line[1000];
    int numbers[100];
    int count = 0;
    int key;
    
    // Читаем всю строку
    fgets(line, sizeof(line), stdin);
    
    // Разбиваем на числа
    char* token = strtok(line, " \n");
    while (token != NULL)
    {
        numbers[count++] = atoi(token);
        token = strtok(NULL, " \n");
    }
    
    if (count < 2) return 1; // недостаточно данных
    
    // Последнее число — искомый ключ
    key = numbers[count - 1];
    
    // Строим дерево из остальных чисел
    for (int i = 0; i < count - 1; i++)
    {
        root = insert(root, numbers[i], NULL);
    }
    
    tree* brother = findBrother(root, key);
    
    // Выводим результат
    if (brother)
    {
        printf("%d\n", brother->key);
    }
    else
    {
        printf("No brother found\n");
    }
    
    freeTree(root);
    return 0;
}