#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <random>
#include "rb_tree.h"
#include "siga.h"
#include "tools.h"
#include "sort.h"

using namespace std;

int numAleatorio() {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dis(0, TEST_VECTOR_SIZE - 1);
    return dis(mt);
}

// Implemente aqui testes para remoção de arvore vermelho-preto
int main() {

    Siga::Siga siga;
    siga.InitDatabase("estudantes"); //Database inicializado
    std::vector<Siga::Estudante> data; //Vetor de estudantes
    std::vector<int> idx = Siga::Tools::get_random_int_vector(TEST_VECTOR_SIZE,
                                                              siga.ObterNumeroEstudantes()); //Vetor de indices aleatorios

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


    int num = numAleatorio();
    cout << "Matricula que sera removida: " << data[num].ObterMatricula() << endl;
    tree.remover(data[num].ObterMatricula());
    int aux = 0;
    Node_RB<int> *node = tree.search(data[num].ObterMatricula(), aux);
    if (node != nullptr) {
        return -1;
    }

    if (!tree.isRBTree())
        return -1;

    return 0;
}