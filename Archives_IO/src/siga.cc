#include <string>
#include <sstream>

using namespace std;

#include "siga.h"
#include "config.h"

Siga::Siga()
{
    this->arquivo_nome = "";
    this->n_estudantes = 0;
}

void Siga::SetDatabase(string arquivo_dados_estudante)
{

    this->arquivo_nome = INPUT_DATA_DIR + arquivo_dados_estudante;

    // Obter numero de estudantes no arquivo
    // Se o arquivo não existir, o numero de estudantes é zero
    // Se o arquivo existir, o numero de estudantes é o numero de registros no arquivo
    //  o numero de estudantes é armazenado no atributo n_estudantes

    this->file_stream = fstream(this->arquivo_nome, ios::in | ios::out | ios::binary);
    cout << "SIGA: Inicializado com sucesso" << endl;

    // arquivo nao existe ainda
    if (!this->file_stream.is_open())
    {

        // cria um arquivo vazio
        ofstream out(arquivo_nome, ios::binary);
        out.close();
        // reabre para leitura e escrita
        this->file_stream = fstream(this->arquivo_nome, ios::in | ios::out | ios::binary);
        if (!this->file_stream.is_open())
        {
            cout << "SIGA: Erro ao criar arquivo de dados de estudante" << endl;
            return;
        }
    }

    this->file_stream.seekg(0, this->file_stream.end);
    int length = this->file_stream.tellg();
    this->file_stream.seekg(0, this->file_stream.beg);
    this->n_estudantes = length / sizeof(Estudante);

    cout << this->n_estudantes << " registros de estudantes" << endl;
}

void Siga::LerCSV(string arquivo_csv)
{
    // Implementação leitura de arquivo CSV
    //  Passos:
    //  Abrir arquivo CSV

    string arquivo_csv_path = INPUT_DATA_DIR + arquivo_csv;
    ifstream csv_file;
    csv_file.open(arquivo_csv_path);
    if (!csv_file.is_open())
    {
        cout << "Erro ao abrir arquivo CSV" << endl;
        return;
    }
    // Ler cabeçalho
    string line;
    getline(csv_file, line);

    // Para cada linha de dados
    while (getline(csv_file, line))
    {
        // Ler um estudante do arquivo CSV
        Estudante est;
        stringstream ss(line);
        string token;
        getline(ss, token, ',');
        est.TrocarNome(token.c_str());
        getline(ss, token, ',');
        est.TrocarMatricula(stoi(token));
        getline(ss, token, ',');
        est.TrocarAnoIngresso(stoi(token));
        getline(ss, token, '\n');
        est.TrocarIRA(stof(token));

        // Escrever o objeto estudante no arquivo binário
        this->EscrevaEstudante(this->n_estudantes, est);

        // Atualize o numero de estudantes no atributo n_estudantes
        this->n_estudantes++;
    }
    // Fim-Para
    // Fechar arquivo CSV
    csv_file.close();

    cout << this->n_estudantes << " registros de estudantes" << endl;
}

int Siga::PesquisaPorMatricula(int matricula)
{
    Estudante est;
    // TODO: implementar pesquisa por matrícula
    // Posicione o cursor para o inicio do arquivo:
    this->file_stream.seekg(0 * sizeof(Estudante), this->file_stream.beg);

    // Para i = 0 até n_estudante
    for (int i = 0; i < this->ObterNumeroEstudantes(); i++)
    {
        //    Ler estudante na posição corrente no arquivo
        this->LeiaEstudante(i, est);
        //    Testar se é a matricula procurada, se afirmativo
        //    retorne a posiçao i.
        if (est.ObterMatricula() == matricula)
            return i;
    }
    // Fim-Para
    // Coloque o cursor para o final do arquivo
    this->file_stream.seekg(0, this->file_stream.end);
    // retorne -1
    return -1;
}

void Siga::AdicionaEstudante(Estudante est)
{
    // TODO: Implementar cadastro de estudante
    // Passos:

    // Testar se est já foi cadastrado
    // Se já cadastrado, retorne sem fazer nada
    if (PesquisaPorMatricula(est.ObterMatricula()) != (-1))
        return;
    // Caso Contrário, adicione o estudante no final do arquivobinário
    else
        this->EscrevaEstudante(this->n_estudantes, est);
    // e incremente o numero de estudantes
    this->n_estudantes++;
}

Estudante Siga::ObterEstudante(int idx)
{
    Estudante est;
    // TODO: implementar obter estudante
    // Leia o estudante na posição idx
    if (idx >= 0 && idx < this->ObterNumeroEstudantes())
        this->LeiaEstudante(idx, est);
    else
        exit(1);
    // Retorne o estudante
    return est;
}

void Siga::SalvaCSV(string arquivo_csv)
{
    string arquivo_csv_path = INPUT_DATA_DIR + arquivo_csv;
    // TODO: implementar salvamento de arquivo CSV
    Estudante est;

    // Passos:
    // Abrir arquivo CSV
    ofstream New_csv(arquivo_csv_path, ios::out);
    if (New_csv.is_open())
    {
        // Escrever cabeçalho
        New_csv << "Nome;Matricula;Ano;Ira" << endl;
        // Posicione o cursor para o inicio do arquivo binário
        this->file_stream.seekg(0 * sizeof(Estudante), this->file_stream.beg);
        // Para cada linha de dados
        for (int i = 0; i < this->ObterNumeroEstudantes(); i++)
        {
            //    Ler um estudante do arquivo binário
            this->LeiaEstudante(i, est);
            //    Escrever o objeto estudante no arquivo CSV
            New_csv << est.ObterNome() << ", ";
            New_csv << est.ObterMatricula() << ", ";
            New_csv << est.ObterAnoIngresso() << ", ";
            New_csv << est.ObterIRA() << endl;
        }
        // Fim-Para
    }
    // Fechar arquivo CSV
    New_csv.close();
}

void Siga::AlteraCadastroEstudante(int idx, Estudante est)
{
    // TODO: implementar alteração de cadastro de estudante
    // Passos:
    // Escreva o estudante na posição idx
    this->EscrevaEstudante(idx, est);
    // Saia da função
    return;
}

Siga::~Siga()
{
    this->file_stream.close();
}

int Siga::ObterNumeroEstudantes()
{
    return this->n_estudantes;
}

void Siga::LeiaEstudante(int idx, Estudante &est)
{
    this->file_stream.seekg(idx * sizeof(Estudante), this->file_stream.beg);
    this->file_stream.read((char *)&est, sizeof(Estudante));
}

void Siga::EscrevaEstudante(int idx, Estudante est)
{
    this->file_stream.seekp(idx * sizeof(Estudante), this->file_stream.beg);
    this->file_stream.write((char *)&est, sizeof(Estudante));
}