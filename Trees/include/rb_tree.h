#ifndef RB_TREE_H
#define RB_TREE_H

#include "Node_RB.h"

using namespace std;

// TODO: Implementar a árvore rubro-negra aqui e classes auxiliares (se necessário)
template<typename T>
class RBTree {
public:
    RBTree<T>();         // construtor
    ~RBTree() = default; // destrutor
    void inserir(T key); // insere um novo nó na árvore
    void remover(T key); // remove um nó da árvore
    Node_RB<T> *search(T key, int &comparisons);     // busca um nó na árvore
    void imprimir();     // imprime a árvore
    bool isRBTree();     // verifica se a árvore é uma árvore rubro-negra
    int rbRotations; // Variável para contar o número de rotações

private:
    Node_RB<T> *root;                    // raiz da árvore
    void insert_fixup(Node_RB<T> *node); // corrige a árvore após a inserção de um novo nó
    void left_rotate(Node_RB<T> *node);  // rotaciona a árvore para a esquerda
    void right_rotate(Node_RB<T> *node); // rotaciona a árvore para a direita

    void auxImprimir(Node_RB<T> *node, const std::string &prefix, bool isLeft, std::ostream &out); // imprime a árvore

    bool auxIsRBTree(Node_RB<T> *node);                 // verifica se a árvore é uma árvore rubro-negra
    Node_RB<T> *auxSearch(Node_RB<T> *node, T key, int &comparisons);     // busca um nó na árvore
    void transplant(Node_RB<T> *node, Node_RB<T> *aux); // substitui um nó por outro
    Node_RB<T> *maxLeft(Node_RB<T> *node);              // retorna o nó com a maior chave à esquerda
    void remove_fixup(Node_RB<T> *node);                // corrige a árvore após a remoção de um nó


};

template<typename T>
RBTree<T>::RBTree() {
    root = nullptr;
    rbRotations = 0; // Inicializa a contagem de rotações como zero
}

template<typename T>
void RBTree<T>::inserir(T key) {
    Node_RB<T> *p = new Node_RB<T>(key); // cria um novo nó
    if (this->root == nullptr)           // se a árvore estiver vazia, o novo nó será a raiz
    {
        this->root = p;     // o novo nó é a raiz
        p->setColor(false); // a raiz é preta
        return;             // sai da função
    }

    for (Node_RB<T> *q = this->root; q != nullptr;) // percorre a árvore
    {
        if (p->getKey() < q->getKey()) // se a chave do novo nó for menor que a chave do nó atual
        {
            if (q->getLeft() == nullptr) // se o filho esquerdo do nó atual for nulo
            {
                q->setLeft(p);   // o filho esquerdo do nó atual será o novo nó
                p->setParent(q); // o pai do novo nó será o nó atual
                break;           // sai do loop
            } else // se o filho esquerdo do nó atual não for nulo
            {
                q = q->getLeft(); // o nó atual será o filho esquerdo do nó atual
            }
        } else // se a chave do novo nó for maior que a chave do nó atual
        {
            if (q->getRight() == nullptr) // se o filho direito do nó atual for nulo
            {
                q->setRight(p);  // o filho direito do nó atual será o novo nó
                p->setParent(q); // o pai do novo nó será o nó atual
                break;           // sai do loop
            } else // se o filho direito do nó atual não for nulo
            {
                q = q->getRight(); // o nó atual será o filho direito do nó atual
            }
        }
    }

    insert_fixup(p); // conserta a árvore
}

