#include "noArvoreB.hpp"
#include <iostream>

noArvoreB::noArvoreB(int t, bool leaf) {
    this->t = t;
    this->leaf = leaf;
    this->n = 0;
    this->keys = new std::string[2 * t - 1];
    this->voos = new ListaEncad<Voo>*[2 * t - 1];
    this->C = new noArvoreB*[2 * t];
    for (int i = 0; i < 2 * t - 1; i++) {
        voos[i] = new ListaEncad<Voo>();
    }
}

ListaEncad<Voo>* noArvoreB::search(const std::string& key) {
    int i = 0;
    while (i < n && key > keys[i]) {
        i++;
    }
    if (i < n && keys[i] == key) {
        return voos[i];
    }
    if (leaf) {
        return NULL;
    }
    return C[i]->search(key);
}

void noArvoreB::insertNonFull(Voo* voo, const std::string& key) {
    int i = n - 1;
    if (leaf) {
        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            voos[i + 1] = voos[i];
            i--;
        }
        keys[i + 1] = key;
        if (voos[i + 1] == NULL) {
            voos[i + 1] = new ListaEncad<Voo>();
        }
        voos[i + 1]->adiciona(voo);
        n++;
    } else {
        while (i >= 0 && keys[i] > key) {
            i--;
        }
        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1] < key) {
                i++;
            }
        }
        C[i + 1]->insertNonFull(voo, key);
    }
}

void noArvoreB::splitChild(int i, noArvoreB* y) {
    noArvoreB* z = new noArvoreB(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
        z->voos[j] = y->voos[j + t];
    }

    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->C[j] = y->C[j + t];
        }
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--) {
        C[j + 1] = C[j];
    }
    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--) {
        keys[j + 1] = keys[j];
        voos[j + 1] = voos[j];
    }
    keys[i] = y->keys[t - 1];
    voos[i] = y->voos[t - 1];
    n++;
}