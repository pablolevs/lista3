#include "matchmaking.hpp"
#include <iostream>

Matchmaking::Matchmaking()
{
    size = 0;
}

Matchmaking::~Matchmaking() {}

bool Matchmaking::insert(Player player)
{
    if (size >= MAX_PLAYERS)
    {
        return false;
    }

    players[size] = player;

    size++;

    return true;
}

bool Matchmaking::removePlayer(int id)
{
    for (int i = 0; i < size; i++)
    {
        if (players[i].getId() == id)
        {
            for (int j = i; j < size - 1; j++)
            {
                players[j] = players[j + 1];
            }

            size--;

            return true;
        }
    }

    return false;
}

void Matchmaking::sortByScoreInsertion()
{
    for (int i = 1; i < size; i++)
    {
        Player key = players[i];
        int j = i - 1;
        while (j >= 0 && (players[j].getScore() > key.getScore() ||
                          (players[j].getScore() == key.getScore() &&
                           players[j].getTimestamp() > key.getTimestamp())))
        {
            players[j + 1] = players[j];
            j -= 1;
        }
        players[j + 1] = key;
    }
}

void Matchmaking::merge(int left, int mid, int right)
{
    int n = mid - left + 1;
    int m = right - mid;
    Player *leftTemp = new Player[n];
    Player *rightTemp = new Player[m];

    for (int i = 0; i < n; i++)
    {
        leftTemp[i] = players[left + i];
    }
    for (int j = 0; j < m; j++)
    {
        rightTemp[j] = players[mid + j + 1];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n && j < m)
    {
        if (leftTemp[i].getScore() < rightTemp[j].getScore())
        {
            players[k] = leftTemp[i];
            i++;
        }
        else if (leftTemp[i].getScore() > rightTemp[j].getScore())
        {
            players[k] = rightTemp[j];
            j++;
        }
        else
        {
            if (leftTemp[i].getTimestamp() <= rightTemp[j].getTimestamp())
            {
                players[k] = leftTemp[i];
                i++;
            }
            else
            {
                players[k] = rightTemp[j];
                j++;
            }
        }
        k++;
    }

    while (i < n)
    {
        players[k] = leftTemp[i];
        i++;
        k++;
    }

    while (j < m)
    {
        players[k] = rightTemp[j];
        j++;
        k++;
    }

    delete[] leftTemp;
    delete[] rightTemp;
}

void Matchmaking::mergeSort(int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

void Matchmaking::sortByScoreMerge()
{
    if (size > 0)
    {
        mergeSort(0, size - 1);
    }
}

Player *Matchmaking::formGroup(int groupSize, int delta, int *n)
{
    // verifica se existem jogadores suficientes
    if (size < groupSize)
    {
        *n = 0;
        return nullptr;
    }

    // procura o começo do grupo
    for (int i = 0; i + groupSize - 1 < size; i++)
    {
        // verifica se está no intervalo válido
        if (players[i + groupSize - 1].getScore() - players[i].getScore() <= delta)
        {
            // cria o array que vai ser retornado
            Player *group = new Player[groupSize];

            // insere os jogadores no grupo
            for (int j = 0; j < groupSize; j++)
            {
                group[j] = players[j + i];
            }

            // remove os jogadores do grupo
            for (int j = 0; j < groupSize; j++)
            {
                int id_remove = group[j].getId();
                removePlayer(id_remove);
            }

            // atualiza o n e retorna o grupo
            *n = groupSize;
            return group;
        }
    }

    // se não achou nenhum grupo válido
    *n = 0;
    return nullptr;
}

Player *Matchmaking::getWaitingPlayers(int *n)
{
    // caso não tenha jogadores em espera
    if (size == 0)
    {
        *n = 0;
        return nullptr;
    }

    // define o array a ser retornado
    Player *copy = new Player[size];

    // copia os jogadores
    for (int i = 0; i < size; i++)
    {
        copy[i] = players[i];
    }

    *n = size;
    return copy;
}

void Matchmaking::printWaitingPlayers()
{
    std::cout << "Waiting Players:" << std::endl;
    // verifica se existem jogadores
    if (size == 0)
    {
        std::cout << "(empty)" << std::endl;
        return;
    }

    // exibe os jogadores no formato desejado
    for (int i = 0; i < size; i++)
    {
        std::cout << '['
                  << players[i].getId() << " | "
                  << players[i].getName() << " | "
                  << players[i].getScore() << " | "
                  << players[i].getTimestamp() << ']'
                  << std::endl;
    }
}