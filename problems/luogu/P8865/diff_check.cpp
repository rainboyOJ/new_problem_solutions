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

    // 检查 main.cpp 的逻辑
    int R[7][7] = {0}, D[7][7] = {0};
    for (int i = 1; i <= n; ++i) {
        for (int j = m - 1; j >= 1; --j) {
            if (g[i - 1][j - 1] == '1' || g[i - 1][j] == '1') R[i][j] = 0;
            else R[i][j] = R[i][j + 1] + 1;
        }
    }
    for (int j = 1; j <= m; ++j) {
        for (int i = n - 1; i >= 1; --i) {
            if (g[i - 1][j - 1] == '1' || g[i][j - 1] == '1') D[i][j] = 0;
            else D[i][j] = D[i + 1][j] + 1;
        }
    }

    for (int j = 1; j <= m; ++j) {
        int sum_up = 0;
        for (int i = 1; i <= n; ++i) {
            if (g[i - 1][j - 1] == '1') {
                sum_up = 0;
            } else {
                if (i >= 3 && g[i - 2][j - 1] == '0') {
                    sum_up += R[i - 2][j];
                }
                int cur_r = R[i][j];
                int cur_d = D[i][j];
                if (cur_r > 0 && sum_up > 0 && cur_d > 0) {
                    cout << "MAIN: j=" << j-1 << " i=" << i-1 << " sum_up=" << sum_up << " cur_r=" << cur_r << " cur_d=" << cur_d << " add=" << sum_up * cur_r * cur_d << endl;
                }
            }
        }
    }
    return 0;
}
