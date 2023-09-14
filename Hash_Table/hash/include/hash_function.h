#ifndef HASH_FUNCTION_H
#define HASH_FUNCTION_H

#include <cmath>

/* Função de hash que retorna o resto da divisão */
int hash_divide(int key, int table_size)
{
    return key % table_size;
}

/* Função hash multiplicacap */
int hash_multiply(int key, int table_size)
{
    return floor(table_size * (key * 0.6180339887 - floor(key * 0.6180339887)));
}

/* Funçao minha hash Enlaçamento Limite*/
int hash_my_func(int key, int table_size)
{
    // TODO: Implementar a função de hash de Enlaçamento Limite
    int hash = 0;
    int i = 0;
    while (key > 0)
    {
        hash += (key % 10) * pow(10, i);
        key /= 10;
        i++;
    }
    return hash % table_size;
}

#endif /* HASH_FUNCTION_H */
