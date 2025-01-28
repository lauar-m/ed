#include "Fila.hpp"
#include "Procedimento.hpp"
#include "Paciente.hpp"
#include "SimuladorEventos.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <string>
#include <memory>
#include <stdexcept>
using namespace std::chrono;
using namespace std;

void cronometrarESalvar(const string& nomeArquivo, const string& nomeFuncao, double duracao, int numPacientes) {
    std::ofstream arquivo(nomeArquivo, std::ios_base::app);
    if (arquivo.is_open()) {
        arquivo << numPacientes << "," << nomeFuncao << "," << duracao << "\n";
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo de resultados. \n";
    }
}



void carregarDadosCSV(const std::string& nomeArquivo, float tempos[], int capacidades[], Paciente*& pacientes, int& numPacientes) {
    std::ifstream arquivo(nomeArquivo);
    std::string linha;
    
    if (arquivo.is_open()) {
        // Ler as primeiras 6 linhas (tempo médio e capacidades)
        for (int i = 0; i < 6; ++i) {
            std::getline(arquivo, linha);
            std::stringstream ss(linha);
            std::string valor;

            // Primeiro valor: tempo médio de atendimento
            std::getline(ss, valor, ' ');
            tempos[i] = std::stof(valor);

            // Segundo valor: capacidade (número de unidades disponíveis)
            std::getline(ss, valor, ' ');
            capacidades[i] = std::stoi(valor);
        }

        // Ler o número de pacientes
        std::getline(arquivo, linha);
        try {
            numPacientes = std::stoi(linha);
        } catch (...) {
            std::cerr << "Erro ao ler número de pacientes." << std::endl;
            arquivo.close();
            return;
        }

        // Alocar array de pacientes
        pacientes = new Paciente[numPacientes];

        // Ler os dados de cada paciente
        for (int j = 0; j < numPacientes; ++j) {
            std::getline(arquivo, linha);
            std::stringstream ss(linha);
            std::string valor;
            int dados[11];
            int i = 0;

            while (std::getline(ss, valor, ' ') && i < 11) {
                dados[i++] = std::stoi(valor);
            }

            if (i == 11) {
                struct tm dataHora = {};
                dataHora.tm_year = dados[2] - 1900;
                dataHora.tm_mon = dados[3] - 1;
                dataHora.tm_mday = dados[4];
                dataHora.tm_hour = dados[5];
                time_t dataAdmissao = mktime(&dataHora);
                pacientes[j].definirPaciente(dados[0], dados[1], dataAdmissao, dados[6], dados[7], dados[8], dados[9], dados[10]);
                pacientes[j].estado = 1;  // Paciente inicialmente chegou
            }
        }
        arquivo.close();
    }
}

