// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 205;

int n, m;
int x[MAXM];
long long ans_a[MAXM], ans_b[MAXM], ans_c[MAXM], ans_d[MAXM];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> x[i];
    }

    // 直接枚举四个不同的物品，按定义判断是否构成魔法阵。
    // 复杂度 O(m^4)，只适合很小的数据，但逻辑最直接。
    for (int a = 1; a <= m; a++) {
        for (int b = 1; b <= m; b++) {
            if (b == a) continue;
            for (int c = 1; c <= m; c++) {
                if (c == a || c == b) continue;
                for (int d = 1; d <= m; d++) {
                    if (d == a || d == b || d == c) continue;

                    int xa = x[a];
                    int xb = x[b];
                    int xc = x[c];
                    int xd = x[d];

                    if (!(xa < xb && xb < xc && xc < xd)) continue;
                    if (xb - xa != 2 * (xd - xc)) continue;
                    if (xb - xa >= (xc - xb) / 3.0) continue;

                    ans_a[a]++;
                    ans_b[b]++;
                    ans_c[c]++;
                    ans_d[d]++;
                }
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        cout << ans_a[i] << ' ' << ans_b[i] << ' ' << ans_c[i] << ' ' << ans_d[i] << '\n';
    }

    return 0;
}
