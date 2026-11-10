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

    // 检查暴力中每一种 F
    for (int y0 = 0; y0 < m; ++y0) {
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

                if (len1 > 0 && len2 > 0) {
                    int down_count = 0;
                    for (int x3 = x2 + 1; x3 < n; ++x3) {
                        if (g[x3][y0] == '0') down_count++;
                        else break;
                    }
                    if (down_count > 0) {
                        cout << "F: col=" << y0 << " x1=" << x1 << " x2=" << x2 << " len1=" << len1 << " len2=" << len2 << " down=" << down_count << endl;
                    }
                }
            }
        }
    }
    return 0;
}
