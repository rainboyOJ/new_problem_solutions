/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:03
 * update_at: 2026-11-10 23:03
 */
#include <iostream>

using namespace std;

const int MOD = 998244353;
const int MAXN = 35;
const int MAXM = 105;

int n, m, K;
int v[MAXM];
int c[MAXN][MAXN];       // 组合数 C(n, m)
int v_pow[MAXM][MAXN];   // v[i]^t % MOD
int dp[MAXM][MAXN][MAXN][MAXN]; // dp[i][j][k][p]: 处理完前 i 位，选了 j 个数，产生了 k 个 1，向第 i 位进位 p

// 预处理组合数与幂次
void init() {
    for (int i = 0; i <= n; ++i) {
        c[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
        }
    }

    for (int i = 0; i <= m; ++i) {
        v_pow[i][0] = 1;
        for (int t = 1; t <= n; ++t) {
            v_pow[i][t] = static_cast<long long>(v_pow[i][t - 1]) * v[i] % MOD;
        }
    }
}

int count_ones(int x) {
    return __builtin_popcount(x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m >> K)) return 0;
    for (int i = 0; i <= m; ++i) {
        cin >> v[i];
    }

    init();

    dp[0][0][0][0] = 1;

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k <= K; ++k) {
                for (int p = 0; p <= (n / 2); ++p) {
                    if (dp[i][j][k][p] == 0) continue;

                    long long cur_val = dp[i][j][k][p];

                    // 枚举当前第 i 位分配 t 个数
                    for (int t = 0; t <= n - j; ++t) {
                        int sum = p + t;
                        int new_k = k + (sum % 2);
                        if (new_k > K) continue;

                        int new_p = sum / 2;
                        // 选取 t 个数的组合方式 * 权值
                        long long ways = static_cast<long long>(c[n - j][t]) * v_pow[i][t] % MOD;
                        long long add = cur_val * ways % MOD;

                        dp[i + 1][j + t][new_k][new_p] = (dp[i + 1][j + t][new_k][new_p] + add) % MOD;
                    }
                }
            }
        }
    }

    // 统计最终答案
    long long ans = 0;
    for (int k = 0; k <= K; ++k) {
        for (int p = 0; p <= (n / 2); ++p) {
            if (k + count_ones(p) <= K) {
                ans = (ans + dp[m + 1][n][k][p]) % MOD;
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
