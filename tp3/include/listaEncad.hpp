#ifndef LISTAENCAD_HPP
#define LISTAENCAD_HPP
#include <iostream>
#include <cstddef>

template <typename T>
class ListaEncad {
public:
    ListaEncad() : head(NULL), length(0) {}

    ~ListaEncad() {
        Node* current = head;
        while (current != NULL) {
            if (!current) break;  // Verifica se o nó atual é válido
            Node* next = current->next;  // Acesso ao próximo nó
            delete current;  // Libera o nó
            current = next;
        }
    }

    void adiciona(T* item) {
        Node* newNode = new Node();
        newNode->data = item;
        newNode->next = head;
        head = newNode;
        length++;
    }

    void adicionaFila(T* item) {
        Node* newNode = new Node();
        newNode->data = item;
        newNode->next = NULL;
        if (head == NULL) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
        length++;
    }

    void remove(T* item) {
        Node* current = head;
        Node* previous = NULL;
        while (current != NULL) {
            if (current->data == item) {
                if (previous == NULL) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                length--;
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    T* get(int index) {
        if (index < 0 || index >= length) {
            return NULL;  // Índice inválido
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    int tamanho() {
        return length;
    }

    T* retiraDaPosicao(int index) {
        if (index < 0 || index >= length) {
            return NULL;  // Índice inválido
        }
        Node* current = head;
        Node* previous = NULL;
        for (int i = 0; i < index; i++) {
            previous = current;
            current = current->next;
        }
        T* data = current->data;
        if (previous == NULL) {
            head = current->next;
        } else {
            previous->next = current->next;
        }
        delete current;
        length--;
        return data;
    }

    void adicionaNaPosicao(T* item, int index) {
        if (index < 0 || index > length) {
            return;  // Índice inválido
        }
        Node* newNode = new Node();
        newNode->data = item;
        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        length++;
    }

    void set(int index, T* item) {
        if (index < 0 || index >= length) {
            return;  // Índice inválido
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        current->data = item;
    }

private:
    struct Node {
        T* data;
        Node* next;
    };
    Node* head;
    int length;
};

#endif // LISTAENCAD_HPP