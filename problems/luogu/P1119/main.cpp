/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-10-20 15:45
 */
// 灾后重建：村庄按时间修复，询问某天只经过已修复村庄的最短路。
// 朴素做法是对每个询问重建图再跑一次 Floyd，代价 Q*N^3 必超时。
// 关键：Floyd 的中间点 k 不是在"迭代次数"，而是在控制"允许使用的中转点集合"，
// 跑完 k 轮就代表允许经过前 k 批点中转。而村庄只会修复不会摧毁，
// 所以已开放集合只增不减 —— 这两件事结构相同，就把 k 交给时间轴：
//   题面保证 t_i 非降、询问的 t 也非降，所以可以边读询问边往前推进指针，
//   每放开一个新村庄就让它当一次 k，做一轮 Floyd 加点转移。
// N 个点全程各只当一次中间点，总代价 O(N^3 + Q)，而不是 O(Q*N^3)。
// 复用旧矩阵的前提是单调收紧：新增中转点只会让最短路变短或不变，
// 所以旧值恒为新值的上界，不会成为错误答案。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;              // 村庄数上界 N <= 200
const long long INF = (1LL << 60);

int n, m;
int ready_day[MAXN];               // ready_day[i]：i 号村庄第几天修复完成
long long dist_node[MAXN][MAXN];   // dist_node[i][j]：只用已开放村庄中转的最短路

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> ready_day[i];  // 题面保证非降序

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist_node[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        // 公路双向；题面保证任意两点间只有一条路，直接赋值即可
        dist_node[u][v] = w;
        dist_node[v][u] = w;
    }

    int activated = 0;  // 已经放开到哪个村庄，它同时也是"下一次要用的 k"
    int query_cnt;
    cin >> query_cnt;

    for (int i = 0; i < query_cnt; i++) {
        int start, end, day;
        cin >> start >> end >> day;

        // 把修复时间不晚于今天、但还没当过中间点的村庄依次放开。
        // 每放开一个就做一轮 Floyd 加点转移：允许经过它的路径可能更短。
        while (activated < n && ready_day[activated] <= day) {
            int middle = activated;
            for (int x = 0; x < n; x++) {
                if (dist_node[x][middle] == INF) continue;  // x 到 middle 不可达，这一轮对 x 无改善
                long long base = dist_node[x][middle];
                for (int y = 0; y < n; y++) {
                    long long candidate = base + dist_node[middle][y];
                    if (candidate < dist_node[x][y]) {
                        dist_node[x][y] = candidate;
                    }
                }
            }
            activated++;
        }

        // 三种输出 -1 的情形：起点未修复、终点未修复、仍然不可达
        if (ready_day[start] > day || ready_day[end] > day || dist_node[start][end] == INF) {
            cout << -1 << '\n';
        } else {
            cout << dist_node[start][end] << '\n';
        }
    }

    return 0;
}
