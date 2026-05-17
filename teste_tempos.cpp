#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

#include "Matchmaking.hpp"
#include "Player.hpp"

using namespace std;
using namespace std::chrono;

const int REPETICOES = 3;

// Gera scores pseudoaleatorios de forma deterministica.
// Assim, toda execucao usa os mesmos dados.
int gerarScore(int i) {
    long long x = 1103515245LL * (i + 12345) + 12345;
    if (x < 0) {
        x = -x;
    }

    return 500 + static_cast<int>(x % 3000);
}

// Preenche dois sistemas com exatamente os mesmos jogadores.
void preencherSistemas(Matchmaking& mmInsertion, Matchmaking& mmMerge, int n) {
    for (int i = 0; i < n; i++) {
        int id = i + 1;
        string nome = "Player_" + to_string(id);
        int score = gerarScore(i);

        // O timestamp representa a ordem de chegada.
        int timestamp = i + 1;

        Player jogador(id, nome, score, timestamp);

        mmInsertion.insert(jogador);
        mmMerge.insert(jogador);
    }
}

// Mede somente o tempo da ordenacao por Insertion Sort.
double medirInsertionSort(int n) {
    double somaTempos = 0.0;

    for (int r = 0; r < REPETICOES; r++) {
        Matchmaking* mmInsertion = new Matchmaking();
        Matchmaking* mmMerge = new Matchmaking();

        preencherSistemas(*mmInsertion, *mmMerge, n);

        auto inicio = high_resolution_clock::now();
        mmInsertion->sortByScoreInsertion();
        auto fim = high_resolution_clock::now();

        duration<double, milli> tempo = fim - inicio;
        somaTempos += tempo.count();

        delete mmInsertion;
        delete mmMerge;
    }

    return somaTempos / REPETICOES;
}

// Mede somente o tempo da ordenacao por Merge Sort.
double medirMergeSort(int n) {
    double somaTempos = 0.0;

    for (int r = 0; r < REPETICOES; r++) {
        Matchmaking* mmInsertion = new Matchmaking();
        Matchmaking* mmMerge = new Matchmaking();

        preencherSistemas(*mmInsertion, *mmMerge, n);

        auto inicio = high_resolution_clock::now();
        mmMerge->sortByScoreMerge();
        auto fim = high_resolution_clock::now();

        duration<double, milli> tempo = fim - inicio;
        somaTempos += tempo.count();

        delete mmInsertion;
        delete mmMerge;
    }

    return somaTempos / REPETICOES;
}

int main() {
    const int tamanhos[] = {100, 500, 1000, 3000, 5000, 10000};
    const int qtdTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    cout << fixed << setprecision(4);

    cout << "Comparacao de tempo entre Insertion Sort e Merge Sort\n";
    cout << "Cada valor representa a media de " << REPETICOES << " execucoes.\n";
    cout << "Tempos em milissegundos.\n\n";

    cout << left
         << setw(15) << "n"
         << setw(25) << "Insertion Sort"
         << setw(25) << "Merge Sort"
         << '\n';

    cout << string(65, '-') << '\n';

    for (int i = 0; i < qtdTamanhos; i++) {
        int n = tamanhos[i];

        double tempoInsertion = medirInsertionSort(n);
        double tempoMerge = medirMergeSort(n);

        cout << left
             << setw(15) << n
             << setw(25) << tempoInsertion
             << setw(25) << tempoMerge
             << '\n';
    }

    return 0;
}
