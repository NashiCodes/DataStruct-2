#ifndef AVL__TREE_H
#define AVL_TREE_H

#include <iostream>

using namespace std;

class AVLTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;
        
    };

    Node* root;
     int avlRotations; // Variável para contar o número de rotações

    // Função auxiliar para criar um novo nó com a chave fornecida
    Node* createNode(int key) {
        Node* newNode = new Node();
        newNode->key = key;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
        avlRotations = 0;
    }
public:
    AVLTree() {
        root = nullptr;
    }
      int getRotationCount() {
        return avlRotations;
    }

    // Função pública para inserir uma chave na árvore AVL
    void insert(int key) {
        root = insertNode(root, key);
    }

    // Função pública para buscar uma chave na árvore AVL
    bool search(int key, int &comparisons) {
        return searchNode(root, key, comparisons);
    }

    // Função auxiliar para obter a altura de um nó
    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // Função auxiliar para obter o fator de balanceamento de um nó
    int getBalanceFactor(Node* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Função auxiliar para atualizar a altura de um nó
    void updateHeight(Node* node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = max(leftHeight, rightHeight) + 1;
    }

    // Função auxiliar para realizar uma rotação simples à direita
    Node* rotateRight(Node* node) {
        Node* newRoot = node->left;
        Node* subtree = newRoot->right;
        newRoot->right = node;
        node->left = subtree;
        updateHeight(node);
        updateHeight(newRoot);
        avlRotations++; // Incrementa a contagem de rotações
        return newRoot;
    }

    // Função auxiliar para realizar uma rotação simples à esquerda
    Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;
        Node* subtree = newRoot->left;
        newRoot->left = node;
        node->right = subtree;
        updateHeight(node);
        updateHeight(newRoot);
        avlRotations++; // Incrementa a contagem de rotações
        return newRoot;
    }

    // Função auxiliar para balancear um nó após uma inserção ou remoção
    Node* balanceNode(Node* node) {
        updateHeight(node);
        int balanceFactor = getBalanceFactor(node);

        // Caso o nó esteja desbalanceado, é necessário realizar rotações para restaurar o balanceamento
        if (balanceFactor > 1) {
            if (getBalanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balanceFactor < -1) {
            if (getBalanceFactor(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    // Função auxiliar para inserir uma chave na árvore AVL
   Node* insertNode(Node* node, int key) {
        // Realiza a inserção como em uma árvore binária de busca
        if (node == nullptr)
            return createNode(key);
        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else
            return node; // Chave já existente, não realiza a inserção

        // Atualiza a altura e balanceia o nó
        node = balanceNode(node);
        return node;
    }
      // Função auxiliar para buscar uma chave na árvore AVL
    bool searchNode(Node* node, int key, int& comparisons) {
        comparisons++; // Incrementa a contagem de comparações
        if (node == nullptr)
            return false;
        if (key == node->key)
            return true;
        if (key < node->key)
            return searchNode(node->left, key, comparisons);
        else
            return searchNode(node->right, key, comparisons);
    }

    // Função auxiliar para encontrar o nó com a chave mínima na subárvore
    Node* findMinimumNode(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Função auxiliar para remover um nó da árvore AVL
    Node* removeNode(Node* node, int key) {
        // Realiza a remoção como em uma árvore binária de busca
        if (node == nullptr)
            return node;
        if (key < node->key)
            node->left = removeNode(node->left, key);
        else if (key > node->key)
            node->right = removeNode(node->right, key);
        else {
            // Caso tenha encontrado o nó a ser removido
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* temp = findMinimumNode(node->right);
                node->key = temp->key;
                node->right = removeNode(node->right, temp->key);
            }
        }

        // Se a árvore possuir apenas um nó ou nenhum, retorna o nó atual
        if (node == nullptr)
            return node;

        // Atualiza a altura e balanceia o nó
        return balanceNode(node);
    }
};
#endif