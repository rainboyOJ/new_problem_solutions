#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;

int n, m;
int w[MAXN];         // 物品重量（体积）
// f[j] 表示用所有物品凑出和为 j 的方案数。
int f[MAXN];
// g[j] 表示不含当前物品时，凑出和为 j 的方案数。
int g[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    // 第一遍：正序 DP 求出包含所有物品的方案数 f[]。
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= w[i]; j--) {
            f[j] = (f[j] + f[j - w[i]]) % 10;
        }
    }

    // 对每个物品 i，用 f[] - (包含 i 的方案) 得到不含 i 的方案数。
    for (int i = 1; i <= n; i++) {
        g[0] = 1;
        for (int j = 1; j <= m; j++) {
            if (j < w[i]) {
                g[j] = f[j];
            } else {
                // f[j] 中可能包含选了物品 i 的方案（即 g[j - w[i]]），
                // 从 f[j] 中减去这些方案得到不含 i 的方案数。
                g[j] = (f[j] - g[j - w[i]] + 10) % 10;
            }
        }
        for (int j = 1; j <= m; j++) {
            cout << g[j];
        }
        cout << '\n';
    }

    return 0;
}
