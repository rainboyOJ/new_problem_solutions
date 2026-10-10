/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int NEG = -1000000000;

int n, m, p;
int coin[1005][1005];   // coin[i][t]：第 i 条马路在第 t 个时间单位出现的金币
int cost[1005];         // 每个工厂买机器人的花费

ll prefix[1005];
deque<pair<int, ll> > queues[1005];   // (k, dp[k] - prefix - cost)
ll dp[1005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> p;
    for (int i = 0; i < n; i++)
        for (int t = 1; t <= m; t++)
            cin >> coin[i][t];
    for (int i = 0; i < n; i++) cin >> cost[i];

    for (int i = 0; i < n; i++) prefix[i] = 0;
    dp[0] = 0;
    for (int j = 1; j <= m; j++) {
        ll best = NEG;
        for (int c = 0; c < n; c++) {
            int k = j - 1;
            ll value = dp[k] - prefix[c] - cost[(k + c) % n];
            deque<pair<int, ll> >& q = queues[c];
            while (!q.empty() && q.back().second <= value) q.pop_back();
            q.push_back(make_pair(k, value));
            while (q.front().first < j - p) q.pop_front();
            prefix[c] += coin[(j + c - 1) % n][j];
            best = max(best, prefix[c] + q.front().second);
        }
        dp[j] = best;
    }
    cout << dp[m] << "\n";
    return 0;
}
