#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "rb_tree.h"
#include "siga.h"
#include "tools.h"
#include "sort.h"

using namespace std;

// Implemente aqui testes para busca de arvore vermelho-preto
int main(int argc, char *argv[]) {
    Siga::Siga siga;
    siga.InitDatabase("estudantes"); //Database inicializado
    std::vector<Siga::Estudante> data; //Vetor de estudantes
    std::vector<int> idx = Siga::Tools::get_random_int_vector(TEST_VECTOR_SIZE, siga.ObterNumeroEstudantes()); //Vetor de indices aleatorios

    if (siga.ObterNumeroEstudantes() < TEST_VECTOR_SIZE) {
        cout << "SIGA: Erro ao gerar vetor de indices aleatorios" << endl;
        return -1;
    }

    siga.ExtraiaEstudantes(idx, data);

    if (data.size() != TEST_VECTOR_SIZE) {
        cout << "SIGA: Erro ao extrair estudantes" << endl;
        return -1;
    }

    RBTree<int> tree;
    for (auto estudante: data) {
        tree.inserir(estudante.ObterMatricula());
    }


if (!tree.isRBTree())
        return -1;
int aux = 0;
    for (auto estudante: data) {
        Node_RB<int> *node = tree.search(estudante.ObterMatricula(), aux);
        if (node->getKey() != estudante.ObterMatricula()) {
            cout << "SIGA: Erro ao buscar estudante" << endl;
            return -1;
        }
    }

    return 0;
}