template<typename T>
void RBTree<T>::insert_fixup(Node_RB<T> *node) {
    if (node == this->root) // se o novo nó for a raiz
    {
        node->setColor(false); // a raiz será preta
        return;                // sai da função
    }

    Node_RB<T> *pai = node->getParent(); // pai do novo nó
    Node_RB<T> *avo = pai->getParent();  // avô do novo nó
    Node_RB<T> *tio;                     // tio do novo nó

    if (!pai->getColor()) // se o pai do novo nó for preto
    {
        return; // sai da função
    } else {
        if (pai == avo->getLeft()) // se o pai do novo nó for o filho esquerdo do avô do novo nó
        {
            tio = avo->getRight();                 // o tio do novo nó será o filho direito do avô do novo nó
            if (tio != nullptr && tio->getColor()) // se o tio do novo nó for vermelho
            {
                pai->setColor(false); // o pai do novo nó será preto
                tio->setColor(false); // o tio do novo nó será preto
                avo->setColor(true);  // o avô do novo nó será vermelho
                insert_fixup(avo);    // conserta a árvore
            } else // se o tio do novo nó for preto
            {
                if (node == pai->getRight()) // se o novo nó for o filho direito do pai do novo nó
                {
                    node = pai;              // o novo nó será o pai do novo nó
                    left_rotate(node);       // rotaciona o novo nó à esquerda
                    pai = node->getParent(); // pai do novo nó
                    avo = pai->getParent();  // avô do novo nó
                    pai->setColor(false);    // o pai do novo nó será preto
                    avo->setColor(true);     // o avô do novo nó será vermelho
                    right_rotate(avo);       // rotaciona o avô do novo nó à direita
                } else // se o novo nó for o filho esquerdo do pai do novo nó
                {
                    pai->setColor(false); // o pai do novo nó será preto
                    avo->setColor(true);  // o avô do novo nó será vermelho
                    right_rotate(avo);    // rotaciona o avô do novo nó à direita
                }
            }
        } else // se o pai do novo nó for o filho direito do avô do novo nó
        {
            tio = avo->getLeft();                  // o tio do novo nó será o filho esquerdo do avô do novo nó
            if (tio != nullptr && tio->getColor()) // se o tio do novo nó for vermelho
            {
                pai->setColor(false); // o pai do novo nó será preto
                tio->setColor(false); // o tio do novo nó será preto
                avo->setColor(true);  // o avô do novo nó será vermelho
                insert_fixup(avo);    // conserta a árvore
            } else // se o tio do novo nó for preto
            {
                if (node == pai->getLeft()) // se o novo nó for o filho esquerdo do pai do novo nó
                {
                    node = pai;              // o novo nó será o pai do novo nó
                    right_rotate(node);      // rotaciona o novo nó à direita
                    pai = node->getParent(); // pai do novo nó
                    avo = pai->getParent();  // avô do novo nó
                    pai->setColor(false);    // o pai do novo nó será preto
                    avo->setColor(true);     // o avô do novo nó será vermelho
                    left_rotate(avo);        // rotaciona o avô do novo nó à esquerda
                } else // se o novo nó for o filho direito do pai do novo nó
                {
                    pai->setColor(false); // o pai do novo nó será preto
                    avo->setColor(true);  // o avô do novo nó será vermelho
                    left_rotate(avo);     // rotaciona o avô do novo nó à esquerda
                }
            }
        }
    }

    this->root->setColor(false); // a raiz será preta
}

template<typename T>
void RBTree<T>::left_rotate(Node_RB<T> *node) {
    Node_RB<T> *q = node->getRight(); // nó que será rotacionado

    node->setRight(
            q->getLeft()); // o filho direito do nó que será rotacionado será o filho esquerdo do nó que será rotacionado
    if (q->getLeft() != nullptr) {
        q->getLeft()->setParent(
                node); // o pai do filho esquerdo do nó que será rotacionado será o nó que será rotacionado
    }

    q->setParent(node->getParent()); // o pai do nó que será rotacionado será o pai do nó que será rotacionado
    if (node->getParent() == nullptr) {
        this->root = q; // se o pai do nó que será rotacionado for nulo, o nó que será rotacionado será a raiz
    } else {
        if (node ==
            node->getParent()->getLeft()) // se o nó que será rotacionado for o filho esquerdo do pai do nó que será rotacionado
        {
            node->getParent()->setLeft(
                    q); // o filho esquerdo do pai do nó que será rotacionado será o nó que será rotacionado
        } else // se o nó que será rotacionado for o filho direito do pai do nó que será rotacionado
        {
            node->getParent()->setRight(
                    q); // o filho direito do pai do nó que será rotacionado será o nó que será rotacionado
        }
    }
    rbRotations++; // Incrementa a contagem de rotações
    q->setLeft(node);   // o filho esquerdo do nó que será rotacionado será o nó que será rotacionado
    node->setParent(q); // o pai do nó que será rotacionado será o nó que será rotacionado
}

