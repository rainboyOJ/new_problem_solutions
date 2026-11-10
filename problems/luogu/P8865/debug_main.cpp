#include <iostream>
#include <vector>
#include <string>

using namespace std;

using ll = long long;

int main() {
    int n, m, c, f;
    int t, id;
    cin >> t >> id;
    cin >> n >> m >> c >> f;
    vector<string> grid(n + 1);
    for (int i = 1; i <= n; ++i) cin >> grid[i];

    int R[105][105] = {0}, D[105][105] = {0};
    for (int i = 1; i <= n; ++i) {
        for (int j = m - 1; j >= 1; --j) {
            if (grid[i][j - 1] == '1' || grid[i][j] == '1') R[i][j] = 0;
            else R[i][j] = R[i][j + 1] + 1;
        }
    }
    for (int j = 1; j <= m; ++j) {
        for (int i = n - 1; i >= 1; --i) {
            if (grid[i - 1][j - 1] == '1' || grid[i][j - 1] == '1') D[i][j] = 0;
            else D[i][j] = D[i + 1][j] + 1;
        }
    }

    ll total_C = 0, total_F = 0;
    for (int j = 1; j <= m; ++j) {
        ll sum_up = 0;
        ll col_c = 0, col_f = 0;
        for (int i = 1; i <= n; ++i) {
            if (grid[i][j - 1] == '1') {
                sum_up = 0;
            } else {
                if (i >= 3 && grid[i - 1][j - 1] == '0') {
                    sum_up += R[i - 2][j];
                }
                int cur_r = R[i][j];
                int cur_d = D[i][j];
                if (cur_r > 0 && sum_up > 0) {
                    col_c += sum_up * cur_r;
                }
                if (cur_r > 0 && sum_up > 0 && cur_d > 0) {
                    col_f += sum_up * cur_r * cur_d;
                }
            }
        }
        cout << "MAIN Col " << j-1 << " : c=" << col_c << " f=" << col_f << endl;
        total_C += col_c;
        total_F += col_f;
    }
    cout << "Total: " << total_C << " " << total_F << endl;
    return 0;
}
