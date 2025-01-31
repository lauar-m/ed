// #include "listaEncad.hpp"

// template <typename T>
// ListaEncad<T>::ListaEncad() : head(nullptr), length(0) {}

// template <typename T>
// ListaEncad<T>::~ListaEncad() {
//     Node* current = head;
//     while (current != nullptr) {
//         Node* next = current->next;
//         delete current->data;
//         delete current;
//         current = next;
//     }
// }

// template <typename T>
// void ListaEncad<T>::adiciona(T* item) {
//     Node* newNode = new Node();
//     newNode->data = item;
//     newNode->next = head;
//     head = newNode;
//     length++;
// }

// template <typename T>
// void ListaEncad<T>::remove(T* item) {
//     Node* current = head;
//     Node* previous = nullptr;
//     while (current != nullptr) {
//         if (current->data == item) {
//             if (previous == nullptr) {
//                 head = current->next;
//             } else {
//                 previous->next = current->next;
//             }
//             delete current->data;
//             delete current;
//             length--;
//             return;
//         }
//         previous = current;
//         current = current->next;
//     }
// }

// template <typename T>
// T* ListaEncad<T>::get(int index) {
//     Node* current = head;
//     for (int i = 0; i < index; i++) {
//         current = current->next;
//     }
//     return current->data;
// }

// template <typename T>
// int ListaEncad<T>::tamanho() {
//     return length;
// }

// template <typename T>
// T* ListaEncad<T>::retiraDaPosicao(int index) {
//     if (index < 0 || index >= length) {
//         return nullptr; // Índice inválido
//     }
//     Node* current = head;
//     Node* previous = nullptr;
//     for (int i = 0; i < index; i++) {
//         previous = current;
//         current = current->next;
//     }
//     T* data = current->data;
//     if (previous == nullptr) {
//         head = current->next;
//     } else {
//         previous->next = current->next;
//     }
//     delete current;
//     length--;
//     return data;
// }

// template <typename T>
// void ListaEncad<T>::adicionaNaPosicao(T* item, int index) {
//     if (index < 0 || index > length) {
//         return; // Índice inválido
//     }
//     Node* newNode = new Node();
//     newNode->data = item;
//     if (index == 0) {
//         newNode->next = head;
//         head = newNode;
//     } else {
//         Node* current = head;
//         for (int i = 0; i < index - 1; i++) {
//             current = current->next;
//         }
//         newNode->next = current->next;
//         current->next = newNode;
//     }
//     length++;
// }