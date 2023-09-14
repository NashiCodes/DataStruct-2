#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "avl_tree.h"
#include "b_tree.h"
#include "rb_tree.h"
#include "siga.h"
#include "sort.h"
#include "tools.h"

struct AscendingCompare {
    bool operator()(int a, int b) const {
        return a < b;
    }
};

int main(int argc, const char* argv[])
{
    // Tamanhos da base de dados
    int sizes[] = {100, 1000, 10000, 100000, 1000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    // Abrir arquivo REPORT.md para escrever os resultados
    std::ofstream reportFile("REPORT.md");

    // Verificar se o arquivo foi aberto com sucesso
    if (!reportFile.is_open()) {
        std::cout << "Erro ao abrir o arquivo REPORT.md" << std::endl;
        return 1;
    }

    // Configurar a semente aleatória
    srand(time(0));

    // Loop pelos tamanhos da base de dados
    for (int i = 0; i < numSizes; i++) {
        int size = sizes[i];

        // Gerar chaves aleatórias
        int* randomKeys = new int[size];
        for (int j = 0; j < size; j++) {
            randomKeys[j] = rand();
        }

        // Ordenar as chaves
      std::vector<int> sortedKeys(randomKeys, randomKeys + size);
      Sort::QuickSort(sortedKeys, AscendingCompare());

        // Árvore AVL
        AVLTree avlTree;
        int avlRotations = 0;

        // Árvore Vermelho-Preto (Red-Black)
        RBTree<int> rbTree;
        int rbRotations = 0;

        // Loop pelas diferentes ordens da árvore B
        int orders[] = {2, 4, 8, 16};
        int numOrders = sizeof(orders) / sizeof(orders[0]);

        for (int k = 0; k < numOrders; k++) {
            int order = orders[k];

            // Árvore B
                     
            BTree bTree(order);

            // Inserção de chaves aleatórias
            for (int j = 0; j < size; j++) {
                bTree.insert(randomKeys[j]);
            }

            // Medição do número de comparações na busca por uma chave na árvore AVL
            int avlComparisons = 0;
            for (int j = 0; j < size; j++) {
                avlTree.search(randomKeys[j], avlComparisons);
                avlRotations += avlTree.getRotationCount();

            }

            // Medição do número de comparações na busca por uma chave na árvore Vermelho-Preto
            int rbComparisons = 0;
            for (int j = 0; j < size; j++) {
                rbTree.search(randomKeys[j], rbComparisons);
                rbRotations += rbTree.rbRotations;
            }

            // Medição do número de comparações na busca por uma chave na árvore B
            int bComparisons = 0;
            for (int j = 0; j < size; j++) {
                bTree.search(randomKeys[j], bComparisons);
            }

            // Escrever os resultados no arquivo REPORT.md
            reportFile << "Tamanho da base de dados: " << size << std::endl;
            reportFile << "Ordem da árvore B: " << order << std::endl;
            reportFile << "Número de rotações na inserção (AVL): " << avlRotations << std::endl;
            reportFile << "Número de rotações na inserção (Vermelho-Preto): " << rbRotations << std::endl;
            reportFile << "Número de comparações na busca (AVL): " << avlComparisons << std::endl;
            reportFile << "Número de comparações na busca (Vermelho-Preto): " << rbComparisons << std::endl;
            reportFile << "Número de comparações na busca (B): " << bComparisons << std::endl;
            reportFile << std::endl;
        }

        // Liberar a memória alocada
        delete[] randomKeys;
    }

    // Fechar o arquivo REPORT.md
    reportFile.close();

    return 0;
}


