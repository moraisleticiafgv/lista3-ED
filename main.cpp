#include <iostream>
#include "Matchmaking.hpp"
#include "Player.hpp"

using namespace std;

void testInsert() {
    cout << "\n=== TEST INSERT ===\n";

    Matchmaking mm;

    Player p1(1, "Ana", 1200, 10);
    Player p2(2, "Carlos", 1300, 20);
    Player p3(3, "Julia", 1100, 30);

    mm.insert(p1);
    mm.insert(p2);
    mm.insert(p3);

    mm.printWaitingPlayers();
}

void testRemove() {
    cout << "\n=== TEST REMOVE ===\n";

    Matchmaking mm;

    mm.insert(Player(1, "Ana", 1200, 10));
    mm.insert(Player(2, "Carlos", 1300, 20));
    mm.insert(Player(3, "Julia", 1100, 30));
    cout << "\nAntes da remoção:\n";
    mm.printWaitingPlayers();

    cout << "\nRemovendo Player 2...\n";
    bool removed = mm.removePlayer(2);

    cout << "Retorno de removePlayer(2): "
    << (removed ? "true" : "false") << endl;
    
    mm.printWaitingPlayers();
}

void testInsertionSort() {
    cout << "\n=== TEST INSERTION SORT ===\n";

    Matchmaking mm;

    mm.insert(Player(1, "Ana", 1500, 30));
    mm.insert(Player(2, "Carlos", 1200, 10));
    mm.insert(Player(3, "Julia", 1500, 20));
    mm.insert(Player(4, "Pedro", 1000, 5));

    cout << "\nAntes da ordenação:\n";
    mm.printWaitingPlayers();

    mm.sortByScoreInsertion();

    cout << "\nDepois da ordenação:\n";
    mm.printWaitingPlayers();
}

void testMergeSort() {
    cout << "\n=== TEST MERGE SORT ===\n";

    Matchmaking mm;

    mm.insert(Player(1, "Ana", 1500, 30));
    mm.insert(Player(2, "Carlos", 1200, 10));
    mm.insert(Player(3, "Julia", 1500, 20));
    mm.insert(Player(4, "Pedro", 1000, 5));

    cout << "\nAntes da ordenação\n";
    mm.printWaitingPlayers();

    mm.sortByScoreMerge();

    cout << "\nDepois da ordenação:\n";
    mm.printWaitingPlayers();
}

void testFormGroup() {
    cout << "\n=== TEST FORM GROUP ===\n";

    Matchmaking mm;

    mm.insert(Player(1, "Ana", 1000, 10));
    mm.insert(Player(2, "Carlos", 1010, 20));
    mm.insert(Player(3, "Julia", 1020, 30));
    mm.insert(Player(4, "Pedro", 1400, 40));

    mm.sortByScoreMerge();

    cout << "\nAntes de formar:\n";
    mm.printWaitingPlayers();

    int n = 0;

    Player* group = mm.formGroup(3, 30, &n);

    cout << "\nGrupo formado:\n";

    if (group != nullptr) {
        for (int i = 0; i < n; i++) {
            cout << group[i].getName()
                 << " - "
                 << group[i].getScore()
                 << endl;
        }

        delete[] group;
    } else {
        cout << "No valid group found.\n";
    }
    mm.printWaitingPlayers();
}

void testFormGroupFail(){
    cout << "\n=== TEST FORM GROUP FAIL ===\n";

    Matchmaking mm;

    mm.insert(Player(1, "Ana", 1000, 1));
    mm.insert(Player(2, "Carlos", 1100, 2));
    mm.insert(Player(3, "Julia", 1250, 3));

    mm.sortByScoreInsertion();

    cout << "\nAntes de tentar formar grupo:\n";
    mm.printWaitingPlayers();

    int n = 0;

    Player* group = mm.formGroup(3, 50, &n);

    if (group == nullptr && n == 0) {
        cout << "Nenhum grupo válido foi formado.\n";
    }

    cout << "\nDepois da tentativa:\n";
    mm.printWaitingPlayers();

    delete[] group;
}

void testGetWaitingPlayers() {
    cout << "\n=== TEST GET WAITING PLAYERS ===\n";

    Matchmaking mm;

    mm.insert(Player(1, "Ana", 1000, 10));
    mm.insert(Player(2, "Carlos", 1200, 20));

    int n = 0;

    Player* waiting = mm.getWaitingPlayers(&n);

    for (int i = 0; i < n; i++) {
        cout << waiting[i].getName()
             << " - "
             << waiting[i].getScore()
             << endl;
    }

    delete[] waiting;
}

void testGetWaitingPlayersEmpty() {
    cout << "\n=== TEST GET WAITING PLAYERS EMPTY===\n";

    Matchmaking mm;

    int n = 0;

    Player* waiting = mm.getWaitingPlayers(&n);

    for (int i = 0; i < n; i++) {
        cout << waiting[i].getName()
             << " - "
             << waiting[i].getScore()
             << endl;
    }

    delete[] waiting;
}

int main() {

    testInsert();

    testRemove();

    testInsertionSort();

    testMergeSort();

    testFormGroup();

    testFormGroupFail();

    testGetWaitingPlayers();

    testGetWaitingPlayersEmpty();

    return 0;
}