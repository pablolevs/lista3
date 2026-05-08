#include <iostream>
#include <chrono>
#include <fstream>
#include "player.hpp"
#include "matchmaking.hpp"

using namespace std;
using namespace chrono;

int main()
{
    static Matchmaking m;
    cout << "\n=== TESTE 1 (INSERCAO) ===\n";
    m.insert(Player(1, "Ana", 1000, 1));
    m.insert(Player(2, "Bruno", 900, 2));
    m.insert(Player(3, "Carlos", 1030, 3));
    m.insert(Player(4, "Diana", 950, 4));

    // estado de espera
    cout << "Insercao de jogadores:\n";
    m.printWaitingPlayers();

    cout << "\n=== TESTE 2 (REMOCAO) ===\n";
    // remoção correta
    m.removePlayer(3);

    // estado após a remoção
    cout << "Remocao correta:\n";
    m.printWaitingPlayers();

    // remoção incorreta
    m.removePlayer(5);

    // estado após remoção incorreta
    cout << "\nRemocao incorreta:\n";
    m.printWaitingPlayers();

    cout << "\n=== TESTE 3 (ORDENACAO POR INSERTION-SORT) ===\n";
    m.insert(Player(5, "Estefany", 2300, 5));

    // estado antes da ordenação
    cout << "Estado antes da ordenacao:\n";
    m.printWaitingPlayers();

    // ordenação por insertion sort
    m.sortByScoreInsertion();

    // estado após a ordenação
    cout << "\nEstado apos a ordenacao por insertion sort:\n";
    m.printWaitingPlayers();

    // limpeza da lista de espera e criação de outra para testar ordenação por merge sort
    m.removePlayer(1);
    m.removePlayer(2);
    m.removePlayer(4);
    m.removePlayer(5);

    m.insert(Player(1, "Angela", 1600, 1));
    m.insert(Player(2, "Bianca", 1200, 2));
    m.insert(Player(3, "Caio", 1300, 3));
    m.insert(Player(4, "Diego", 870, 4));
    m.insert(Player(5, "Estevao", 700, 5));

    cout << "\n=== TESTE 4 (ORDENACAO POR MERGE-SORT) ===\n";
    // estado antes da ordenação
    cout << "Estado antes da ordenacao:\n";
    m.printWaitingPlayers();

    // ordenação por merge sort
    m.sortByScoreMerge();

    // estado após a ordenação
    cout << "\nEstado apos a ordenacao por merge sort:\n";
    m.printWaitingPlayers();

    cout << "\n=== TESTE 5 (ORDENACAO COM EMPATE DE SCORE) ===\n";
    // inserindo jogadores com score iguais
    m.insert(Player(6, "Fernanda", 1200, 6));
    m.insert(Player(7, "Guilherme", 700, 7));
    m.insert(Player(8, "Henrique", 1200, 8));

    // estado antes de ordenar
    cout << "Estado antes da ordenacao:\n";
    m.printWaitingPlayers();

    // ordenação por merge sort (podia ser insertion também)
    m.sortByScoreMerge();

    // estado após a ordenação
    cout << "\nEstado apos a ordenacao com empate por score:\n";
    m.printWaitingPlayers();

    cout << "\n=== TESTE 6 (FORMACAO DE GRUPO COM SUCESSO) ===\n";
    // escolhi delta=100 e groupSize=3
    int n;
    Player *group = m.formGroup(3, 100, &n);
    // jogadores presentes no grupo
    if (group != nullptr)
    {
        cout << "Tamanho do grupo: " << n << endl;
        cout << "Group:\n";
        for (int i = 0; i < n; i++)
        {
            std::cout << '['
                      << group[i].getId() << " | "
                      << group[i].getName() << " | "
                      << group[i].getScore() << " | "
                      << group[i].getTimestamp() << ']'
                      << std::endl;
        }
        delete[] group;
    }

    // estado da lista após a formação do grupo
    cout << "\nEstado da lista de espera apos a formacao do grupo:\n";
    m.printWaitingPlayers();
    // Perceba que mesmo que o primeiro da fila seja o primeiro a ser analisado
    // os jogadores escolhidos foram aqueles nas posições 4, 5 e 6 (ou 3, 4 e 5 em index do python)
    // isso pois o primeiro, segundo e terceiro da lista não satisfizeram o delta

    cout << "\n=== TESTE 7 (FORMACAO DE GRUPO SEM SUCESSO) ===\n";
    // tentativa de formar grupo com size maior que o número de jogadores em espera
    Player *group1 = m.formGroup(6, 100, &n);

    // estado após a tentativa
    if (group1 == nullptr)
    {
        cout << "Grupo nao criado!\n";
        cout << "Tamanho da lista alocado: " << n << endl;
        cout << "Estado apos a tentativa:\n";
        m.printWaitingPlayers();
    }
    delete[] group1;

    // tentativa de formar grupo com delta insuficiente
    Player *group2 = m.formGroup(3, 50, &n);

    // estado após a tentativa
    if (group2 == nullptr)
    {
        cout << "\nGrupo nao criado!\n";
        cout << "Tamanho da lista alocado: " << n << endl;
        cout << "Estado apos a tentativa:\n";
        m.printWaitingPlayers();
    }
    delete[] group2;

    cout << "\n=== TESTE 8 (RECUPERACAO DOS DADOS) ===\n";
    int p;
    Player *copy = m.getWaitingPlayers(&p);
    if (copy != nullptr)
    {
        cout << "Tamanho da copia retornada: " << p << endl;
        cout << "Jogadores atuais (copia)\n";
        for (int i = 0; i < p; i++)
        {
            cout << '[' << copy[i].getId() << " | "
                 << copy[i].getName() << ']' << endl;
        }
    }

    cout << "\n=== TESTE 9 (TESTE DE PERFORMANCE ENTRE MERGE E INSERTION SORT) ===\n";

    // cria e abre o arquivo .csv para salvar os resultados
    ofstream arquivoCSV("resultados_ordenacao.csv");

    // escreve o cabeçalho das colunas
    arquivoCSV << "N,InsertionSort,MergeSort\n";

    // array com diferentes tamanhos de teste
    int test_sizes[] = {1000, 2500, 5000, 7500, 10000};
    int num_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);

    for (int t = 0; t < num_tests; t++)
    {
        int MAX = test_sizes[t];
        Player *base_player = new Player[MAX];

        // Gera jogadores aleatórios com scores entre 1 e 1500
        for (int i = 0; i < MAX; i++)
        {
            base_player[i] = Player(i, "Player " + to_string(i), rand() % 1500 + 1, i);
        }

        // --- TESTE INSERTION SORT ---
        static Matchmaking m2;
        for (int i = 0; i < MAX; i++)
        {
            m2.insert(base_player[i]);
        }

        // analise de tempo
        auto start1 = steady_clock::now();
        m2.sortByScoreInsertion();
        auto end1 = steady_clock::now();
        auto insertionDuration = duration_cast<milliseconds>(end1 - start1).count();

        // --- TESTE MERGE SORT ---
        static Matchmaking m3;
        for (int i = 0; i < MAX; i++)
        {
            m3.insert(base_player[i]);
        }

        // analise de tempo
        auto start2 = steady_clock::now();
        m3.sortByScoreMerge();
        auto end2 = steady_clock::now();
        auto mergeDuration = duration_cast<milliseconds>(end2 - start2).count();

        delete[] base_player;

        // salva os resultados no .csv
        arquivoCSV << MAX << ',' << insertionDuration << ',' << mergeDuration << endl;

        // Imprime o resultado para os valores testados
        cout << "\nResultados para N = " << MAX << " jogadores:\n";
        cout << "Duracao de Insertion Sort: " << insertionDuration << " milisegundos\n";
        cout << "Duracao de Merge Sort: " << mergeDuration << " milisegundos\n";

        if (insertionDuration < mergeDuration)
        {
            cout << "Insertion Sort foi " << (mergeDuration - insertionDuration)
                 << " milisegundos mais rapido.\n";
        }
        else if (mergeDuration < insertionDuration)
        {
            cout << "Merge Sort foi " << (insertionDuration - mergeDuration)
                 << " milisegundos mais rapido.\n";
        }
        else
        {
            cout << "Tempos iguais.\n";
        }
    }
    // fecha o arquivo
    arquivoCSV.close();

    return 0;
}
