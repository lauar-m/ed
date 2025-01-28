#ifndef SIMULADOREVENTOS_HPP
#define SIMULADOREVENTOS_HPP

#include <iostream>
#include <stdexcept>
#include <ctime>

// Estrutura para representar um evento
struct Evento {
    time_t dataHora;     // Data e hora do evento
    int tipoEvento;     // Tipo do evento (identifica o procedimento)
    int idPaciente;     // ID do paciente associado ao evento

    Evento();
    Evento(time_t _dataHora, int _tipoEvento, int _idPaciente);

    // Comparação para priorizar eventos pela data-hora (menor primeiro)
    bool operator<(const Evento& outro) const {
        return dataHora > outro.dataHora; // Invertido para MinHeap
    }
};

// Classe SimuladorEventos implementada com MinHeap
class SimuladorEventos {
private:
    Evento* heap;      // Array que representa o MinHeap
    int capacidade;    // Capacidade máxima do heap
    int tamanho;       // Tamanho atual do heap

    int pai(int i);
    int esquerdo(int i);
    int direito(int i);
    void minHeapify(int i);

public:
    SimuladorEventos(int capacidadeMax);  // Inicializa
    ~SimuladorEventos();                  // Finaliza

    void insereEvento(const Evento& evento); // InsereEvento
    Evento retiraProximoEvento();            // RetiraProximoEvento
    bool vazio() const;                      // Verifica se o heap está vazio
};

#endif
