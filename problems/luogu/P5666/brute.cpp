/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:34
 * update_at: 2026-08-12 22:48
 */
// brute.cpp：小数据暴力解。对每条边断开，两侧连通块分别以断边端点为根，
// 用“沿最大子树方向下降”在 O(size) 内找重心并累加编号和。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n;
vector<int> g[MAXN];            // 邻接表存树
int edge_u[MAXN], edge_v[MAXN]; // 按输入顺序存每条边
bool in_comp[MAXN];             // 标记当前连通块内的节点
int fa[MAXN], sz[MAXN];         // 连通块内以根做 DFS 得到的父节点与子树大小

// 收集从 start 出发、不经过断边 (ban_u, ban_v) 的连通块。
void collect_component(int start, int ban_u, int ban_v) {
    memset(in_comp, 0, sizeof(in_comp));
    queue<int> q;
    q.push(start);
    in_comp[start] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if ((u == ban_u && v == ban_v) || (u == ban_v && v == ban_u)) {
                continue;
            }
            if (!in_comp[v]) {
                in_comp[v] = true;
                q.push(v);
            }
        }
    }
}

// 在当前连通块内以 root 为根做 DFS，求出 sz[] 与 fa[]。
void dfs_size(int root) {
    sz[root] = 1;
    for (int i = 0; i < (int)g[root].size(); i++) {
        int v = g[root][i];
        if (v == fa[root] || !in_comp[v]) {
            continue;
        }
        fa[v] = root;
        dfs_size(v);
        sz[root] += sz[v];
    }
}

// 求以 root 为根的连通块的重心编号和（沿最大子树方向下降，O(size)）。
int centroid_sum(int root) {
    int total = sz[root];
    int cur = root;
    int max_child = 0;

    // 不断进入“大小超过一半”的唯一子树方向；超过一半的子树至多一个，
    // 所以方向唯一，走到停就是重心。
    while (true) {
        max_child = 0;
        for (int i = 0; i < (int)g[cur].size(); i++) {
            int v = g[cur][i];
            if (in_comp[v] && fa[v] == cur && sz[v] > sz[max_child]) {
                max_child = v;
            }
        }
        if (max_child != 0 && sz[max_child] * 2 > total) {
            cur = max_child;
        } else {
            break;
        }
    }

    // cur 是重心；若最大子树恰好为一半，其根与 cur 是两个相邻重心，编号都要计入。
    int result = cur;
    if (max_child != 0 && sz[max_child] * 2 == total) {
        result += max_child;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            g[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            edge_u[i] = u;
            edge_v[i] = v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        long long answer = 0;
        for (int i = 1; i < n; i++) {
            int u = edge_u[i], v = edge_v[i];
            // u 一侧：以 u 为根的连通块。
            collect_component(u, u, v);
            fa[u] = 0;
            dfs_size(u);
            answer += centroid_sum(u);
            // v 一侧：以 v 为根的连通块。
            collect_component(v, u, v);
            fa[v] = 0;
            dfs_size(v);
            answer += centroid_sum(v);
        }
        cout << answer << '\n';
    }

    return 0;
}
