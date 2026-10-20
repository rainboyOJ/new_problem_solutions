/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-10-20 16:40
 */
// 社交网络：求每个点的重要度 I(v) = sum_{s!=v, t!=v} C(s,t)(v) / C(s,t)。
// 需要两个量：任意两点的最短路条数，以及经过 v 的最短路条数。
//
// 第一个量在 Floyd 里同步维护。Floyd 第 k 轮只在上一轮结论上加一件事：放开 k 这个中转点，
// 所以每轮的候选恰好是两类——不经 k 的（上一轮已有）和经 k 的（本轮新算）。两类互斥，
// 所以等长时累加不会重复；而一条经 k 的路径拆成 i->k 与 k->j 两段，两段独立选择，
// 所以条数相乘。
//
// 必须跳过 i == k 和 j == k：dist[i][k] 在 i == k 时是 0，那条"路径"原地没动，
// 它既不算"经 k"也不算"不经 k"，上述互斥前提被破坏，累加就会重复计数。
//
// 第二个量用距离的加性判断：v 在 s->t 的某条最短路上 <=> dist[s][v]+dist[v][t]==dist[s][t]。
// 此时 C(s,t)(v) = cnt[s][v] * cnt[v][t]，因为 v 在路径上的位置确定，拆分唯一。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;              // 点数上界 n <= 100
const long long INF = (1LL << 60);

int n, m;
long long dist_node[MAXN][MAXN];   // dist_node[i][j]：i 到 j 的最短距离
long long cnt_path[MAXN][MAXN];    // cnt_path[i][j]：i 到 j 的最短路条数
long double answer[MAXN];          // answer[v]：v 的重要程度

void read_input() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dist_node[i][j] = 0;
                cnt_path[i][j] = 1;  // 自己到自己有一条长度 0 的平凡路径
            } else {
                dist_node[i][j] = INF;
                cnt_path[i][j] = 0;
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        // 题面保证任意两点间最多一条边，直接赋值即可
        dist_node[u][v] = dist_node[v][u] = w;
        cnt_path[u][v] = cnt_path[v][u] = 1;
    }
}

// Floyd：距离与条数同步松弛
void floyd_with_count() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (i == k) continue;  // 必须跳过：否则 dist[i][k]=0 的平凡路径会被重复累加
            for (int j = 1; j <= n; j++) {
                if (j == k || i == j) continue;

                long long bridge = dist_node[i][k] + dist_node[k][j];
                // 先比较距离再算乘积：不是更优时直接跳过，避免算出一个可能溢出的乘积
                if (bridge > dist_node[i][j]) continue;

                long long ways = cnt_path[i][k] * cnt_path[k][j];
                if (bridge < dist_node[i][j]) {
                    // 经 k 更短：旧走法全部作废，条数替换
                    dist_node[i][j] = bridge;
                    cnt_path[i][j] = ways;
                } else {
                    // 经 k 一样短：一批新最短路，条数累加（两类路径互斥，不会重复）
                    cnt_path[i][j] += ways;
                }
            }
        }
    }
}

// 按定义累加每个点的重要度
void count_importance() {
    for (int v = 1; v <= n; v++) {
        long double total = 0;
        for (int s = 1; s <= n; s++) {
            if (s == v) continue;
            for (int t = 1; t <= n; t++) {
                if (t == v || t == s) continue;
                // v 在 s->t 的某条最短路上 <=> 两段距离之和等于总距离
                if (dist_node[s][v] + dist_node[v][t] == dist_node[s][t]) {
                    total += (long double)cnt_path[s][v] * cnt_path[v][t] / cnt_path[s][t];
                }
            }
        }
        answer[v] = total;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    floyd_with_count();
    count_importance();

    cout << fixed << setprecision(3);
    for (int i = 1; i <= n; i++) {
        cout << (double)answer[i] << '\n';
    }

    return 0;
}
