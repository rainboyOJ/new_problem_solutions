#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n = 6, m = 6, c = 1, f = 1;
    vector<string> g = {
        "000000",
        "010000",
        "001001",
        "001110",
        "000000",
        "000010"
    };

    int sum_c = 0, sum_f = 0;
    for (int y0 = 0; y0 < m; ++y0) {
        int col_c = 0, col_f = 0;
        for (int x1 = 0; x1 < n; ++x1) {
            for (int x2 = x1 + 2; x2 < n; ++x2) {
                bool col_ok = true;
                for (int r = x1; r <= x2; ++r) {
                    if (g[r][y0] == '1') { col_ok = false; break; }
                }
                if (!col_ok) continue;

                int len1 = 0;
                for (int c1 = y0 + 1; c1 < m; ++c1) {
                    if (g[x1][c1] == '0') len1++;
                    else break;
                }
                int len2 = 0;
                for (int c2 = y0 + 1; c2 < m; ++c2) {
                    if (g[x2][c2] == '0') len2++;
                    else break;
                }
                col_c += len1 * len2;
                for (int x3 = x2 + 1; x3 < n; ++x3) {
                    if (g[x3][y0] == '0') col_f += len1 * len2;
                    else break;
                }
            }
        }
        cout << "Col " << y0 << " : c=" << col_c << " f=" << col_f << endl;
        sum_c += col_c;
        sum_f += col_f;
    }
    cout << "Total: " << sum_c << " " << sum_f << endl;
    return 0;
}
