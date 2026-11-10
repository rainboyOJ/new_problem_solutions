/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:39
 * update_at: 2026-11-10 23:39
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

using ll = long long;
const ll INF = 1e18; // 足够大的无穷大
const int MAXN = 100005;
const int MAX_LOG = 18;

int n, m;
string problem_type;
ll p[MAXN];
vector<int> tree[MAXN];

int depth[MAXN];
int up[MAXN][MAX_LOG];

// f[u][0]: u 不驻扎时，以 u 为根子树的最小花费
// f[u][1]: u 驻扎时，以 u 为根子树的最小花费
ll f[MAXN][2];

// trans[u][j][x][y]:
// u 取状态 x (0/1) 时，跳到 2^j 级祖先 fa 取状态 y (0/1)，
// fa 的子树中（排除 u 的整棵子树后加上 u 取 x）的最小权值
ll trans[MAXN][MAX_LOG][2][2];

// 第一次 DFS：求出普通的树形 DP 值
void dfs1(int u, int fa) {
    depth[u] = depth[fa] + 1;
    up[u][0] = fa;
    f[u][0] = 0;
    f[u][1] = p[u];

    for (int v : tree[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        f[u][0] += f[v][1];
        f[u][1] += min(f[v][0], f[v][1]);
    }
}

// 预处理倍增转移表
void init_doubling() {
    for (int u = 1; u <= n; ++u) {
        int fa = up[u][0];
        if (fa != 0) {
            // fa 不驻扎 (y=0)，u 必须驻扎 (x=1)
            trans[u][0][0][0] = INF;
            trans[u][0][1][0] = f[fa][0] - f[u][1];

            // fa 驻扎 (y=1)，u 可驻扎也可不驻扎
            ll rest = f[fa][1] - min(f[u][0], f[u][1]);
            trans[u][0][0][1] = rest;
            trans[u][0][1][1] = rest;
        } else {
            for (int x = 0; x < 2; ++x) {
                for (int y = 0; y < 2; ++y) {
                    trans[u][0][x][y] = (x == y ? 0 : INF);
                }
            }
        }
    }

    for (int j = 1; j < MAX_LOG; ++j) {
        for (int u = 1; u <= n; ++u) {
            int anc = up[u][j - 1];
            up[u][j] = up[anc][j - 1];

            for (int x = 0; x < 2; ++x) {
                for (int y = 0; y < 2; ++y) {
                    ll val = INF;
                    for (int mid = 0; mid < 2; ++mid) {
                        if (trans[u][j - 1][x][mid] < INF && trans[anc][j - 1][mid][y] < INF) {
                            val = min(val, trans[u][j - 1][x][mid] + trans[anc][j - 1][mid][y]);
                        }
                    }
                    trans[u][j][x][y] = val;
                }
            }
        }
    }
}

// 回答单次询问
ll query(int a, int x, int b, int y) {
    // 深度大的放 a
    if (depth[a] < depth[b]) {
        swap(a, b);
        swap(x, y);
    }

    // dp 向量：[0] 为不选的花费，[1] 为选的花费
    ll cur_a[2] = {INF, INF};
    cur_a[x] = f[a][x];

    ll cur_b[2] = {INF, INF};
    cur_b[y] = f[b][y];

    // 先把 a 跳到和 b 相同的深度
    for (int j = MAX_LOG - 1; j >= 0; --j) {
        if (depth[a] - (1 << j) >= depth[b]) {
            ll next_a[2] = {INF, INF};
            for (int cur = 0; cur < 2; ++cur) {
                if (cur_a[cur] >= INF) continue;
                for (int nxt = 0; nxt < 2; ++nxt) {
                    if (trans[a][j][cur][nxt] < INF) {
                        next_a[nxt] = min(next_a[nxt], cur_a[cur] + trans[a][j][cur][nxt]);
                    }
                }
            }
            cur_a[0] = next_a[0];
            cur_a[1] = next_a[1];
            a = up[a][j];
        }
    }

    // 如果 b 本身就是 a 的祖先
    if (a == b) {
        // 此时 a 和 b 重合，但之前指定的约束为 y，所以 cur_a[1-y] 无效
        cur_a[1 - y] = INF;

        // 继续从 b 向上跳到根节点
        for (int j = MAX_LOG - 1; j >= 0; --j) {
            if (up[b][j] != 0) {
                ll next_b[2] = {INF, INF};
                for (int cur = 0; cur < 2; ++cur) {
                    if (cur_a[cur] >= INF) continue;
                    for (int nxt = 0; nxt < 2; ++nxt) {
                        if (trans[b][j][cur][nxt] < INF) {
                            next_b[nxt] = min(next_b[nxt], cur_a[cur] + trans[b][j][cur][nxt]);
                        }
                    }
                }
                cur_a[0] = next_b[0];
                cur_a[1] = next_b[1];
                b = up[b][j];
            }
        }
        ll ans = min(cur_a[0], cur_a[1]);
        return (ans >= INF ? -1 : ans);
    }

    // 一起向上跳，跳到 LCA 的子节点
    for (int j = MAX_LOG - 1; j >= 0; --j) {
        if (up[a][j] != up[b][j]) {
            ll next_a[2] = {INF, INF};
            ll next_b[2] = {INF, INF};
            for (int cur = 0; cur < 2; ++cur) {
                for (int nxt = 0; nxt < 2; ++nxt) {
                    if (cur_a[cur] < INF && trans[a][j][cur][nxt] < INF) {
                        next_a[nxt] = min(next_a[nxt], cur_a[cur] + trans[a][j][cur][nxt]);
                    }
                    if (cur_b[cur] < INF && trans[b][j][cur][nxt] < INF) {
                        next_b[nxt] = min(next_b[nxt], cur_b[cur] + trans[b][j][cur][nxt]);
                    }
                }
            }
            cur_a[0] = next_a[0];
            cur_a[1] = next_a[1];
            cur_b[0] = next_b[0];
            cur_b[1] = next_b[1];
            a = up[a][j];
            b = up[b][j];
        }
    }

    // 此时 a 和 b 的父节点就是 LCA
    int lca = up[a][0];

    // 在 lca 处合并来自 a 和 b 两个子分支的贡献
    ll cur_lca[2];
    // lca 不选 (0)：其所有子节点必须驻扎
    cur_lca[0] = f[lca][0] - f[a][1] - f[b][1] + cur_a[1] + cur_b[1];
    if (cur_a[1] >= INF || cur_b[1] >= INF) cur_lca[0] = INF;

    // lca 选 (1)：子节点可选可不选
    ll rest_lca = f[lca][1] - min(f[a][0], f[a][1]) - min(f[b][0], f[b][1]);
    ll min_a = min(cur_a[0], cur_a[1]);
    ll min_b = min(cur_b[0], cur_b[1]);
    if (min_a >= INF || min_b >= INF) cur_lca[1] = INF;
    else cur_lca[1] = rest_lca + min_a + min_b;

    // 从 LCA 一路跳到根节点 1
    int cur_node = lca;
    for (int j = MAX_LOG - 1; j >= 0; --j) {
        if (up[cur_node][j] != 0) {
            ll next_node[2] = {INF, INF};
            for (int cur = 0; cur < 2; ++cur) {
                if (cur_lca[cur] >= INF) continue;
                for (int nxt = 0; nxt < 2; ++nxt) {
                    if (trans[cur_node][j][cur][nxt] < INF) {
                        next_node[nxt] = min(next_node[nxt], cur_lca[cur] + trans[cur_node][j][cur][nxt]);
                    }
                }
            }
            cur_lca[0] = next_node[0];
            cur_lca[1] = next_node[1];
            cur_node = up[cur_node][j];
        }
    }

    ll ans = min(cur_lca[0], cur_lca[1]);
    return (ans >= INF ? -1 : ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m >> problem_type)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }

    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs1(1, 0);
    init_doubling();

    while (m--) {
        int a, x, b, y;
        cin >> a >> x >> b >> y;
        // 特判相邻且都不选
        if (up[a][0] == b && x == 0 && y == 0) {
            cout << -1 << "\n";
            continue;
        }
        if (up[b][0] == a && x == 0 && y == 0) {
            cout << -1 << "\n";
            continue;
        }

        cout << query(a, x, b, y) << "\n";
    }

    return 0;
}
