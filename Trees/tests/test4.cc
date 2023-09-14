#include <iostream>
#include <fstream>
#include <string>
#include "b_tree.h"
#include "siga.h"
#include "tools.h"


using namespace std;


int main() {
// Implemente aqui testes para inserção de arvore vermelho-preto
    Siga::Siga siga;
    siga.InitDatabase("estudantes");
    std::vector<Siga::Estudante> data;
    std::vector<int> idx = Siga::Tools::get_random_int_vector(TEST_VECTOR_SIZE, siga.ObterNumeroEstudantes());

    if (siga.ObterNumeroEstudantes() < TEST_VECTOR_SIZE) {
        cout << "SIGA: Erro ao gerar vetor de indices aleatorios" << endl;
        return -1;
    }

    siga.ExtraiaEstudantes(idx, data);

    if (data.size() != TEST_VECTOR_SIZE) {
        cout << "SIGA: Erro ao extrair estudantes" << endl;
        return -1;
    }

    BTree tree(2);
    for (auto estudante: data) {
        tree.insert(estudante.ObterMatricula());
    }
    if (!tree.isBTree(tree))
        return -1;

    return 0;
}