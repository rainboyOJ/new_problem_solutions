/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:18
 * update_at: 2026-10-05 04:18
 */

// 最小环 + 输出方案：以环上编号最大的点 k 拆环，
// 环长 = dist(i,j) + w(i,k) + w(k,j)，其中 dist 只允许经过编号 < k 的中间点。
// Floyd 第 k 轮松弛开始前，dist[i][j] 恰好就是这种受限最短路，
// 所以每轮先探测候选环，再做标准 Floyd 松弛；松弛时同步维护后继表用于还原路径。
// 无向图可能有重边：重边取最短；自环凑不出 3 点环，忽略。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;
const ll INF = 1e12; // 无穷哨兵：环长是边权之和，达不到这个量级

int n, m;
ll w[MAXN][MAXN];    // w[i][j]：i、j 之间最短边的权，不相邻为 INF
ll dist_[MAXN][MAXN]; // dist_[i][j]：中间点限制在编号 < k 的最短路（避开 std 的 dist 名字不必要，仅区分含义）
int nxt[MAXN][MAXN]; // 后继表：i 走向 j 的下一个点，用于把路径还原成点序列
ll best;             // 当前最小环长
int cyc[MAXN];       // 最优环上的点（1 编号），按环上顺序
int cyc_len;         // 环上点数

// 用后继表把 i -> j 的最短路回溯成点序列，再接上 k 闭合成环，存入 cyc[]
void record_cycle(int i, int j, int k) {
    int path[MAXN];
    int len = 0;
    path[len++] = i;
    while (path[len - 1] != j) {
        path[len] = nxt[path[len - 1]][j];
        len++;
    }
    cyc_len = 0;
    for (int t = 0; t < len; t++) cyc[cyc_len++] = path[t];
    cyc[cyc_len++] = k; // 按环上顺序：i -> ... -> j -> k，k 再回到 i
}

void solve() {
    // 初始化：dist 初始就是邻接矩阵；后继表初始为直达的下一个点
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist_[i][j] = w[i][j];
            if (w[i][j] < INF) nxt[i][j] = j; // i 直达 j，后继就是 j 本身
            else nxt[i][j] = -1;
        }
    }
    best = INF;
    cyc_len = 0;

    for (int k = 1; k <= n; k++) {
        // 第一步：用还没并入 k 的受限最短路探测候选环 i -> ... -> j -> k -> i
        for (int i = 1; i < k; i++) {
            if (w[i][k] >= INF) continue; // i、k 不相邻，闭不回环
            for (int j = i + 1; j < k; j++) {
                // w[k][j] 为 INF 时候选溢出，自然不会更优
                ll cand = dist_[i][j] + w[i][k] + w[k][j];
                if (cand < best) {
                    best = cand;
                    record_cycle(i, j, k);
                }
            }
        }

        // 第二步：标准 Floyd 的 k 阶段松弛，把 k 变成允许的中间点
        for (int i = 1; i <= n; i++) {
            if (dist_[i][k] >= INF) continue;
            for (int j = 1; j <= n; j++) {
                if (dist_[i][k] + dist_[k][j] < dist_[i][j]) {
                    dist_[i][j] = dist_[i][k] + dist_[k][j];
                    nxt[i][j] = nxt[i][k]; // i 去 j 先迈向 i 的 k-后继
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            w[i][j] = INF;
    for (int i = 1; i <= n; i++) w[i][i] = 0;
    for (int e = 1; e <= m; e++) {
        int x, y; ll z;
        cin >> x >> y >> z;
        if (x != y && z < w[x][y]) { // 重边取最短，自环忽略
            w[x][y] = z;
            w[y][x] = z;
        }
    }

    solve();

    if (cyc_len == 0) {
        cout << "No solution." << endl;
    } else {
        for (int t = 0; t < cyc_len; t++) {
            if (t) cout << ' ';
            cout << cyc[t];
        }
        cout << endl;
    }

    return 0;
}
