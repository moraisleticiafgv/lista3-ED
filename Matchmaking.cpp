#include "Matchmaking.hpp"
#include <iostream>
 using namespace std;

Matchmaking::Matchmaking() : size(0) {}
Matchmaking::~Matchmaking() {}

bool Matchmaking::insert(Player player)
{
    if (size >= MAX_PLAYERS)
        return false;
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

void Matchmaking::sortByScoreInsertion() {
    for (int i = 1; i < size; i++) {
        Player key = players[i];
        int j = i - 1;
 
        // Move elementos maiores que key uma posição à frente
        while (j >= 0) {
            bool shouldMove = false;
 
            if (players[j].getScore() > key.getScore()) {
                shouldMove = true;
            } else if (players[j].getScore() == key.getScore() &&
                       players[j].getTimestamp() > key.getTimestamp()) {
                shouldMove = true;
            }
 
            if (!shouldMove) break;
 
            players[j + 1] = players[j];
            j--;
        }
        players[j + 1] = key;
    }
}

bool Matchmaking::comesBefore(const Player& a, const Player& b) {
    if (a.getScore() != b.getScore())
        return a.getScore() < b.getScore();
    return a.getTimestamp() < b.getTimestamp();
}

void Matchmaking::merge(int mid, int left, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;
 
    // Arrays auxiliares temporários
    Player* L = new Player[n1];
    Player* R = new Player[n2];
 
    for (int i = 0; i < n1; i++) L[i] = players[left + i];
    for (int j = 0; j < n2; j++) R[j] = players[mid + 1 + j];
 
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (comesBefore(L[i], R[j])) {
            players[k++] = L[i++];
        } else {
            players[k++] = R[j++];
        }
    }
    while (i < n1) players[k++] = L[i++];
    while (j < n2) players[k++] = R[j++];
 
    delete[] L;
    delete[] R;
}

void Matchmaking::mergeSort(int left, int right) {
    if (left >= right) return;          // caso base: subarray de 1 elemento
    int mid = left + (right - left) / 2;
    mergeSort(left, mid);
    mergeSort(mid + 1, right);
    merge(mid, left, right);
}
 
void Matchmaking::sortByScoreMerge() {
    if (size <= 1) return;
    mergeSort(0, size - 1);
}

Player* Matchmaking::formGroup(int groupSize, int delta, int* n) {
    if (groupSize <= 0 || size < groupSize) {
        *n = 0;
        return nullptr;
    }
 
    for (int i = 0; i <= size - groupSize; i++) {
        int minScore = players[i].getScore();
        int maxScore = players[i + groupSize - 1].getScore();
 
        if (maxScore - minScore <= delta) {
            // Grupo válido encontrado – copia os jogadores
            Player* group = new Player[groupSize];
            for (int k = 0; k < groupSize; k++) {
                group[k] = players[i + k];
            }
            *n = groupSize;
 
            // Remove os jogadores do grupo da fila deslocando à esquerda
            int removeEnd = i + groupSize;
            for (int j = i; j < size - groupSize; j++) {
                players[j] = players[removeEnd++];
            }
            size -= groupSize;
 
            return group;
        }
    }
 
    // Nenhum grupo válido encontrado
    *n = 0;
    return nullptr;
}

Player* Matchmaking::getWaitingPlayers(int* n) {
    if (size == 0) {
        *n = 0;
        std::cout << "Nenhum jogador aguardando\n";
        return nullptr;
    }
    Player* copy = new Player[size];
    for (int i = 0; i < size; i++) {
        copy[i] = players[i];
    }
    *n = size;
    return copy;
}

void Matchmaking::printWaitingPlayers() {
    std::cout << "Waiting Players:\n";
    if (size == 0) {
        std::cout << "(empty)\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        std::cout << "[" << players[i].getId()
                  << " | " << players[i].getName()
                  << " | " << players[i].getScore()
                  << " | " << players[i].getTimestamp()
                  << "]\n";
    }
}