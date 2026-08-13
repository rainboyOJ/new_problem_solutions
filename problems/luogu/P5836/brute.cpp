/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:58
 * update_at: 2026-08-12 22:58
 */
// brute.cpp：小数据暴力解，每次查询沿路径 DFS 找路并统计颜色，用来理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
char color[MAXN];       // color[i] 为 'G' 或 'H'
vector<int> g[MAXN];    // 树的邻接表
int path[MAXN];         // 记录当前 DFS 找到的路径节点
int path_len;           // 当前路径长度
bool vis[MAXN];         // 标记节点是否被访问
bool found;             // 是否已经找到目标节点

// 从 u 出发寻找 target，把路径存入 path[]；每一步选择往哪个邻居走。
void dfs_find(int u, int target) {
    vis[u] = true;
    path[path_len++] = u;
    if (u == target) {
        found = true;
        return;
    }
    for (int v : g[u]) {
        if (vis[v] || found) continue;
        dfs_find(v, target);
        if (found) return;
    }
    path_len--; // 回溯：这条路不通，撤销这个节点
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    cin >> (color + 1);
    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    string ans;
    for (int i = 1; i <= m; i++) {
        int a, b;
        char want;
        cin >> a >> b >> want;

        // 每次查询都重新 DFS 找 a 到 b 的路径，复杂度 O(n)。
        memset(vis, 0, sizeof(vis));
        path_len = 0;
        found = false;
        dfs_find(a, b);

        // 统计路径上 G 的数量，H 的数量用总长度减 G 的数量补出。
        int cntG = 0;
        for (int j = 0; j < path_len; j++)
            if (color[path[j]] == 'G') cntG++;
        int cntH = path_len - cntG;

        if (want == 'G')
            ans.push_back(cntG > 0 ? '1' : '0');
        else
            ans.push_back(cntH > 0 ? '1' : '0');
    }
    cout << ans << '\n';

    return 0;
}
