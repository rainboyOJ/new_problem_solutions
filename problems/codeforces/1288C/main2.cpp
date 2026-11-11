#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int f[15][1005][1005];
int S[1005][1005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // pos = 1 初始化
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            f[1][i][j] = 1;
        }
    }

    // 二维前缀/后缀和优化转移
    for (int pos = 2; pos <= m; ++pos) {
        // 构建上一层的二维前缀和 S[u][v] = sum_{x=1}^u sum_{y=v}^n f[pos-1][x][y]
        // u 从 1 到 n 递增（前缀），v 从 n 到 1 递减（后缀）
        for (int u = 1; u <= n; ++u) {
            for (int v = n; v >= 1; --v) {
                long long val = (long long)S[u - 1][v] + S[u][v + 1] - S[u - 1][v + 1] + f[pos - 1][u][v];
                S[u][v] = (val % MOD + MOD) % MOD;
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                f[pos][i][j] = S[i][j];
            }
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            ans = (ans + f[m][i][j]) % MOD;
        }
    }

    cout << ans << "\n";
    return 0;
}