// Função para gerir o tempo eax
std::string formatarTempo(time_t tempo) {
    char buffer[80];
    struct tm* timeinfo = localtime(&tempo);
    strftime(buffer, 80, "%a %b %d %H:%M:%S %Y", timeinfo);
    return std::string(buffer);
}
int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    std::string nomeArquivo = argv[1];
    auto start = high_resolution_clock::now();

    // Variáveis para armazenar tempos e capacidades de cada procedimento
    float tempos[6];
    int capacidades[6];

    // Variável para armazenar os pacientes
    Paciente* pacientes = nullptr;
    int numPacientes = 0;
    
    // auto start = high_resolution_clock::now();
    // Carregar dados do arquivo CSV
    carregarDadosCSV(nomeArquivo, tempos, capacidades, pacientes, numPacientes);
    // auto stop = high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count();
    // cronometrarESalvar("tempos.csv", "Procedimento", duration, numPacientes);



    if (!pacientes) {
        std::cerr << "Erro ao carregar pacientes!" << std::endl;
        return 1;
    }

    //  start = high_resolution_clock::now();
    // Iniciar procedimentos com os tempos e capacidades lidos do CSV
    Procedimento triagem("Triagem", tempos[0], capacidades[0]);
    Procedimento atendimento("Atendimento", tempos[1], capacidades[1]);
    Procedimento medidasHospitalares("Medidas Hospitalares", tempos[2], capacidades[2]);
    Procedimento testesLaboratorio("Testes de Laboratório", tempos[3], capacidades[3]);
    Procedimento examesImagem("Exames de Imagem", tempos[4], capacidades[4]);
    Procedimento instrumentosMedicamentos("Instrumentos/Medicamentos", tempos[5], capacidades[5]);
    //  stop = high_resolution_clock::now();
    //  duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count();
    // cronometrarESalvar("tempos.csv", "Procedimentos", duration, numPacientes);

    // auto start = high_resolution_clock::now();
    // Iniciar filas
    Fila filaTriagem;
    Fila filaAtendimento;
    Fila filaMedidasHospitalares;
    Fila filaTestesLaboratorio;
    Fila filaExamesImagem;
    Fila filaInstrumentosMedicamentos;
    // auto stop = high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count();
    // cronometrarESalvar("tempos.csv", "Filas", duration, numPacientes);


    // Iniciar simulador de eventos
    SimuladorEventos simulador(10000);  // Aumentar a capacidade inicial para 10000 eventos

    // Sort pacientes por ordem de chegada
    for (int i = 0; i < numPacientes; ++i) {
        for (int j = i + 1; j < numPacientes; ++j) {
            if (pacientes[i].dataAdmissao > pacientes[j].dataAdmissao) {
                std::swap(pacientes[i], pacientes[j]);
            }
        }
    }

    // Adicionar pacientes ao simulador de eventos (evento de chegada à triagem)
    for (int i = 0; i < numPacientes; ++i) {
        simulador.insereEvento(Evento(pacientes[i].dataAdmissao, 0, pacientes[i].id));  // 0 indica evento de triagem
        //std::cout << "Paciente " << pacientes[i].id << " chegou no hospital" << std::endl;
    }

    // start = high_resolution_clock::now();
    // Simulação de atendimento
    while (!simulador.vazio()) {
        Evento proximoEvento = simulador.retiraProximoEvento();
        int pacienteID = proximoEvento.idPaciente;
        if (pacienteID < 0 || pacienteID >= numPacientes) {
            std::cerr << "Erro: ID de paciente fora do intervalo válido." << std::endl;
            continue;
        }
        Paciente& paciente = pacientes[pacienteID];

        switch (proximoEvento.tipoEvento) {
            case 0:  // Triagem
                
                if (triagem.temUnidadeLivre()) {
                    triagem.ocuparUnidade();
                    //std::cout << "Paciente " << pacienteID << " entrou na triagem." << std::endl;

                    // Inserir evento de saída da triagem e entrada no atendimento
                    simulador.insereEvento(Evento(proximoEvento.dataHora + (time_t)(triagem.getTempo() * 3600), 1, pacienteID));
                } else {
                    // Reenfileirar o evento até que uma unidade esteja livre
                    simulador.insereEvento(Evento(proximoEvento.dataHora + 3600, 0, pacienteID));  // Tenta novamente em 1h
                }
                break;

            case 1:  // Atendimento
                triagem.liberarUnidade();  // Liberar unidade da triagem
                if (atendimento.temUnidadeLivre()) {
                    atendimento.ocuparUnidade();
                    //std::cout << "Paciente " << pacienteID << " entrou no atendimento." << std::endl;

                    // Próximo evento será a alta ou o próximo procedimento
                if (paciente.alta == 1) {
                    paciente.dataSaida = proximoEvento.dataHora + (time_t)(atendimento.getTempo() * 3600);
                    //std::cout << "Paciente " << pacienteID << " recebeu alta." << std::endl;
                } else if (paciente.medidasHospitalares) {
                    simulador.insereEvento(Evento(proximoEvento.dataHora + (time_t)(atendimento.getTempo() * 3600), 2, pacienteID));
                } else if (paciente.testesLaboratorio) {
                    simulador.insereEvento(Evento(proximoEvento.dataHora + (time_t)(atendimento.getTempo() * 3600), 3, pacienteID));
                } else if (paciente.examesImagem) {
                    simulador.insereEvento(Evento(proximoEvento.dataHora + (time_t)(atendimento.getTempo() * 3600), 4, pacienteID));
                } else if (paciente.instrumentosMedicamentos) {
                    simulador.insereEvento(Evento(proximoEvento.dataHora + (time_t)(atendimento.getTempo() * 3600), 5, pacienteID));
                } else {
                    // Reenfileirar o evento até que uma unidade esteja livre
                    simulador.insereEvento(Evento(proximoEvento.dataHora + 3600, 1, pacienteID));
                }
                break;

            case 2:  // Medidas Hospitalares
                atendimento.liberarUnidade();
                if (medidasHospitalares.temUnidadeLivre()) {
                    medidasHospitalares.ocuparUnidade();
                    //std::cout << "Paciente " << pacienteID << " está realizando medidas hospitalares." << std::endl;

                    // Retornar ao atendimento após o procedimento
                    simulador.insereEvento(Evento(proximoEvento.dataHora + (time_t)(medidasHospitalares.getTempo() * 3600), 1, pacienteID));
                } else {
                    // Reenfileirar o evento até que uma unidade esteja livre
                    simulador.insereEvento(Evento(proximoEvento.dataHora + 3600, 2, pacienteID));
                }
                break;

            case 3:  // Testes de Laboratório
                atendimento.liberarUnidade();
                if (testesLaboratorio.temUnidadeLivre()) {
                    testesLaboratorio.ocuparUnidade();
                    //std::cout << "Paciente " << pacienteID << " está realizando testes de laboratório." << std::endl;

                    // Retornar ao atendimento após o procedimento
                    simulador.insereEvento(Evento(proximoEvento.dataHora + (time_t)(testesLaboratorio.getTempo() * 3600), 1, pacienteID));
                } else {
                    simulador.insereEvento(Evento(proximoEvento.dataHora + 3600, 3, pacienteID));
                }
                break;

            case 4:  // Exames de Imagem
                atendimento.liberarUnidade();
                if (examesImagem.temUnidadeLivre()) {
                    examesImagem.ocuparUnidade();
                    //std::cout << "Paciente " << pacienteID << " está realizando exames de imagem." << std::endl;

                    // Retornar ao atendimento após o procedimento
                    simulador.insereEvento(Evento(proximoEvento.dataHora + (time_t)(examesImagem.getTempo() * 3600), 1, pacienteID));
                } else {
                    simulador.insereEvento(Evento(proximoEvento.dataHora + 3600, 4, pacienteID));
                }
                break;

            case 5:  // Instrumentos/Medicamentos
                atendimento.liberarUnidade();
                if (instrumentosMedicamentos.temUnidadeLivre()) {
                    instrumentosMedicamentos.ocuparUnidade();
                    //std::cout << "Paciente " << pacienteID << " está utilizando instrumentos/medicamentos." << std::endl;

                    // Retornar ao atendimento após o procedimento
                    simulador.insereEvento(Evento(proximoEvento.dataHora + (time_t)(instrumentosMedicamentos.getTempo() * 3600), 1, pacienteID));
                } else {
                    simulador.insereEvento(Evento(proximoEvento.dataHora + 3600, 5, pacienteID));
                }
                break;
        }
    }
    // stop = high_resolution_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count();
    // cronometrarESalvar("tempos.csv", "SimuladorEventos", duration, numPacientes);

    // Exibir a data e hora de entrada e alta de todos os pacientes
    //std::cout << "\nResumo das altas dos pacientes:\n";
    
    }
    for (int i = 0; i < numPacientes; ++i) {
        if (pacientes[i].alta) {
            std::cout << pacientes[i].id << " "
                      << formatarTempo(pacientes[i].dataAdmissao) << " "
                      << formatarTempo(pacientes[i].dataSaida) << std::endl;
                      //                       << segundoToHora(pacientes[i].tempoEspera + pacientes[i].tempoAtendimento) << " "
//                       << segundoToHora(pacientes[i].tempoAtendimento) << " "
//                       << segundoToHora(pacientes[i].tempoEspera) << " "
//                       << std::endl;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count();
    cronometrarESalvar("tempos.csv", "Main", duration , numPacientes);
    
    // Limpeza
    delete[] pacientes;
    return 0;
}
