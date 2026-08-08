#include <bits/stdc++.h>
using namespace std;

const long long NEG_INF = -(1LL << 60);

int subtask_id;
int n, m, w;
long long k[25];
int p[25];
long long choose_best_k[205];
long long memo[1005][205];
bool vis[1005][205];
long long xa, xb;
int start_da, start_db;

long long dfs(int turn_left, int delta) {
    if (turn_left == 0) {
        return 0;
    }
    if (vis[turn_left][delta + 100]) {
        return memo[turn_left][delta + 100];
    }
    vis[turn_left][delta + 100] = true;

    long long ans;

    if (delta <= 0) {
        ans = NEG_INF;
        for (int sum_p = 0; sum_p <= 200; sum_p++) {
            if (choose_best_k[sum_p] == NEG_INF) {
                continue;
            }
            int next_delta = delta + w + sum_p;
            if (next_delta < -100 || next_delta > 100) {
                continue;
            }
            long long damage = xa + (xa / 100000) * choose_best_k[sum_p];
            ans = max(ans, damage + dfs(turn_left - 1, next_delta));
        }
    } else {
        ans = NEG_INF;
        for (int sum_p = 0; sum_p <= 200; sum_p++) {
            if (choose_best_k[sum_p] == NEG_INF) {
                continue;
            }
            int next_delta = delta - w - sum_p;
            if (next_delta < -100 || next_delta > 100) {
                continue;
            }
            long long damage = xb + (xb / 100000) * choose_best_k[sum_p];
            ans = max(ans, damage - dfs(turn_left - 1, next_delta));
        }
        ans = -ans;
    }

    memo[turn_left][delta + 100] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
    // 先枚举每个子集的 (sum_p, sum_k)，对同一 sum_p 保留最大的 sum_k，
    // 再按回合数和 d 值差做记忆化搜索。
    cin >> subtask_id;
    cin >> n >> m >> w;
    for (int i = 1; i <= m; i++) {
        cin >> k[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> p[i];
    }
    cin >> xa >> xb >> start_da >> start_db;

    for (int i = 0; i <= 200; i++) {
        choose_best_k[i] = NEG_INF;
    }
    choose_best_k[0] = 0;

    for (int mask = 0; mask < (1 << m); mask++) {
        int sum_p = 0;
        long long sum_k = 0;
        for (int i = 0; i < m; i++) {
            if ((mask >> i) & 1) {
                sum_p += p[i + 1];
                sum_k += k[i + 1];
            }
        }
        if (sum_p <= 200) {
            choose_best_k[sum_p] = max(choose_best_k[sum_p], sum_k);
        }
    }

    cout << dfs(n, start_da - start_db) << '\n';
    return 0;
}
