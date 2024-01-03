#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct BTNode {
    struct BTNode *lchild, *rchild;
    char data;
    float power;
} BTNode;

void insertNode(BTNode **array, int *size, BTNode *node);
BTNode* createNode(char data, float power);
BTNode* buildHuffmanTree(char data[], float power[], int size);
void printHuffmanTree(BTNode *root, int depth);
void generateHuffmanCodes(BTNode *root, char *code, int depth, char codeTable[256][256]);
float calculateWPL(BTNode *root, int depth);
void translateStringToHuffmanCode(const char *input, char *output, char codeTable[256][256]);

// 插入节点到优先队列（这里简化为直接插入到数组并排序）
void insertNode(BTNode **array, int *size, BTNode *node) {
    array[*size] = node;
    (*size)++;
    // 简单的冒泡排序，实际中应使用更高效的算法
    for (int i = *size - 1; i > 0; --i) {
        if (array[i]->power < array[i - 1]->power) {
            BTNode *temp = array[i];
            array[i] = array[i - 1];
            array[i - 1] = temp;
        }
    }
}

// 创建新节点
BTNode* createNode(char data, float power) {
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    node->data = data;
    node->power = power;
    node->lchild = node->rchild = NULL;
    return node;
}

// 构建哈夫曼树
BTNode* buildHuffmanTree(char data[], float power[], int size) {
    BTNode *queue[100]; // 假定队列足够大
    int queueSize = 0;

    // 初始化优先队列
    for (int i = 0; i < size; ++i) {
        insertNode(queue, &queueSize, createNode(data[i], power[i]));
    }

    // 构建哈夫曼树
    while (queueSize > 1) {
        BTNode *left = queue[0];
        BTNode *right = queue[1];

        // 移动队列中的元素
        for (int i = 0; i < queueSize - 2; ++i) {
            queue[i] = queue[i + 2];
        }
        queueSize -= 2;

        // 创建新节点
        BTNode *parent = createNode('\0', left->power + right->power);
        parent->lchild = left;
        parent->rchild = right;

        // 将新节点插入优先队列
        insertNode(queue, &queueSize, parent);
    }

    return queue[0]; // 哈夫曼树的根节点
}

void printHuffmanTree(BTNode *root, int depth) {
    if (root == NULL) return;
    
    printf("%c (%.2f) -> ", root->data, root->power);
    
    if (root->lchild != NULL) {
        printf("%c", root->lchild->data);
    } else {
        printf("NULL");
    }
    
    printf(" | ");
    
    if (root->rchild != NULL) {
        printf("%c", root->rchild->data);
    } else {
        printf("NULL");
    }
    
    printf("\n");
    
    printHuffmanTree(root->lchild, depth + 1);
    printHuffmanTree(root->rchild, depth + 1);
}

void generateHuffmanCodes(BTNode *root, char *code, int depth, char codeTable[256][256]) {
    if (root == NULL) return;
    if (root->lchild == NULL && root->rchild == NULL) {
        code[depth] = '\0';
        printf("%c: %s\n", root->data, code);
        strcpy(codeTable[(unsigned char)root->data], code);
    } else {
        code[depth] = '0';
        generateHuffmanCodes(root->lchild, code, depth + 1, codeTable);
        code[depth] = '1';
        generateHuffmanCodes(root->rchild, code, depth + 1, codeTable);
    }
}

float calculateWPL(BTNode *root, int depth) {
    if (root == NULL) return 0;
    if (root->lchild == NULL && root->rchild == NULL) {
        return root->power * depth;
    }
    return calculateWPL(root->lchild, depth + 1) + calculateWPL(root->rchild, depth + 1);
}

void translateStringToHuffmanCode(const char *input, char *output, char codeTable[256][256]) {
    output[0] = '\0';  // 初始化输出字符串
    while (*input) {
        strcat(output, codeTable[(unsigned char)*input]);
        input++;
    }
}

int findCharForCode(const char *code, char codeTable[256][256], char *foundChar) {
    for (int i = 0; i < 256; ++i) {
        if (strcmp(code, codeTable[i]) == 0) {
            *foundChar = (char)i;
            return 1; // 成功找到字符
        }
    }
    return 0; // 未找到字符
}

void translateHuffmanCodeToString(const char *encoded, char *output, char codeTable[256][256]) {
    output[0] = '\0';
    char tempCode[256];
    int tempCodeIndex = 0;
    int outputIndex = 0;

    while (*encoded) {
        tempCode[tempCodeIndex++] = *encoded;
        tempCode[tempCodeIndex] = '\0';

        char foundChar;
        if (findCharForCode(tempCode, codeTable, &foundChar)) {
            output[outputIndex++] = foundChar;
            tempCodeIndex = 0; // 重置临时编码索引
        }

        encoded++;
    }
    output[outputIndex] = '\0'; // 确保输出字符串正确终止
}

// 主函数
int main() 
{
    int n;
    printf("请输入节点数量: \n");
    scanf("%d", &n);
    getchar();  // 清除缓冲区中的换行符

    char data[n];
    float power[n];
    printf("请输入数据和权重 \n");
    for (int i = 0; i < n; i++) 
    {
        scanf("%c %f", &data[i], &power[i]);
        getchar();  // 清除缓冲区中的换行符
    }
    int size = sizeof(data) / sizeof(data[0]);
    char codeTable[256][256] = {0};  // 初始化编码表
    char code[256];

    BTNode *root = buildHuffmanTree(data, power, size);

    printf("Huffman Tree:\n");
    printHuffmanTree(root, 0);

    printf("\nHuffman Codes:\n");

    generateHuffmanCodes(root, code, 0, codeTable);

    float wpl = calculateWPL(root, 0);
    printf("\nWeighted Path Length (WPL): %.2f\n", wpl);
    
    char inputString[1024] ;
    printf("请输入需编码字符串\n");
    scanf("%s",inputString);
    char encodedOutput[1024];
    translateStringToHuffmanCode(inputString, encodedOutput, codeTable);
    printf("\nHuffman Encoded: %s\n", encodedOutput);
    
    char encodedString[1024];
    printf("请输入需译码的二进制译文\n");
    scanf("%s",encodedString);
    char decodedOutput[1024];
    translateHuffmanCodeToString(encodedString, decodedOutput, codeTable);
    printf("Decoded String: %s\n", decodedOutput);
    return 0;
}