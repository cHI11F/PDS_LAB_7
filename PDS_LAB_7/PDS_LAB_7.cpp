#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;


vector<vector<int>> readGraph(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> graph;

 
    if (!file.is_open()) {
        cerr << "Помилка: Не вдалося відкрити файл " << filename << endl;
        exit(EXIT_FAILURE); 
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<int> row;
        int value;
        while (ss >> value) {
            row.push_back(value);
        }
        
        if (!graph.empty() && row.size() != graph[0].size()) {
            cerr << "Помилка: Некоректний формат графу. Кількість елементів в рядках не співпадає." << endl;
            exit(EXIT_FAILURE);
        }
        graph.push_back(row);
    }

    file.close();
    return graph;
}


void calculateDegrees(const vector<vector<int>>& graph) {
    int vertices = graph.size();
    if (vertices == 0) {
        cerr << "Помилка: Граф порожній." << endl;
        return;
    }

    vector<int> inDegree(vertices, 0);
    vector<int> outDegree(vertices, 0);

    for (int i = 0; i < vertices; ++i) {
        if (graph[i].size() != vertices) {
            cerr << "Помилка: Некоректний розмір матриці суміжності." << endl;
            return;
        }

        for (int j = 0; j < vertices; ++j) {
            if (graph[i][j] != 0) {
                outDegree[i]++;
                inDegree[j]++;
            }
        }
    }

    cout << "Степені вершин графу (виходу/заходу):\n";
    for (int i = 0; i < vertices; ++i) {
        cout << "Вершина " << i + 1 << ": Вихідний степінь = " << outDegree[i]
            << ", Вхідний степінь = " << inDegree[i] << endl;
    }

  
    bool isHomogeneous = true;
    int degree = outDegree[0];
    for (int i = 1; i < vertices; ++i) {
        if (outDegree[i] != degree || inDegree[i] != degree) {
            isHomogeneous = false;
            break;
        }
    }

    if (isHomogeneous) {
        cout << "Граф є однорідним з степенем однорідності: " << degree << endl;
    }
    else {
        cout << "Граф не є однорідним." << endl;
    }
}


void findPendantAndIsolatedVertices(const vector<vector<int>>& graph) {
    int vertices = graph.size();
    if (vertices == 0) {
        cerr << "Помилка: Граф порожній." << endl;
        return;
    }

    vector<int> degree(vertices, 0);
    vector<int> pendantVertices;
    vector<int> isolatedVertices;

    for (int i = 0; i < vertices; ++i) {
        if (graph[i].size() != vertices) {
            cerr << "Помилка: Некоректний розмір матриці суміжності." << endl;
            return;
        }

        for (int j = 0; j < vertices; ++j) {
            if (graph[i][j] != 0) {
                degree[i]++;
            }
        }
        if (degree[i] == 1) {
            pendantVertices.push_back(i + 1);
        }
        else if (degree[i] == 0) {
            isolatedVertices.push_back(i + 1);
        }
    }

    cout << "Висячі вершини: ";
    if (pendantVertices.empty()) {
        cout << "Немає\n";
    }
    else {
        for (int vertex : pendantVertices) {
            cout << vertex << " ";
        }
        cout << endl;
    }

    cout << "Ізольовані вершини: ";
    if (isolatedVertices.empty()) {
        cout << "Немає\n";
    }
    else {
        for (int vertex : isolatedVertices) {
            cout << vertex << " ";
        }
        cout << endl;
    }
}

int main() {
    string filename;
    cout << "Введіть назву вхідного файлу з описом графу: ";
    cin >> filename;

    vector<vector<int>> graph = readGraph(filename);

    cout << "\nЗавдання 1: Визначення степенів вершин графу.\n";
    calculateDegrees(graph);

    cout << "\nЗавдання 2: Визначення висячих та ізольованих вершин графу.\n";
    findPendantAndIsolatedVertices(graph);

    return 0;
}
