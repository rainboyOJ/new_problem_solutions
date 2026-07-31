/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 21:35
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXA = 100000;
const long long MOD = 1000000007;

int n, position[MAXN], blocked[MAXA + 1];
long long dp[MAXN];
vector<int> divisor[MAXA + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> position[i];
    for (int d = 1; d <= MAXA; d++) {
        for (int value = d; value <= MAXA; value += d) divisor[value].push_back(d);
    }

    dp[1] = 1;
    for (int left = 1; left < n; left++) {
        for (int right = left + 1; right <= n; right++) {
            int distance = position[right] - position[left];
            int ways = 0;
            for (int i = 0; i < (int)divisor[distance].size(); i++) {
                int step = divisor[distance][i];
                if (step != distance && blocked[step] != left) ways++;
            }
            dp[right] = (dp[right] + dp[left] * ways) % MOD;
            for (int i = 0; i < (int)divisor[distance].size(); i++) blocked[divisor[distance][i]] = left;
        }
    }
    cout << dp[n] << '\n';

    return 0;
}
