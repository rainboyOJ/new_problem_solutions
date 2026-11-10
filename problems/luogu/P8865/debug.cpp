#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n = 4, m = 3, c = 1, f = 1;
    vector<string> g = {
        "001",
        "010",
        "000",
        "000"
    };
    int ans_c = 0, ans_f = 0;
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
                    cout << "C at y0=" << y0 << " x1=" << x1 << " x2=" << x2 << " len1=" << len1 << " len2=" << len2 << endl;
                    ans_c += len1 * len2;
                    for (int x3 = x2 + 1; x3 < n; ++x3) {
                        if (g[x3][y0] == '0') ans_f += len1 * len2;
                        else break;
                    }
                }
            }
        }
    }
    cout << "ans_c: " << ans_c << " ans_f: " << ans_f << endl;
    return 0;
}
