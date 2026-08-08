#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;
const long long MOD = 1000000007LL;

int n, r_limit;
int eu[MAXN], ev[MAXN], et[MAXN];
int w[MAXN];
long long ways;
long long best_sum;

void dfs(int u) {
    if (u > n) {
        for (int i = 1; i < n; i++) {
            if (et[i] == 0 && w[eu[i]] == w[ev[i]]) {
                return;
            }
            if (et[i] == 2 && w[eu[i]] != w[ev[i]]) {
                return;
            }
        }

        ways = (ways + 1) % MOD;
        long long sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += w[i];
        }
        best_sum = min(best_sum, sum);
        return;
    }

    for (int val = 1; val <= r_limit; val++) {
        w[u] = val;
        dfs(u + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据暴力枚举所有点权，检查约束并统计答案。
    cin >> n >> r_limit;
    for (int i = 1; i < n; i++) {
        cin >> eu[i] >> ev[i] >> et[i];
    }

    ways = 0;
    best_sum = (1LL << 60);
    dfs(1);

    if (ways == 0) {
        cout << 0 << ' ' << 0 << '\n';
    } else {
        cout << ways % MOD << ' ' << best_sum << '\n';
    }
    return 0;
}
