import pandas as pd
import matplotlib.pyplot as plt

# Carregar o CSV
df = pd.read_csv("tempos.csv")  # Substitua "dados.csv" pelo caminho do seu arquivo CSV

# Listar as funções únicas no arquivo
funcoes = df['funcao'].unique()

# Criar um gráfico para cada função
for funcao in funcoes:
    # Filtra os dados da função atual
    dados_funcao = df[df['funcao'] == funcao]

    # Plotar o gráfico
    plt.figure(figsize=(10, 6))
    plt.plot(dados_funcao['numPacientes'], dados_funcao['tempoExecucao(s)'], marker='o', label=funcao)

    # Adicionar título e rótulos
    plt.title(f"Tempo de Execução por Número de Pacientes - Função: {funcao}")
    plt.xlabel("Número de Pacientes")
    plt.ylabel("Tempo de Execução (s)")
    plt.grid(True)
    plt.legend()

    # Exibir o gráfico
    plt.savefig(f"{funcao}_tempo_execucao.png")
    plt.close()
