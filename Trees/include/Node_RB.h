#ifndef NODE_RB_H
#define NODE_RB_H

template <typename T>
class Node_RB
{
public:
    explicit Node_RB(T key) : key(key), left(nullptr), right(nullptr), parent(nullptr), color(true) {}
    ~Node_RB() = default;

    void setKey(T key) { this->key = key; }            // seta a chave do nó
    void setLeft(Node_RB *p) { this->left = p; };      // seta o filho esquerdo do nó
    void setRight(Node_RB *p) { this->right = p; };    // seta o filho direito do nó
    void setParent(Node_RB *p) { this->parent = p; }   // seta o pai do nó
    void setColor(bool color) { this->color = color; } // seta a cor do nó

    T getKey() { return key; };                    // retorna a chave do nó
    Node_RB *getLeft() { return this->left; };     // retorna o filho esquerdo do nó
    Node_RB *getRight() { return this->right; };   // retorna o filho direito do nó
    Node_RB *getParent() { return this->parent; }; // retorna o pai do nó
    bool getColor() { return this->color; }        // retorna a cor do nó

    bool isLeaf() {return this->left == NULL && this->right == NULL;}

private:
    T key;
    Node_RB *left;
    Node_RB *right;
    Node_RB *parent;
    bool color; // true = red, false = black
};

#endif // NODE_RB_H
