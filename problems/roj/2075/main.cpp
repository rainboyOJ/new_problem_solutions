/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:32
 * update_at: 2026-10-06 11:32
 */

// main.cpp：重叠的图像（usaco 4.4.3 frameup）
// 做法：由每个字母出现位置的极值坐标还原矩形边框，
//       边框上出现的其它字母说明后者覆盖在前者之上，连边 u -> v，
//       最后回溯搜索所有合法的自底向上拓扑序，按字典序输出。

#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 35;

int h, w;
char grid[MAXN][MAXN];      // 输入网格
char path[30];              // 当前正在构造的拓扑序列
bool used[26];              // 某个字母是否已经在当前序列中
bool exist[26];             // 某个字母是否出现
bool adj[26][26];           // adj[u][v] = true 表示 u 必须排在 v 前面（v 覆盖 u）
int indeg[26];              // 拓扑搜索用入度
int minr[26], maxr[26], minc[26], maxc[26]; // 每个字母边框的极值坐标
int total = 0;              // 出现的矩形（字母）个数

// 用边框上的覆盖关系建图：u 的边上出现字母 v（v != u），说明 v 盖住了 u，连边 u -> v
void build_graph() {
    memset(adj, 0, sizeof(adj));
    memset(indeg, 0, sizeof(indeg));
    for (int u = 0; u < 26; ++u) {
        if (!exist[u]) continue;
        for (int c = minc[u]; c <= maxc[u]; ++c) { // 上下两条边
            int v = grid[minr[u]][c] - 'A';
            if (v != u && exist[v] && !adj[u][v]) { adj[u][v] = true; ++indeg[v]; }
            v = grid[maxr[u]][c] - 'A';
            if (v != u && exist[v] && !adj[u][v]) { adj[u][v] = true; ++indeg[v]; }
        }
        for (int r = minr[u]; r <= maxr[u]; ++r) { // 左右两条边
            int v = grid[r][minc[u]] - 'A';
            if (v != u && exist[v] && !adj[u][v]) { adj[u][v] = true; ++indeg[v]; }
            v = grid[r][maxc[u]] - 'A';
            if (v != u && exist[v] && !adj[u][v]) { adj[u][v] = true; ++indeg[v]; }
        }
    }
}

// 回溯搜索所有拓扑序：dep 表示已确定序列的前 dep 个字母
void dfs(int dep) {
    if (dep == total) { // 序列完整，输出一种合法的自底向上顺序
        path[total] = '\0';
        printf("%s\n", path);
        return;
    }
    for (int u = 0; u < 26; ++u) { // 按字母序枚举，保证输出按字典序
        if (!exist[u] || used[u] || indeg[u] != 0) continue;
        used[u] = true;
        path[dep] = 'A' + u;
        for (int v = 0; v < 26; ++v) // 拿掉 u 之后，它的后继入度减一
            if (adj[u][v]) --indeg[v];

        dfs(dep + 1);

        for (int v = 0; v < 26; ++v) // 回溯恢复
            if (adj[u][v]) ++indeg[v];
        used[u] = false;
    }
}

int main() {
    scanf("%d %d", &h, &w);
    for (int r = 0; r < h; ++r) scanf("%s", grid[r]);

    memset(exist, 0, sizeof(exist));
    memset(used, 0, sizeof(used));
    // 1. 扫描网格，求每个字母出现位置的极值行列号
    //    因为每条边至少有一部分可见，极值行列一定是边框四条边所在的位置
    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            if (grid[r][c] == '.') continue;
            int u = grid[r][c] - 'A';
            if (!exist[u]) {
                exist[u] = true;
                minr[u] = maxr[u] = r;
                minc[u] = maxc[u] = c;
                ++total;
            } else {
                if (r < minr[u]) minr[u] = r;
                if (r > maxr[u]) maxr[u] = r;
                if (c < minc[u]) minc[u] = c;
                if (c > maxc[u]) maxc[u] = c;
            }
        }
    }

    build_graph();
    dfs(0);
    return 0;
}
