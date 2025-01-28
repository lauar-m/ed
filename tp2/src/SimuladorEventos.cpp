#include "SimuladorEventos.hpp"

// Construtores da estrutura Evento
Evento::Evento() : dataHora(0), tipoEvento(0), idPaciente(0) {}
Evento::Evento(time_t _dataHora, int _tipoEvento, int _idPaciente)
    : dataHora(_dataHora), tipoEvento(_tipoEvento), idPaciente(_idPaciente) {}

// Construtor do SimuladorEventos
SimuladorEventos::SimuladorEventos(int capacidadeMax) : capacidade(capacidadeMax), tamanho(0) {
    heap = new Evento[capacidade];
}

// Destrutor do SimuladorEventos
SimuladorEventos::~SimuladorEventos() {
    delete[] heap;
}

// Funções auxiliares para navegar no heap
int SimuladorEventos::pai(int i) {
    return (i - 1) / 2;
}

int SimuladorEventos::esquerdo(int i) {
    return 2 * i + 1;
}

int SimuladorEventos::direito(int i) {
    return 2 * i + 2;
}

// Função para manter a propriedade do MinHeap
void SimuladorEventos::minHeapify(int i) {
    int menor = i;
    int esq = esquerdo(i);
    int dir = direito(i);

    if (esq < tamanho && heap[esq].dataHora < heap[menor].dataHora) {
        menor = esq;
    }
    if (dir < tamanho && heap[dir].dataHora < heap[menor].dataHora) {
        menor = dir;
    }

    if (menor != i) {
        std::swap(heap[i], heap[menor]);
        minHeapify(menor);
    }
}

// Insere um evento no heap
void SimuladorEventos::insereEvento(const Evento& evento) {
    if (tamanho == capacidade) {
        throw std::overflow_error("SimuladorEventos cheio");
    }

    // Inserir no final e reorganizar
    int i = tamanho++;
    heap[i] = evento;

    while (i != 0 && heap[pai(i)].dataHora > heap[i].dataHora) {
        std::swap(heap[i], heap[pai(i)]);
        i = pai(i);
    }
}

// Retira e retorna o próximo evento (com menor data-hora)
Evento SimuladorEventos::retiraProximoEvento() {
    if (tamanho <= 0) {
        throw std::underflow_error("SimuladorEventos vazio");
    }

    Evento proximo = heap[0];
    heap[0] = heap[--tamanho];
    minHeapify(0);

    return proximo;
}

// Verifica se o heap está vazio
bool SimuladorEventos::vazio() const {
    return tamanho == 0;
}