template<typename T>
void RBTree<T>::right_rotate(Node_RB<T> *node) {
    Node_RB<T> *q = node->getLeft(); // nó que será rotacionado

    node->setLeft(
            q->getRight()); // o filho esquerdo do nó que será rotacionado será o filho direito do nó que será rotacionado
    if (q->getRight() != nullptr) {
        q->getRight()->setParent(
                node); // o pai do filho direito do nó que será rotacionado será o nó que será rotacionado
    }

    q->setParent(node->getParent()); // o pai do nó que será rotacionado será o pai do nó que será rotacionado
    if (node->getParent() == nullptr) {
        this->root = q; // se o pai do nó que será rotacionado for nulo, o nó que será rotacionado será a raiz
    } else {
        if (node ==
            node->getParent()->getRight()) // se o nó que será rotacionado for o filho direito do pai do nó que será rotacionado
        {
            node->getParent()->setRight(
                    q); // o filho direito do pai do nó que será rotacionado será o nó que será rotacionado
        } else // se o nó que será rotacionado for o filho esquerdo do pai do nó que será rotacionado
        {
            node->getParent()->setLeft(
                    q); // o filho esquerdo do pai do nó que será rotacionado será o nó que será rotacionado
        }
    }
    rbRotations++; // Incrementa a contagem de rotações
    q->setRight(node);  // o filho direito do nó que será rotacionado será o nó que será rotacionado
    node->setParent(q); // o pai do nó que será rotacionado será o nó que será rotacionado
}

template<typename T>
void RBTree<T>::imprimir() {
    auxImprimir(this->root, "", false, std::cout);
}

template<typename T>
void RBTree<T>::auxImprimir(Node_RB<T> *node, const std::string &prefix, bool isLeft, std::ostream &out) {
    if (node == nullptr)
        return;

    out << prefix;
    out << (isLeft ? "├──" : "└──");

    // imprimir o valor do nó
    out << "[" << node->getKey() << ", " << (node->getColor() ? "R" : "B") << "]" << std::endl;

    // enter the next tree level - left and right branch
    auxImprimir(node->getLeft(), prefix + (isLeft ? "│   " : "    "), true, out);
    auxImprimir(node->getRight(), prefix + (isLeft ? "│   " : "    "), false, out);
}

template<typename T>
bool RBTree<T>::isRBTree() {
    return auxIsRBTree(this->root);
}

template<typename T>
bool RBTree<T>::auxIsRBTree(Node_RB<T> *node) {
    if (node == nullptr) // se o nó for nulo, retorna verdadeiro
        return true;

    if (node->getColor() == true) { // se o nó for vermelho
        if (node->getLeft() != nullptr &&
            node->getLeft()->getColor() == true) // se o filho esquerdo do nó for vermelho
            return false;                        // retorna falso

        if (node->getRight() != nullptr &&
            node->getRight()->getColor() == true) // se o filho direito do nó for vermelho
            return false;                         // retorna falso
    }

    return auxIsRBTree(node->getLeft()) &&
           auxIsRBTree(node->getRight()); // retorna verdadeiro se os dois nós forem pretos
}

template<typename T>
Node_RB<T> *RBTree<T>::search(T key, int &comparisons) {
    return auxSearch(this->root, key, comparisons);
}

