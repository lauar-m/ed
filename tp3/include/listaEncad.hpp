#ifndef LISTAENCAD_HPP
#define LISTAENCAD_HPP

template <typename T>
class ListaEncad {
public:
    ListaEncad() : head(nullptr), length(0) {}

    ~ListaEncad() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current->data;
            delete current;
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

    void remove(T* item) {
        Node* current = head;
        Node* previous = nullptr;
        while (current != nullptr) {
            if (current->data == item) {
                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current->data;
                delete current;
                length--;
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    T* get(int index) {
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
            return nullptr; // Índice inválido
        }
        Node* current = head;
        Node* previous = nullptr;
        for (int i = 0; i < index; i++) {
            previous = current;
            current = current->next;
        }
        T* data = current->data;
        if (previous == nullptr) {
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
            return; // Índice inválido
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

private:
    struct Node {
        T* data;
        Node* next;
    };
    Node* head;
    int length;
};

#endif // LISTAENCAD_HPP