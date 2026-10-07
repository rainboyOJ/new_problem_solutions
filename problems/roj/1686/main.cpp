/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 17:48
 * update_at: 2026-10-07 17:48
 */
// 1686 最小操作次数
// 一本通 / ROJ 1686 —— 网格滑行 + 顺序取字符的最小操作数
//
// 算法：分层最短路（DP + 多源 Dijkstra / Dial 桶队列）
//   目标串 t = s + '*'，设 L = |t|。
//   一次"选择"必然贡献 1 次操作，且恰好要选择 L 个字符，
//   所以 答案 = L + （最少滑行次数）。于是只需最小化滑行次数。
//
//   记 g[j][u] = 从起点出发、已按顺序选出 t 的前 j 个字符、且当前停在格子 u 时，
//   所用的最少滑行次数。则
//       g[0][u] = d(起点, u)                      // 还没选字符，可以任意滑行
//       g[j][v] = min{ g[j-1][u] + d(u, v) : g[u] == t[j-1] }   // 在 u 处选第 j 个字符
//   其中 d(u, v) 是"滑行图"（一次滑行 = 一条边权为 1 的边）上的最短距离。
//   答案为 L + min{ g[L-1][u] : g[u] == t[L-1] }（最后一个字符选完即结束，无需再滑）。
//
//   每一层的 min{...} 是多源最短路：源点 = 字符匹配 t[j-1] 的格子，初值 = g[j-1][u]。
//   边权全为 1 且初值非负，用 Dial 桶队列（按距离值开桶）实现，复杂度线性。
//   由于 g[j][v] <= g[j][u] + d(u,v)（从 u 滑到 v 是合法延续），每层取值跨度
//   不超过"滑行图直径"，桶数组实际很小；桶按每层实际 min/max 动态开。
//
// 复杂度：时间 O(L * (n*m + 桶跨度))，空间 O(n*m + 桶跨度)，n*m <= 2500，L <= 10001。
// 注：素材源 std.cpp 用 (格子,已匹配数) 状态做 BFS，需要 n*m*(L+1) 个 int
//     （约 100MB）；本解改为分层最短路，把空间压到 O(n*m)。

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 55;      // n, m <= 50
const int MAXC = 2505;    // n*m <= 2500
const int INF = 1e9;

int n, m;                 // 矩阵行列数
int L;                    // 目标串长度 = |s| + 1
int nm;                   // n*m
char grid[MAXN][MAXN];    // 矩阵（0 下标）
char t[10015];            // 目标串 s + '*'
int nxt[MAXC][4];         // 滑行落点（扁平编号），-1 表示会滑出边界
int cur[MAXC];            // g[j-1][*]
int nd[MAXC];             // g[j][*]
int dist[MAXC];           // 当前层多源最短路结果

const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

int main() {
    if (scanf("%d %d", &n, &m) != 2) return 0;
    for (int i = 0; i < n; i++) scanf("%s", grid[i]);
    char sbuf[10015];
    scanf("%s", sbuf);
    strcpy(t, sbuf);
    t[strlen(sbuf)] = '*';           // 目标串 = s + '*'
    L = (int)strlen(t);
    nm = n * m;

    // 预处理四个方向的滑行落点：沿该方向一直走，直到字符与当前格不同
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                while (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                       grid[nr][nc] == grid[r][c]) {
                    nr += dr[d];
                    nc += dc[d];
                }
                if (nr < 0 || nr >= n || nc < 0 || nc >= m) nxt[r * m + c][d] = -1;
                else nxt[r * m + c][d] = nr * m + nc;
            }

    // g[0][u] = d(起点, u)：从左上角出发的滑行最短路
    for (int u = 0; u < nm; u++) cur[u] = INF;
    {
        queue<int> q;
        cur[0] = 0;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int d = 0; d < 4; d++) {
                int v = nxt[u][d];
                if (v >= 0 && cur[v] > cur[u] + 1) {
                    cur[v] = cur[u] + 1;
                    q.push(v);
                }
            }
        }
    }

    // 逐层推进：第 j 层要求选出 t[j-1]，初值来自上一层的 cur
    vector<vector<int>> bucket;
    for (int j = 1; j <= L - 1; j++) {
        char need = t[j - 1];
        // 收集源点（字符匹配 t[j-1] 且已可达），求本层多源最短路
        int mn = INF, mx = -INF;
        for (int u = 0; u < nm; u++) {
            if (cur[u] >= INF) continue;
            if (grid[u / m][u % m] != need) continue;
            mn = min(mn, cur[u]);
            mx = max(mx, cur[u]);
        }
        if (mn >= INF) {           // 题面保证有解，这里只是防御
            printf("-1\n");
            return 0;
        }
        // Dial 桶队列：桶下标 = 距离 - mn，范围不超过初值跨度 + 滑行图直径
        int range = mx - mn + nm + 2;
        bucket.assign(range, vector<int>());
        for (int u = 0; u < nm; u++) {
            dist[u] = INF;
            if (cur[u] >= INF) continue;
            if (grid[u / m][u % m] != need) continue;
            dist[u] = cur[u];
            bucket[cur[u] - mn].push_back(u);
        }
        for (int b = 0; b < range; b++) {
            for (size_t i = 0; i < bucket[b].size(); i++) {
                int u = bucket[b][i];
                if (dist[u] != b + mn) continue;   // 桶里的过期副本，已按更小值处理过
                for (int d = 0; d < 4; d++) {
                    int v = nxt[u][d];
                    if (v >= 0 && dist[u] + 1 < dist[v]) {
                        dist[v] = dist[u] + 1;
                        bucket[dist[v] - mn].push_back(v);
                    }
                }
            }
        }
        // 第 j 个字符必须在停下的格子上选出，否则该状态无效
        char nx = t[j];
        for (int u = 0; u < nm; u++) {
            if (dist[u] < INF && grid[u / m][u % m] == nx) nd[u] = dist[u];
            else nd[u] = INF;
        }
        for (int u = 0; u < nm; u++) cur[u] = nd[u];
    }

    // 答案 = L（选择的次数）+ 最少滑行次数
    int best = INF;
    char last = t[L - 1];
    for (int u = 0; u < nm; u++)
        if (cur[u] < INF && grid[u / m][u % m] == last) best = min(best, cur[u]);
    printf("%d\n", L + best);
    return 0;
}
