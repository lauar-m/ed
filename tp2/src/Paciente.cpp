#include "Paciente.hpp"

Paciente::Paciente() : id(0), alta(0), dataAdmissao(0),
                       grauUrgencia(0), medidasHospitalares(0), testesLaboratorio(0),
                       examesImagem(0), instrumentosMedicamentos(0), estado(0),
                       dataSaida(0), horaEntradaFila(0), horaSaidaFila(0), tempoAtendimento(0), tempoEspera(0) {}

void Paciente::definirPaciente(int _id, int _alta, time_t _dataAdmissao,
                               int _grau, int _mh, int _tl, int _ei, int _im) {
    id = _id;
    alta = _alta;
    dataAdmissao = _dataAdmissao;
    grauUrgencia = _grau;
    medidasHospitalares = _mh;
    testesLaboratorio = _tl;
    examesImagem = _ei;
    instrumentosMedicamentos = _im;
    horaEntradaFila = 0;
    horaSaidaFila = 0;
    dataSaida = 0;
    estado = 0;
    tempoAtendimento = 0;
    tempoEspera = 0;
}