template<typename T>
Node_RB<T> *RBTree<T>::auxSearch(Node_RB<T> *node, T key, int &comparisons) {
    if (node == nullptr || node->getKey() == key) {
        comparisons++; // Incrementa a contagem de comparações na comparação de chaves
        return node;
    }

    comparisons++; // Incrementa a contagem de comparações na comparação de chaves

    if (key < node->getKey()) {
        comparisons++; // Incrementa a contagem de comparações para percorrer a árvore
        return auxSearch(node->getLeft(), key, comparisons);
    }

    comparisons++; // Incrementa a contagem de comparações para percorrer a árvore
    return auxSearch(node->getRight(), key, comparisons);
}


template<typename T>
void RBTree<T>::remover(T key) {
    int comparisons = 0;
    Node_RB<T> *node = auxSearch(this->root, key, comparisons); // nó que será removido
    Node_RB<T> *aux;                               // nó auxiliar
    if (node == nullptr)                           // se o nó for nulo, retorna
        return;
    if (node->isLeaf()) {
        if (node->getParent() == nullptr)
            this->root = nullptr;
        else if (node == node->getParent()->getLeft())
            node->getParent()->setLeft(nullptr);
        else
            node->getParent()->setRight(nullptr);
        delete node;
    } else {
        if (node->getLeft() != nullptr && node->getRight() != nullptr) {
            aux = maxLeft(node->getLeft());
            node->setKey(aux->getKey());
            node = aux->getLeft();
            transplant(aux, node);
            delete aux;
            if (node != nullptr)
                remove_fixup(node);
        } else if (node->getLeft() != nullptr) {
            transplant(node, node->getLeft());
            aux = node->getLeft();
            delete node;
            remove_fixup(aux);
        } else {
            transplant(node, node->getRight());
            aux = node->getRight();
            delete node;
            remove_fixup(aux);
        }
    }
}

template<typename T>
void RBTree<T>::transplant(Node_RB<T> *node, Node_RB<T> *aux) {
    if (node->getParent() == nullptr)
        this->root = aux;
    else if (node == node->getParent()->getLeft())
        node->getParent()->setLeft(aux);
    else
        node->getParent()->setRight(aux);

    if (aux != nullptr)
        aux->setParent(node->getParent());
}

template<typename T>
void RBTree<T>::remove_fixup(Node_RB<T> *node) {
    while (node != this->root && node->getColor() == false) {
        if (node == node->getParent()->getLeft()) {
            Node_RB<T> *aux = node->getParent()->getRight();
            if (aux->getColor() == true) {
                aux->setColor(false);
                node->getParent()->setColor(true);
                left_rotate(node->getParent());
                aux = node->getParent()->getRight();
            }
            if (aux->getLeft()->getColor() == false && aux->getRight()->getColor() == false) {
                aux->setColor(true);
                node = node->getParent();
            } else {
                if (aux->getRight()->getColor() == false) {
                    aux->getLeft()->setColor(false);
                    aux->setColor(true);
                    right_rotate(aux);
                    aux = node->getParent()->getRight();
                }
                aux->setColor(node->getParent()->getColor());
                node->getParent()->setColor(false);
                aux->getRight()->setColor(false);
                left_rotate(node->getParent());
                node = this->root;
            }
        } else {
            Node_RB<T> *aux = node->getParent()->getLeft();
            if (aux->getColor() == true) {
                aux->setColor(false);
                node->getParent()->setColor(true);
                right_rotate(node->getParent());
                aux = node->getParent()->getLeft();
            }
            if (aux->getRight()->getColor() == false && aux->getLeft()->getColor() == false) {
                aux->setColor(true);
                node = node->getParent();
            } else {
                if (aux->getLeft()->getColor() == false) {
                    aux->getRight()->setColor(false);
                    aux->setColor(true);
                    left_rotate(aux);
                    aux = node->getParent()->getLeft();
                }
                aux->setColor(node->getParent()->getColor());
                node->getParent()->setColor(false);
                aux->getLeft()->setColor(false);
                right_rotate(node->getParent());
                node = this->root;
            }
        }
    }
    node->setColor(false);
}

template<typename T>
Node_RB<T> *RBTree<T>::maxLeft(Node_RB<T> *node) {
    while (node->getRight() != nullptr)
        node = node->getRight();

    return node;
}

#endif /* RB_TREE_H */