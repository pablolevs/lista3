import pandas as pd
import matplotlib.pyplot as plt

# lê o arquivo gerado pelo cpp
df = pd.read_csv('resultados_ordenacao.csv')

# Define o tamanho da figura
plt.figure(figsize=(10, 6))

# plota a linha do Insertion Sort
plt.plot(df['N'], df['InsertionSort'], marker='o',
         color='red', linewidth=2, label='Insertion Sort')

# plota a linha do Merge Sort
plt.plot(df['N'], df['MergeSort'], marker='s',
         color='blue', linewidth=2, label='Merge Sort')

# configurações do gráfico
plt.title('Comparação de Desempenho: Insertion Sort vs Merge Sort', fontsize=14)
plt.xlabel('Quantidade de Jogadores (N)', fontsize=12)
plt.ylabel('Tempo de Execução (milissegundos)', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(fontsize=12)
plt.xticks(df['N'])

# salva o gráfico em uma imagem .png
plt.savefig('grafico_desempenho.png', dpi=300, bbox_inches='tight')

# exibe o gráfico na tela
plt.show()
