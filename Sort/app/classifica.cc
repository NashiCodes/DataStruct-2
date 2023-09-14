#include "siga.h"
#include "sort.h"
#include "tools.h"
#include <cstring>

struct {
    template <typename T>
    bool operator() (T &a, T &b) const
        {
            return std::strcmp(a.ObterNome(), b.ObterNome()) < 0;
        }
    } CompareNames;

struct {
    template <typename T>
    bool operator() (T &a, T &b) const
        {
            return std::strcmp(a.ObterCurso(), b.ObterCurso()) < 0;
        }
    } CompareCourses;

int main(int argc, const char* argv[])
{
    // TODO: Classifique os estudantes por nome e em seguinda por curso. 
    // Use os métodos mais eficientes observados no teste de performance.
    // Escreva o resultado em um arquivo CSV chamado "classificacao.csv"



    Siga::Siga siga;
    siga.LerCSV("estudantes");
    int size = siga.ObterNumeroEstudantes();

    std::vector<int> indices;
    std::vector<Siga::Estudante> estudantes;
    for(int i = 0; i < size; indices[i] = i++);

    siga.ExtraiaEstudantes(indices, estudantes);

    Sort::QuickSort(estudantes, CompareNames);
    Sort::QuickSort(estudantes, CompareCourses);

    siga.SalvaCSV("classificacao.csv", estudantes);

    return 0;

}
