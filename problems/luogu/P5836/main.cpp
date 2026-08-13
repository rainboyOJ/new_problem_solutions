/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:58
 * update_at: 2026-08-12 22:58
 */
// 主解：倍增 LCA + 根路径 G 前缀计数（仿 rbook 模板 lca-binary-lifting 改造）。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOG = 17; // 2^17 = 131072 > 1e5，足够覆盖最大深度

int n, m;
char color[MAXN];              // color[i] 为 'G' 或 'H'
vector<int> g[MAXN];           // 树的邻接表
int depth[MAXN];               // depth[i]：节点 i 到根 1 的深度（根深度为 1）
int up[MAXN][LOG + 1];         // up[u][j]：u 向上跳 2^j 步到达的祖先
int sumG[MAXN];                // sumG[i]：根到 i 的路径上 G 的数量（含 i 自己）

// 用 BFS 迭代预处理 depth、up 倍增表与根路径 G 前缀计数。
void build(int root) {
    queue<int> q;
    q.push(root);
    depth[root] = 1;
    sumG[root] = (color[root] == 'G');
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (v == up[u][0]) continue; // 跳过父亲
            up[v][0] = u;
            depth[v] = depth[u] + 1;
            sumG[v] = sumG[u] + (color[v] == 'G');
            for (int j = 1; j <= LOG; j++)
                up[v][j] = up[up[v][j - 1]][j - 1];
            q.push(v);
        }
    }
}

// 查询节点 u、v 的最近公共祖先。
int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    // 先把较深的节点向上跳到和较浅节点同一深度。
    int diff = depth[u] - depth[v];
    for (int j = 0; j <= LOG; j++)
        if (diff & (1 << j)) u = up[u][j];
    if (u == v) return u;
    // 再从大到小一起向上跳，最后停在 LCA 的下一层。
    for (int j = LOG; j >= 0; j--)
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    return up[u][0];
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

    build(1);

    string ans;
    for (int i = 1; i <= m; i++) {
        int a, b;
        char want;
        cin >> a >> b >> want;

        int c = lca(a, b);
        // 路径 a->b 上 G 的数量（含端点，用前缀和容斥）。
        int cntG = sumG[a] + sumG[b] - 2 * sumG[c] + (color[c] == 'G');
        // 路径上的点数，H 的数量用总点数减 G 的数量补出。
        int len = depth[a] + depth[b] - 2 * depth[c] + 1;
        int cntH = len - cntG;

        if (want == 'G')
            ans.push_back(cntG > 0 ? '1' : '0');
        else
            ans.push_back(cntH > 0 ? '1' : '0');
    }
    cout << ans << '\n';

    return 0;
}
