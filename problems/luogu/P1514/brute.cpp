/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 10:35
 * update_at: 2026-10-03 10:35
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 使用 01 序列 / 选择序列递归枚举所有可能：
//   第一行一共有 m 座城市，每座城市的决策只有两种——建蓄水厂或不建。
//   choose[j] = 1 表示在第 1 行第 j 列建蓄水厂，0 表示不建。
//   dfs_choose(dep) 只负责填写第 dep 座的决策，填满 choose[1..m] 后
//   在叶子节点统一做一次多源洪水填充，检查干旱区是否全部通水。
// 枚举 2^m 种方案，只有 m 很小时可用，所以只适合小数据对拍。
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 64; // 允许小规模生成器造到 n = 60；对拍时 m 会控制在 14 以内

int n, m;
int h[MAXN][MAXN];    // 海拔高度
int choose[MAXN];     // choose[j]：第 1 行第 j 列是否建蓄水厂
int seen[MAXN][MAXN]; // 洪水填充的访问标记
int able[MAXN];       // 干旱区第 j 列是否通水
int ans;              // 最少蓄水厂数量

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

// 从 (x, y) 出发把能流到的城市全部标记；到第 n 行就记录通水。
void flood(int x, int y) {
    seen[x][y] = 1;
    if (x == n) able[y] = 1;

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
        if (seen[nx][ny]) continue;
        if (h[nx][ny] >= h[x][y]) continue; // 水往低处流
        flood(nx, ny);
    }
}

// 检查当前 choose[] 是否能让干旱区全部通水。
// 能通水时返回蓄水厂数量，不能通水时返回 -1。
int check() {
    int cnt = 0;
    for (int j = 1; j <= m; j++) {
        cnt += choose[j];
    }
    if (cnt == 0) return -1; // 一个蓄水厂都没有，不可能通水

    memset(seen, 0, sizeof(seen));
    memset(able, 0, sizeof(able));
    for (int j = 1; j <= m; j++) {
        if (choose[j] == 1) flood(1, j);
    }

    for (int j = 1; j <= m; j++) {
        if (able[j] == 0) return -1;
    }
    return cnt;
}

// 每一层决定第 dep 座城市建不建蓄水厂。
void dfs_choose(int dep) {
    if (dep == m + 1) {
        int cnt = check();
        if (cnt != -1 && cnt < ans) ans = cnt;
        return;
    }

    for (int v = 0; v <= 1; v++) {
        choose[dep] = v;
        dfs_choose(dep + 1);
    }
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> h[i][j];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();

    ans = MAXN * MAXN; // 一个肯定取不到的初值
    dfs_choose(1);

    if (ans < MAXN * MAXN) {
        cout << 1 << "\n" << ans << "\n";
        return 0;
    }

    // 无解：把全部城市都建成蓄水厂，数一数干旱区里还有多少座通不了水。
    for (int j = 1; j <= m; j++) choose[j] = 1;
    memset(seen, 0, sizeof(seen));
    memset(able, 0, sizeof(able));
    for (int j = 1; j <= m; j++) flood(1, j);

    int bad = 0;
    for (int j = 1; j <= m; j++) {
        if (able[j] == 0) bad++;
    }
    cout << 0 << "\n" << bad << "\n";

    return 0;
}
