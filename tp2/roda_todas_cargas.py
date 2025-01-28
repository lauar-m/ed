import subprocess

# Função para executar o comando com o arquivo de entrada
def executar_comando(limite):
    nome_arquivo = f'cargas/input{limite}.csv'  # Define o nome do arquivo de entrada
    comando = ['./bin/tp2.out', nome_arquivo]  # Monta o comando
    try:
        # Executa o comando
        subprocess.run(comando, check=True)
        print(f'Comando executado com sucesso para {nome_arquivo}')
    except subprocess.CalledProcessError as e:
        print(f'Erro ao executar o comando para {nome_arquivo}: {e}')

# Para cada intervalo de 1000 até 100000
for limite in range(1000, 10001, 1000):
    print(f'Executando comando para input{limite}.csv...')
    executar_comando(limite)
