#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib> ///rand()
#include <ctime>   ///time()

#include "../include/siga.h"
#include "../include/sort.h"
#include "../include/tools.h"
#include "../src/perf.cc"

using namespace std;

int numAleatorio(int a, int b)
{
    return a + rand() % (b - a + 1); /// retorna um numero inteiro aleatorio entre a e b
}

struct
{
    bool operator()(Siga::Estudante &a, Siga::Estudante &b, Perf::PerformanceCounter *counter) const
    {
        counter->increment_comparisons();
        return std::strcmp(a.ObterNome(), b.ObterNome()) < 0;
    }
} LessThanName;

struct ClassGreaterThanCompare
{
    bool operator()(Siga::Estudante &a, Siga::Estudante &b, Perf::PerformanceCounter *counter)
    {
        counter->increment_comparisons();
        return std::strcmp(a.ObterNome(), b.ObterNome()) > 0;
    }
} GreatThanName;

int main(int argc, const char *argv[])
{
    // TODO: Implementar teste de performance considerando aleatórios
    // Chame as rotinas de ordenação:
    //  BasicSort, MergeSort, QuickSort, HeapSort, MySort
    // e meça tempo de execução, número de comparações e trocas.
    // Use diferentes tamanhos de vetores para testar.
    srand(time(NULL));
    Siga::Siga siga;
    siga.InitDatabase("estudantes");
    vector<Siga::Estudante> estudantes;
    vector<int> tam = Siga::Tools::get_random_int_vector(numAleatorio(100, 5000), siga.ObterNumeroEstudantes());

    //----------------------------------------------------------------

    Perf::PerformanceTimer *timer = new Perf::PerformanceTimer();

    //----------------------------------------------------------------
    // Basic Sort
    siga.ExtraiaEstudantes(tam, estudantes);
    Sort::BasicSort(estudantes, LessThanName);

    //----------------------------------------------------------------
    // Merge Sort
    siga.ExtraiaEstudantes(tam, estudantes);
    Sort::MergeSort(estudantes, LessThanName);

    //----------------------------------------------------------------
    //  Quick Sort
    siga.ExtraiaEstudantes(tam, estudantes);
    Sort::QuickSort(estudantes, LessThanName);

    //----------------------------------------------------------------
    // Heaps Sort
    siga.ExtraiaEstudantes(tam, estudantes);
    Sort::HeapSort(estudantes, GreatThanName);
    
    //----------------------------------------------------------------
    // Tim Sort
    siga.ExtraiaEstudantes(tam, estudantes);
    Sort::TimSort(estudantes, LessThanName);


    // Verifique o depemepenho usando
    //    (1) vetores de inteiros de diferentes tamanhos
    //    (2) vetores de estudantes de diferentes tamanhos
    // Observe que a base de dados tem tamanho máximo de 5000 estudantes.
    // Analise o desempenho considerando as seguintes configurações de entrada:
    //    (1) dados com distribuição aleatória. (caso médio)
    //    (2) dados com ordenação descendente (pior caso)

    // OBS.: Na implementação dos métodos de ordenação, busque por implementações eficientes.
    //       Indique os resultados obtidos no arquivo REPORT.m

    return 0;
}
