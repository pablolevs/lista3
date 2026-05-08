# Sistema de Matchmaking para Jogos Online

## Descrição do Projeto
Este projeto implementa um sistema de *matchmaking* em C++ para simular a fila de espera de um jogo online competitivo. 
O sistema gerencia jogadores (com identificador, nome, score e ordem de chegada) e forma grupos de jogadores com níveis de 
habilidade semelhantes, definidos por uma diferença máxima de pontuação (`delta`). Para otimizar e possibilitar a busca por 
grupos justos, o sistema conta com a implementação manual e comparação de dois algoritmos de ordenação: **Insertion Sort** 
e **Merge Sort**.

## Instruções de Compilação
Para compilar o código fonte, certifique-se de que todos os arquivos `.cpp` e `.hpp` estão no mesmo diretório e utilize o 
compilador `g++` através do terminal:

```bash
g++ main.cpp matchmaking.cpp player.cpp -o matchmaking
```

## Instruções de execução
Após compilar com sucesso, execute o arquivo `exe` gerado.

```bash
.\matchmaking.exe
```

## Organização dos Arquivos
O projeto foi modularizado para separar a lógica de negócio das estruturas de dados e execução:
- `player.hpp` / `player.cpp`: Declaração e implementação da classe `Player`, representando o jogador e seus atributos básicos.
- `matchmaking.hpp` / `matchmaking.cpp`: Declaração e implementação da classe `Matchmaking`. Contém o array estático de
  jogadores, os algoritmos de ordenação (Merge e Insertion) e a lógica de formação de grupos válidos.
- `main.cpp`: Ponto de entrada do programa. Contém todos os cenários de testes exigidos, além de um teste de
  performance para avaliação assintótica dos algoritmos.
- `plot.py`: Script em Python criado como auxiliar extra para ler o arquivo `.csv` gerado no Teste 9
 e renderizar um gráfico de comparação de desempenho entre os algoritmos.

## Como executar os testes do `main.cpp`
O arquivo `main.cpp` foi projetado para executar uma bateria de testes de forma sequencial. Ao iniciar o programa 
(seguindo as instruções de execução acima), os 9 testes rodarão automaticamente e os resultados serão impressos no terminal.

O fluxo de testes cobre:
- Testes 1 a 2: Inserção e remoção de jogadores específicos pelo ID.
- Testes 3 a 5: Ordenação usando *Insertion Sort* e *Merge Sort*, demonstrando os critérios de desempate (menor timestamp).
- Testes 6 a 7: Formação de grupos válidos respeitando o delta e comportamento esperado ao não encontrar grupos possíveis.
- Teste 8: Verificação da cópia de memória (`getWaitingPlayers`).
- Teste 9: Gera resultados de dados aleatórios de 1.000 a 10.000 jogadores para visualizar a diferença entre os métodos de ordenação
  (*Insertion* e *Merge*) e exporta para arquivo .csv.

  ## Autores
  - Raul Medici Martinelli
  - Pablo levy Fernades Alcântara
