/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:10
 * update_at: 2026-10-06 18:10
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 8;          // 棋盘最大边长
const int MAXV = MAXN * MAXN; // 格子总数最大值

int n;                       // 当前棋盘边长
ll full;                     // 全 1 掩码，表示所有格子都被吞并
ll color_mask[6];            // color_mask[c] 表示颜色 c 的格子集合
int grid[MAXV];              // grid[i] 表示第 i 个格子的颜色
vector<int> adj[MAXV];       // 每个格子的四邻接格子

// 初始时与左上角同色的连通区域（广度优先）
ll start_mask() {
    ll mask = 1;
    int q[MAXV], head = 0, tail = 0;
    q[tail++] = 0;
    while (head < tail) {
        int u = q[head++];
        for (int v : adj[u]) {
            if (grid[v] == grid[0] && !(mask >> v & 1)) {
                mask |= 1LL << v;
                q[tail++] = v;
            }
        }
    }
    return mask;
}

// 把当前区域 mask 染成 color，返回新区域
ll expand(ll mask, int color) {
    int q[MAXV], head = 0, tail = 0;
    // 种子：紧贴区域且颜色为 color 的格子
    for (int u = 0; u < n * n; ++u) {
        if (!(mask >> u & 1)) continue;
        for (int v : adj[u]) {
            if (grid[v] == color && !(mask >> v & 1)) {
                q[tail++] = v;
            }
        }
    }
    ll gained = 0;
    while (head < tail) {
        int u = q[head++];
        if (gained >> u & 1) continue;
        gained |= 1LL << u;
        for (int v : adj[u]) {
            if (grid[v] == color && !(mask >> v & 1) && !(gained >> v & 1)) {
                q[tail++] = v;
            }
        }
    }
    return mask | gained;
}

// 剩余颜色种数，是完成所需步数的可采纳下界
int remaining_colors(ll mask) {
    int cnt = 0;
    for (int c = 0; c < 6; ++c) {
        if (color_mask[c] & ~mask) ++cnt;
    }
    return cnt;
}

// IDA* 深度受限搜索：能否在 left 步内吞满整个棋盘
bool dfs(ll mask, int left) {
    if (mask == full) return true;
    if (remaining_colors(mask) > left) return false;

    // 生成 6 种颜色转移，去重，按启发值从小到大尝试
    ll nxt[6];
    int nxt_cnt = 0;
    for (int c = 0; c < 6; ++c) {
        ll ns = expand(mask, c);
        if (ns == mask) continue; // 该颜色没有吞到新格子
        bool dup = false;
        for (int i = 0; i < nxt_cnt; ++i) {
            if (nxt[i] == ns) { dup = true; break; }
        }
        if (!dup) nxt[nxt_cnt++] = ns;
    }
    // 按剩余颜色数升序排序，优先尝试更优分支
    for (int i = 0; i < nxt_cnt; ++i) {
        for (int j = i + 1; j < nxt_cnt; ++j) {
            if (remaining_colors(nxt[i]) > remaining_colors(nxt[j])) {
                ll tmp = nxt[i]; nxt[i] = nxt[j]; nxt[j] = tmp;
            }
        }
    }
    for (int i = 0; i < nxt_cnt; ++i) {
        if (dfs(nxt[i], left - 1)) return true;
    }
    return false;
}

// 求解单个测试用例
int solve_case() {
    if (n == 0) return 0;
    for (int i = 0; i < n * n; ++i) adj[i].clear();
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int u = r * n + c;
            if (r > 0) adj[u].push_back((r - 1) * n + c);
            if (r + 1 < n) adj[u].push_back((r + 1) * n + c);
            if (c > 0) adj[u].push_back(r * n + (c - 1));
            if (c + 1 < n) adj[u].push_back(r * n + (c + 1));
        }
    }
    for (int c = 0; c < 6; ++c) color_mask[c] = 0;
    for (int i = 0; i < n * n; ++i) {
        color_mask[grid[i]] |= 1LL << i;
    }
    full = (1LL << (n * n)) - 1;
    ll mask = start_mask();
    if (mask == full) return 0;
    int depth = remaining_colors(mask);
    while (!dfs(mask, depth)) ++depth;
    return depth;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n && n != 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) cin >> grid[i * n + j];
        }
        cout << solve_case() << "\n";
    }
    return 0;
}
