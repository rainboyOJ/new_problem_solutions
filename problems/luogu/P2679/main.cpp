#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXM = 205;
const int MAXK = 205;

int n, m, need_k;
string a, b;
int total_dp[MAXM][MAXK]; // total_dp[j][c]：处理过当前 A 前缀后，拼出 B 前 j 位且用了 c 段的方案数。
int end_dp[MAXM][MAXK];   // end_dp[j][c]：必须选当前 A 字符作为 B[j]，且它在第 c 段内的方案数。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> need_k;
    cin >> a >> b;
    a = " " + a;
    b = " " + b;

    total_dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            for (int c = need_k; c >= 1; c--) {
                if (a[i] == b[j]) {
                    // 继续上一段：上一位 B[j-1] 必须刚好由 A[i-1] 结尾。
                    // 新开一段：前 j-1 位可以在 A[1..i-1] 任意位置结束。
                    end_dp[j][c] = ((long long)end_dp[j - 1][c] + total_dp[j - 1][c - 1]) % MOD;
                    total_dp[j][c] += end_dp[j][c];
                    if (total_dp[j][c] >= MOD) {
                        total_dp[j][c] -= MOD;
                    }
                } else {
                    end_dp[j][c] = 0;
                }
            }
        }
    }

    cout << total_dp[m][need_k] << '\n';

    return 0;
}
