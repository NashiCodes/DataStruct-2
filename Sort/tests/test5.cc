
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

#include "../include/siga.h"
#include "../include/tools.h"
#include "../include/sort.h"

#define VECTOR_SIZE 1000

struct ClassGreaterThanCompare
{
  bool operator()(Siga::Estudante &a, Siga::Estudante &b, Perf::PerformanceCounter *counter)
  {
    return std::strcmp(a.ObterNome(), b.ObterNome()) > 0;
  }
} GreatThanName;

struct
{
  bool operator()(Siga::Estudante &a, Siga::Estudante &b, Perf::PerformanceCounter *counter) const
  {
    return std::strcmp(a.ObterNome(), b.ObterNome()) < 0;
  }
} LessThanName;

struct
{
  bool operator()(Siga::Estudante &a, Siga::Estudante &b) const
  {
    return std::strcmp(a.ObterNome(), b.ObterNome()) == 0;
  }
} EqualName;

// Insere um estudante no gerencia_siga e imprime
// o numero de estudantes armazenados
int main(int argc, char *argv[])
{
  Siga::Siga siga;
  siga.InitDatabase("estudantes");
  std::vector<Siga::Estudante> data;
  std::vector<int> idx = Siga::Tools::get_random_int_vector(TEST_VECTOR_SIZE, siga.ObterNumeroEstudantes());

  if (siga.ObterNumeroEstudantes() < TEST_VECTOR_SIZE)
  {
    cout << "SIGA: Erro ao gerar vetor de indices aleatorios" << endl;
    return -1;
  }

  siga.ExtraiaEstudantes(idx, data);
  // Copia os dados para um vetor de dados
  if (data.size() != TEST_VECTOR_SIZE)
  {
    cout << "SIGA: Erro ao extrair estudantes" << endl;
    return -1;
  }

  Sort::HeapSort(data, GreatThanName);

  if (!Siga::Tools::is_sorted(data, LessThanName))
  {
    cout << "SIGA: Erro ao ordenar estudantes por nome" << endl;
    return -1;
  }

  return 0;
}
