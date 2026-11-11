#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int f[15][105][105];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 初始化第 1 个位置
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            f[1][i][j] = 1;
        }
    }

    // 暴力枚举上一步的所有 (u, v)
    for (int pos = 2; pos <= m; ++pos) {
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                long long sum = 0;
                for (int u = 1; u <= i; ++u) {
                    for (int v = j; v <= n; ++v) {
                        sum += f[pos - 1][u][v];
                    }
                }
                f[pos][i][j] = sum % MOD;
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
