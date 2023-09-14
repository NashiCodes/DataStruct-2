#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "b_tree.h"
#include "siga.h"
#include "tools.h"
#include "sort.h"

using namespace std;

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

    BTree tree(2);
    for (auto estudante: data) {
        tree.insert(estudante.ObterMatricula());
    }


    if (!tree.isBTree(tree))
        return -1;
    int comparisons = 0;
    for (auto estudante: data) {
        if (tree.search(estudante.ObterMatricula(), comparisons) == -1) {
            cout << "SIGA: Erro ao buscar estudante" << endl;
            return -1;
        }
    }

    return 0;
}