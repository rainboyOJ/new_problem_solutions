#include <iostream>
#include <vector>
#include <string>

using namespace std;

using ll = long long;

int main() {
    int n = 6, m = 6;
    vector<string> grid = {
        "",
        "000000",
        "010000",
        "001001",
        "001110",
        "000000",
        "000010"
    };

    int R[8][8] = {0}, D[8][8] = {0};
    for (int i = 1; i <= n; ++i) {
        for (int j = m - 1; j >= 1; --j) {
            if (grid[i][j - 1] == '1' || grid[i][j] == '1') R[i][j] = 0;
            else R[i][j] = R[i][j + 1] + 1;
        }
    }
    for (int j = 1; j <= m; ++j) {
        for (int i = n - 1; i >= 1; --i) {
            if (grid[i][j - 1] == '1' || grid[i + 1][j - 1] == '1') D[i][j] = 0;
            else D[i][j] = D[i + 1][j] + 1;
        }
    }

    ll total_C = 0, total_F = 0;
    for (int j = 1; j <= m; ++j) {
        ll sum_up = 0;
        for (int i = 1; i <= n; ++i) {
            if (grid[i][j - 1] == '1') {
                sum_up = 0;
            } else {
                if (i >= 3 && grid[i - 1][j - 1] == '0') {
                    sum_up = (sum_up + R[i - 2][j]);
                }
                int cur_r = R[i][j];
                int cur_d = D[i][j];
                if (cur_r > 0 && sum_up > 0) {
                    total_C += sum_up * cur_r;
                }
                if (cur_r > 0 && sum_up > 0 && cur_d > 0) {
                    total_F += sum_up * cur_r * cur_d;
                }
            }
        }
    }
    cout << "Total C: " << total_C << " F: " << total_F << endl;
    return 0;
}
