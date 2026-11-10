#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    ifstream fin(argv[1]);
    ifstream fout(argv[2]);

    int n, m;
    if (!(fin >> n >> m)) {
        cerr << "Failed to read input\n";
        return 1;
    }

    vector<vector<int>> p(n + 2);
    for (int i = 1; i <= n; ++i) {
        p[i].resize(m);
        for (int j = 0; j < m; ++j) {
            fin >> p[i][j];
        }
    }

    int k;
    if (!(fout >> k)) {
        cerr << "Failed to read output op count\n";
        return 1;
    }

    if (k < 0 || k > 820000) {
        cerr << "Operation count out of range: " << k << "\n";
        return 1;
    }

    for (int step = 1; step <= k; ++step) {
        int u, v;
        if (!(fout >> u >> v)) {
            cerr << "Failed to read step " << step << "\n";
            return 1;
        }
        if (u < 1 || u > n + 1 || v < 1 || v > n + 1 || u == v) {
            cerr << "Invalid column index at step " << step << ": " << u << " -> " << v << "\n";
            return 1;
        }
        if (p[u].empty()) {
            cerr << "Column " << u << " is empty at step " << step << "\n";
            return 1;
        }
        if ((int)p[v].size() >= m) {
            cerr << "Column " << v << " is full at step " << step << "\n";
            return 1;
        }
        int ball = p[u].back();
        p[u].pop_back();
        p[v].push_back(ball);
    }

    // 检查最终状态
    int empty_cols = 0;
    for (int i = 1; i <= n + 1; ++i) {
        if (p[i].empty()) {
            empty_cols++;
            continue;
        }
        if ((int)p[i].size() != m) {
            cerr << "Column " << i << " has size " << p[i].size() << ", expected " << m << "\n";
            return 1;
        }
        int col = p[i][0];
        for (int b : p[i]) {
            if (b != col) {
                cerr << "Column " << i << " is not pure color!\n";
                return 1;
            }
        }
    }

    if (empty_cols != 1) {
        cerr << "Expected 1 empty column, got " << empty_cols << "\n";
        return 1;
    }

    cout << "VALIDATOR OK: Total steps = " << k << " <= 820000\n";
    return 0;
}
