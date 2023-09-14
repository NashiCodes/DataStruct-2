#ifndef B_TREE_H
#define B_TREE_H

#include <iostream>
#include <vector>


//TODO: Implemenatar a árvore B aqui e classes auxiliares (se necessário)

const int ORDER = 3;

class BTree {
private:
    struct Node {
        bool is_leaf;
        std::vector<int> keys;
        std::vector<Node*> children;

        Node(bool leaf) : is_leaf(leaf) {}
    };

    Node* root;
    int order;
       

public:
  BTree(int order) : order(order) {
        root = nullptr;
    }

    void insert(int key) {
        if (root == nullptr) {
            root = new Node(true);
            root->keys.push_back(key);
        } else {
            if (root->keys.size() == (2 * ORDER - 1)) {
                Node* new_root = new Node(false);
                new_root->children.push_back(root);
                root = new_root;
                split_child(0, root->children[0]);
            }
            insert_non_full(key, root);
        }
    }

    void insert_non_full(int key, Node* node) {
        int i = node->keys.size() - 1;

        if (node->is_leaf) {
            node->keys.push_back(0);
            while (i >= 0 && key < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
        } else {
            while (i >= 0 && key < node->keys[i])
                i--;

            if (node->children[i + 1]->keys.size() == (2 * ORDER - 1)) {
                split_child(i + 1, node->children[i + 1]);

                if (key > node->keys[i + 1])
                    i++;
            }
            insert_non_full(key, node->children[i + 1]);
        }
    }

    void split_child(int i, Node* y) {
        Node* z = new Node(y->is_leaf);
        root->keys.insert(root->keys.begin() + i, y->keys[ORDER - 1]);

        for (int j = 0; j < ORDER - 1; j++)
            z->keys.push_back(y->keys[j + ORDER]);

        y->keys.erase(y->keys.begin() + ORDER - 1, y->keys.end());

        if (!y->is_leaf) {
            for (int j = 0; j < ORDER; j++) {
                z->children.push_back(y->children[j + ORDER]);
                y->children.erase(y->children.begin() + ORDER, y->children.end());
            }
        }

        root->children.insert(root->children.begin() + i + 1, z);
    }

    void print() {
        print_node(root);
    }

    void print_node(Node* node) {
        if (node != nullptr) {
            for (int i = 0; i < node->keys.size(); i++) {
                std::cout << node->keys[i] << " ";
            }
            std::cout << std::endl;

            if (!node->is_leaf) {
                for (int i = 0; i < node->children.size(); i++) {
                    print_node(node->children[i]);
                }
            }
        }
    }
 bool search(int key, int& comparisons) {
    return search_key(key, root, comparisons);
}

   bool search_key(int key, Node* node, int & comparisons) {
    int i = 0;
    while (i < node->keys.size() && key > node->keys[i]) {
        comparisons++;
        i++;
    }

    if (i < node->keys.size() && key == node->keys[i]) {
        comparisons++;
        return true;
    }

    if (node->is_leaf)
        return false;

    comparisons++;
    return search_key(key, node->children[i], comparisons);
}


    void remove(int key) {
        if (!root) {
            std::cout << "A árvore está vazia." << std::endl;
            return;
        }

        remove_key(key, root);

        if (root->keys.empty() && !root->is_leaf) {
            Node* temp = root;
            root = root->children[0];
            delete temp;
        }
    }
     void remove_key(int key, Node* node) {
        int index = find_key_index(key, node);

        if (index < node->keys.size() && node->keys[index] == key) {
            if (node->is_leaf) {
                // Caso 1: A chave está em um nó folha
                node->keys.erase(node->keys.begin() + index);
            } else {
                // Caso 2: A chave está em um nó interno
                Node* pred = node->children[index];
                Node* succ = node->children[index + 1];

                if (pred->keys.size() >= ORDER) {
                    int predecessor = get_predecessor(index, node);
                    node->keys[index] = predecessor;
                    remove_key(predecessor, pred);
                } else if (succ->keys.size() >= ORDER) {
                    int successor = get_successor(index, node);
                    node->keys[index] = successor;
                    remove_key(successor, succ);
                } else {
                    merge_children(index, node, pred, succ);
                    remove_key(key, pred);
                }
            }
        } else {
            // Caso 3: A chave não está no nó atual
            Node* child = node->children[index];
            if (child->keys.size() < ORDER) {
                // Garantir que o filho tenha pelo menos a ordem mínima
                fill_child(index, node, child);
            }
            remove_key(key, child);
        }
    }

     int find_key_index(int key, Node* node) {
        int index = 0;
        while (index < node->keys.size() && key > node->keys[index])
            index++;
        return index;
    }

    int get_predecessor(int index, Node* node) {
        Node* current = node->children[index];
        while (!current->is_leaf)
            current = current->children[current->keys.size()];
        return current->keys[current->keys.size() - 1];
    }

    int get_successor(int index, Node* node) {
        Node* current = node->children[index + 1];
        while (!current->is_leaf)
            current = current->children[0];
        return current->keys[0];
    }

    void merge_children(int index, Node* parent, Node* left_child, Node* right_child) {
        left_child->keys.push_back(parent->keys[index]);

        for (int i = 0; i < right_child->keys.size(); i++)
            left_child->keys.push_back(right_child->keys[i]);

        if (!left_child->is_leaf) {
            for (int i = 0; i < right_child->children.size(); i++)
                left_child->children.push_back(right_child->children[i]);
        }

        parent->keys.erase(parent->keys.begin() + index);
        parent->children.erase(parent->children.begin() + index + 1);

        delete right_child;
    }

    void fill_child(int index, Node* parent, Node* child) {
    if (index > 0 && parent->children[index - 1]->keys.size() >= ORDER) {
        // Caso 2a: Roubar uma chave do filho esquerdo
        Node* left_sibling = parent->children[index - 1];
        child->keys.insert(child->keys.begin(), parent->keys[index - 1]);
        parent->keys[index - 1] = left_sibling->keys[left_sibling->keys.size() - 1];
        left_sibling->keys.pop_back();
        if (!left_sibling->is_leaf) {
            child->children.insert(child->children.begin(), left_sibling->children[left_sibling->children.size() - 1]);
            left_sibling->children.pop_back();
        }
    } else if (index < parent->children.size() - 1 && parent->children[index + 1]->keys.size() >= ORDER) {
        // Caso 2b: Roubar uma chave do filho direito
        Node* right_sibling = parent->children[index + 1];
        child->keys.push_back(parent->keys[index]);
        parent->keys[index] = right_sibling->keys[0];
        right_sibling->keys.erase(right_sibling->keys.begin());
        if (!right_sibling->is_leaf) {
            child->children.push_back(right_sibling->children[0]);
            right_sibling->children.erase(right_sibling->children.begin());
        }
    } else {
        // Caso 2c: Fusão com o filho esquerdo ou direito
        if (index > 0) {
            // Fusão com o filho esquerdo
            Node* left_sibling = parent->children[index - 1];
            left_sibling->keys.push_back(parent->keys[index - 1]);
            left_sibling->keys.insert(left_sibling->keys.end(), child->keys.begin(), child->keys.end());

            if (!child->is_leaf)
                left_sibling->children.insert(left_sibling->children.end(), child->children.begin(), child->children.end());

            parent->keys.erase(parent->keys.begin() + index - 1);
            parent->children.erase(parent->children.begin() + index);
            delete child;
        } else {
            // Fusão com o filho direito
            Node* right_sibling = parent->children[index + 1];
            child->keys.push_back(parent->keys[index]);
            child->keys.insert(child->keys.end(), right_sibling->keys.begin(), right_sibling->keys.end());

            if (!child->is_leaf)
                child->children.insert(child->children.end(), right_sibling->children.begin(), right_sibling->children.end());

            parent->keys.erase(parent->keys.begin() + index);
            parent->children.erase(parent->children.begin() + index + 1);
            delete right_sibling;
        }
    }
}
    bool isEmpty() const {
        return root == nullptr;
    }

    BTree::Node* getRoot() const {
        return root;
    }

    bool isBTree(const BTree& tree) {
        if (tree.isEmpty()) {
            return true;
        }
        return isBTreeNode(tree.getRoot());
    }

    bool isBTreeNode(const BTree::Node* node) {
        if (node->keys.size() > 2 * ORDER - 1) {
            return false;
        }

    if (!node->is_leaf) {
        if (node->children.size() != node->keys.size() + 1) {
            return false;
        }
            for (const auto& child : node->children) {
                if (!isBTreeNode(child)) {
                    return false;
                }
            }
        }

        return true;
    }

};



#endif /* B_TREE_H */
