#include "arvoreB.hpp"

// Construtor
ArvoreB::ArvoreB(int t) {
    this->t = t;
    root = nullptr;
}

// Inserção
void ArvoreB::insert(Voo* voo, const std::string& key) {
    if (root == nullptr) {
        root = new noArvoreB(t, true);
        root->keys[0] = key;
        root->voos[0]->adiciona(voo);
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            noArvoreB* s = new noArvoreB(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < key) {
                i++;
            }
            s->C[i]->insertNonFull(voo, key);
            root = s;
        } else {
            root->insertNonFull(voo, key);
        }
    }
}

// Busca
ListaEncad<Voo>* ArvoreB::search(const std::string& key) {
    return (root == nullptr) ? nullptr : root->search(key);
}