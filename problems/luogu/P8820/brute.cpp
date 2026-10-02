/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:33
 * update_at: 2026-10-01 22:33
 */
// brute.cpp：小数据暴力解，先 Floyd 求树上距离，再在可直接传输图上 Floyd 求最短路。
// 只适合很小的数据（n <= 50 左右），三重循环 O(n^3)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 无穷大哨兵：4e18 远大于合法答案上界，且 2*INF 不溢出（Floyd 相加会用到）。
const ll INF = 4000000000000000000LL;
const int MAXN = 55;

int n, q, K;
ll value_cost[MAXN];      // value_cost[i]：主机 i 的处理时间（点权）
ll tree_dist[MAXN][MAXN]; // tree_dist[i][j]：树上 i 到 j 的边数
ll answer_dist[MAXN][MAXN]; // answer_dist[i][j]：从 i 传到 j 的最小总代价（含两端点权）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> K;
    for (int i = 1; i <= n; i++) {
        cin >> value_cost[i];
    }

    // Floyd 求树上任意两点距离。
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            tree_dist[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree_dist[u][v] = tree_dist[v][u] = 1;
    }

    for (int via = 1; via <= n; via++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (tree_dist[i][j] > tree_dist[i][via] + tree_dist[via][j]) {
                    tree_dist[i][j] = tree_dist[i][via] + tree_dist[via][j];
                }
            }
        }
    }

    // 建立"距离不超过 k 即可直接传输"的新图上的点权最短路模型：
    // 走到自己代价是点权，i 直达 j 的代价是两端点权之和。
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            answer_dist[i][j] = INF;
        }
        answer_dist[i][i] = value_cost[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && tree_dist[i][j] <= K) {
                answer_dist[i][j] = value_cost[i] + value_cost[j];
            }
        }
    }

    // Floyd 求最小总代价：经 via 中转时 via 的点权被加了两次，减掉一次。
    for (int via = 1; via <= n; via++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (answer_dist[i][j] > answer_dist[i][via] + answer_dist[via][j] - value_cost[via]) {
                    answer_dist[i][j] = answer_dist[i][via] + answer_dist[via][j] - value_cost[via];
                }
            }
        }
    }

    while (q--) {
        int s, t;
        cin >> s >> t;
        cout << answer_dist[s][t] << '\n';
    }

    return 0;
}
