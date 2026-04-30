//Dynamic Programming Based Network Routing with Path Reconstruction using Floyd–Warshall Algorithm

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

const int INF = 1e9;

void printPath(int source, int destination, vector<vector<int>>& nextNode, vector<string>& names) {
    if (nextNode[source][destination] == -1) {
        cout << "No path available";
        return;
    }

    int current = source;
    cout << names[current];

    while (current != destination) {
        current = nextNode[current][destination];
        cout << " -> " << names[current];
    }
}

int main() {
    int n = 6;

    vector<string> names = {
        "SRM AP", "Vijayawada", "Hyderabad",
        "Bengaluru", "Chennai", "Delhi"
    };

    vector<vector<int>> dist = {
        {0, 20, 50, 120, 90, INF},      // SRM AP
        {20, 0, 25, INF, INF, 200},     // Vijayawada
        {50, 25, 0, 40, 30, 150},       // Hyderabad
        {120, INF, 40, 0, 70, 110},     // Bengaluru
        {90, INF, 30, 70, 0, INF},      // Chennai
        {INF, 200, 150, 110, INF, 0}    // Delhi
    };

    vector<vector<int>> nextNode(n, vector<int>(n, -1));

    // Initialize path matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] != INF && i != j) {
                nextNode[i][j] = j;
            }
        }
    }

    // Floyd-Warshall Algorithm using Dynamic Programming
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {

                    dist[i][j] = dist[i][k] + dist[k][j];
                    nextNode[i][j] = nextNode[i][k];
                }
            }
        }
    }

    cout << "Servers:\n";
    for (int i = 0; i < n; i++) {
        cout << i << " - " << names[i] << endl;
    }

    int source, destination;

    cout << "\nEnter source server number: ";
    cin >> source;

    cout << "Enter destination server number: ";
    cin >> destination;

    if (source < 0 || source >= n || destination < 0 || destination >= n) {
        cout << "Invalid server number.\n";
        return 0;
    }

    cout << "\nShortest Route:\n";
    printPath(source, destination, nextNode, names);

    cout << "\nMinimum Latency: ";
    if (dist[source][destination] == INF) {
        cout << "No connection available\n";
    } else {
        cout << dist[source][destination] << " ms\n";
    }

    cout << "\nShortest Latency Matrix (ms):\n\n";

    cout << left << setw(15) << "From/To";
    for (int j = 0; j < n; j++) {
        cout << setw(15) << names[j];
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << left << setw(15) << names[i];

        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                cout << setw(15) << "INF";
            else
                cout << setw(15) << dist[i][j];
        }
        cout << endl;
    }

    return 0;
}