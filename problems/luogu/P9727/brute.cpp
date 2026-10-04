/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 16:55
 */
// P9727 暴力对拍解：求「最少 0 的个数」。
//
// 关键观察（只用来做等价变换，不做任何关于答案的猜测）：
//   「没有 4 个连续的 1」 等价于 「所有长度为 4 的横条和竖条都至少含一个 0」。
// 也就是说，0 的集合必须是所有 4 连段的「命中集」。于是暴力可以这样枚举：
//
//   设下界 low = max(n*(m/4), m*(n/4))（横向 / 纵向各自能塞下的互不相交 4 连段数），
//   对每个 z = low, low+1, ... 依次尝试：
//      用最朴素的方式枚举大小恰好为 z 的命中集（每次挑「第一条还没被命中的
//      4 连段」，枚举用它的 4 个格子之一下去命中），
//      对每个枚举到的 0 集，检查剩下的 1 是否四连通；
//      只要找到一个就说明答案是 z，立即输出。
//
// 这样枚举的规模远小于 2^(nm)，而且完全正确、不做任何假设：
// 第一层循环的 z 就是答案，dfs 没有找到任何可行解才会增大 z。
// 只用于对拍的小数据（生成器保证 n*m <= 36，此时单边最大是 2 x 18，
// 所以 MAXN 要开到 18 以上，否则 2 x 17 这类瘦长条会越界）。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int n, m;
int seg[4 * MAXN * MAXN][4][2]; // 每条 4 连段的 4 个格子坐标
int segCnt;
bool zero[MAXN][MAXN]; // 当前被选中当 0 的格子
int sel[MAXN][MAXN];   // sel[i][j] = 该格子的 0 是在第几层被选的

// 当前所有 4 连段是否都已经被命中
int find_unhit() {
    for (int s = 0; s < segCnt; s++) {
        bool hit = false;
        for (int k = 0; k < 4; k++)
            if (zero[seg[s][k][0]][seg[s][k][1]]) { hit = true; break; }
        if (!hit) return s;
    }
    return -1;
}

// 检查 1 是否四连通（没有 1 视为不合法）
bool connected() {
    static int qx[MAXN * MAXN], qy[MAXN * MAXN];
    static bool vis[MAXN][MAXN];
    int si = -1, sj = -1, ones = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (!zero[i][j]) {
                ones++;
                if (si < 0) { si = i; sj = j; }
            }
    if (ones == 0) return false;
    memset(vis, 0, sizeof(vis));
    int head = 0, tail = 0, cnt = 0;
    qx[tail] = si; qy[tail] = sj; tail++; vis[si][sj] = true;
    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
    while (head < tail) {
        int x = qx[head], y = qy[head]; head++; cnt++;
        for (int d = 0; d < 4; d++) {
            int a = x + dx[d], b = y + dy[d];
            if (a < 0 || b < 0 || a >= n || b >= m) continue;
            if (zero[a][b] || vis[a][b]) continue;
            vis[a][b] = true;
            qx[tail] = a; qy[tail] = b; tail++;
        }
    }
    return cnt == ones;
}

// 已经放了 used 个 0，还允许再放 left 个；找大小 <= z 的可行命中集
bool dfs(int left) {
    int s = find_unhit();
    if (s < 0) return connected(); // 已命中所有 4 连段，只需再检查连通性
    if (left == 0) return false;
    for (int k = 0; k < 4; k++) {
        int x = seg[s][k][0], y = seg[s][k][1];
        if (zero[x][y]) continue;
        zero[x][y] = true;
        if (dfs(left - 1)) return true;
        zero[x][y] = false;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        segCnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j + 3 < m; j++) {
                for (int k = 0; k < 4; k++) { seg[segCnt][k][0] = i; seg[segCnt][k][1] = j + k; }
                segCnt++;
            }
        for (int j = 0; j < m; j++)
            for (int i = 0; i + 3 < n; i++) {
                for (int k = 0; k < 4; k++) { seg[segCnt][k][0] = i + k; seg[segCnt][k][1] = j; }
                segCnt++;
            }

        memset(zero, 0, sizeof(zero));
        int low = max(n * (m / 4), m * (n / 4));
        int ans = -1;
        for (int z = low; z <= n * m; z++) {
            memset(zero, 0, sizeof(zero));
            if (dfs(z)) { ans = z; break; }
        }
        cout << n * m - ans << '\n';
    }
    return 0;
}
