# Ordenação de Dados em C++

## 🤓 Resumo

Objetivo dessa atividade é implementar os principais algoritmos de ordenação baseados em comparações  🚀

Espera-se que ao final desta atividade você seja capaz de classificar informaçoes usando diferentes métodos de ordenação e compreender os principais conceitos e analisar o desempenho deles ao serem empregados em uma base de dados reais.

## Atividade :

Nesta atividades, desejamos aprimorar o nosso sistema SIGA. 
Além de manipular o cadastro de informações de estudantes em um arquivo binário, iremos agora classificar as
informações baseados em uma determinada chave de comparação.

### Etapas:

1. Copiar as rotinas do [siga.cc](src/siga.cc) que foram desenvolvidas na atividada prática anterior para o arquivo siga.cc atual. 
2. Alterar a rotina de leitura de dados do arquivo CSV. Observe que novas colunas foram inseridas no arquivo *estundantes.csv*. Alterações em outras partes do código serão necessárias para evitar BUGs. Indetifique-as e faça as correções necessárias.
3. Implementar as rotinas de ordenação no arquivo [sort.h](include/sort.h). Seguir as indicações nas marcações **TODO**.
4. Verificar se as rotinas passam nos testes definidos na pasta tests. Observem como os testes foram feitos e implementados. Há alguma falha neles?
6. Implementar o programa de análise de desempenho [desempenho.cc](app/performance.cc). Seguir as indicações nas marcações **TODO**.
7. Implementar o programa de classificação dos estudantes por nome e turma. Novamente, vocês devem seguir as marcações **TODO** no arquivo. A classificação deve gerar uma arquivo csv chamando *classificado.csv* na pasta dados.

## Organização do Projeto 

O projeto está organizado na seguinte estrutura de arquivos:

src
  - [estudante.h](src/estudante.h) e [estudante.cc](src/estudante.cpp) : Implementa a entidade estudante
  - [siga.h](include/siga.h) e [siga.cc](src/siga.cc): Implementa um sistema simplista de gerenciamento de estudante.
  - [sort.h](include/sort.h): Implementa as rotinas de ordenação usando templates c++.
  - [tools.h](include/tools.h) e [tools.cc](src/tools.cc):  implementa rotinas auxiliares para a verificação dos casos de testes e na medição de desempenho.
  
test
  - [test1.cc](tests/test1.cc):  Testa se a entrada da base de dados está correta.   
  - [test2.cc](tests/test2.cc):  Testa a ordenação do algoritmo ordenação BasicSort está correta.
  - [test3.cc](tests/test3.cc):  Testa a ordenação do algoritmo ordenação MergeSort está correta.
  - [test4.cc](tests/test4.cc):  Testa a ordenação do algoritmo ordenação QuickSort está correta. 
  - [test5.cc](tests/test5.cc):  Testa a ordenação do algoritmo ordenação HeapSort está correta.
  - [test6.cc](tests/test6.cc):  Testa a ordenação do algoritmo ordenação MySort   está correta.

app
  - [performance.cc](app/performance.cc): Gera um relatório de performance entre os métodos.
  - [classifica.cc](app/classifica.cc): Gera um arquivo texto em formato csv classificando os alunos por turma e nome em ordem ascendente.

**IMPORTANTE**
 - Detalhes do que deve ser feito encontram-se no arquivos fontes sob a tag **TODO**.
 - Os arquivos da pasta tests não devem ser modificados.
 - Os arquivos serão lidos ou criados na pasta [tests/data](tests/data)
 - Fiquem a vontade para alterar ou adicionar outras ferramentas nos arquivos [tools.h](include/tools.h) e [tools.cc](src/tools.cc)

### Compilação e Execução: 

Para a compilação em ambiente Unix/linux, use o comando:

 - Crie um diretório build
  ```
    mkdir build
  ```
 - Entre no diretório

  ```
    cd build
  ```
  - Chame o cmake
 
  ```
    cmake ../.
  ```
  - Compile os testes:
  
  ```
    make 
  ```
  
  - Rode os testes:
   
  ```
    ctest
  ```
  
  - Para rodar o estudo de desempenho:
   ```
    ./app/performance

  ```
  
  - Para rodar a classificação:
   ```
    ./app/classifica
    
  ```

*Importante:* Entre uma chamadas do ctest, remova o arquivo estudantes.bin da pasta tests/data.