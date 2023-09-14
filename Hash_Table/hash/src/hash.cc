#include <iostream>
#include <vector>

#include "hash.h"

using namespace std;

Hash::Hash(int size, HashFunction *hash_fn)
{
    this->_hash_fn = hash_fn;
    this->_table_size = size;
    this->_n_collisions = 0;
    this->_hash_table.resize(size);
}

Hash::~Hash()
{
    // TODO: Implementar o destrutor
    //  Percorrer a tabela e deletar as listas encadeadas
    for (int i = 0; i < this->_table_size; i++)
    {
        if (this->_hash_table[i] != nullptr)
        {
            delete this->_hash_table[i];
        }
    }
}

ListNode *Hash::insert(int key)
{
    // TODO: Implementar a inserção
    //  Chamar a função _hash_fn para calcular o índice
    int index = this->_hash_fn(key, this->_table_size);
    if (this->_hash_table[index] != nullptr)
        // Atualizar o número de colisões se a lista não estiver vazia
        this->_n_collisions++;
    else
        this->_hash_table[index] = new List();

    // Inserir na lista encadeada que está no índice calculado
    return this->_hash_table[index]->insert(key);
    // Retornar um ponteiro para o valor inserido
}

ListNode *Hash::lookup(int key)
{
    // TODO: Implementar a busca
    //  Chamar a função hash_fn para calcular o índice
    int index = this->_hash_fn(key, this->_table_size);
    // Buscar na lista encadeada que está no índice calculado
    if (this->_hash_table[index] != nullptr)
    {
        // Retornar um ponteiro para o valor buscado
        return this->_hash_table[index]->search(key);
    }
    return nullptr;
}

int Hash::getCollisions() const
{
    return this->_n_collisions;
}
