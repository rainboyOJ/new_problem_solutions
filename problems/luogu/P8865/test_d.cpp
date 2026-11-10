#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n = 6, m = 6;
    vector<string> g = {
        "000000",
        "010000",
        "001001",
        "001110",
        "000000",
        "000010"
    };

    int D[8][8] = {0};
    for (int j = 1; j <= m; ++j) {
        for (int i = n - 1; i >= 1; --i) {
            if (g[i - 1][j - 1] == '1' || g[i][j - 1] == '1') {
                D[i][j] = 0;
            } else {
                D[i][j] = D[i + 1][j] + 1;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << "row " << i << " (0-indexed " << i-1 << ") D: ";
        for (int j = 1; j <= m; ++j) {
            cout << D[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
