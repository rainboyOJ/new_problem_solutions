/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:29
 * update_at: 2026-08-12 22:34
 */
// brute.cpp：小数据暴力解，路径操作沿父链一步一步爬，子树操作 DFS 枚举，
// 用来帮助理解题意并辅助对拍。只适合 n 很小的情况。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m, root;
long long mod;
long long a[MAXN];          // a[i] 表示节点 i 当前的权值（始终对 mod 取模）
int fa[MAXN];               // fa[i] 表示节点 i 的父亲
int depth[MAXN];            // depth[i] 表示节点 i 的深度
vector<int> g[MAXN];        // 邻接表存树

// 从根出发 BFS，求出每个节点的父亲和深度。
void build_parent() {
    queue<int> q;
    q.push(root);
    fa[root] = 0;
    depth[root] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (v == fa[u]) continue;
            fa[v] = u;
            depth[v] = depth[u] + 1;
            q.push(v);
        }
    }
}

// 路径加：让 x、y 中较深的一个先向上爬，直到两点相遇，
// 途中经过的每个点都加 z（沿父链爬，单次操作 O(深度)）。
void path_add(int x, int y, long long z) {
    while (x != y) {
        if (depth[x] < depth[y]) swap(x, y);
        a[x] = (a[x] + z) % mod;
        x = fa[x];
    }
    a[x] = (a[x] + z) % mod;
}

// 路径和：和路径加同样的爬法，把沿途经过的点的权值累加起来。
long long path_sum(int x, int y) {
    long long answer = 0;
    while (x != y) {
        if (depth[x] < depth[y]) swap(x, y);
        answer = (answer + a[x]) % mod;
        x = fa[x];
    }
    answer = (answer + a[x]) % mod;
    return answer;
}

// 子树加：DFS 枚举 u 子树内每个节点，逐个加 z。
void subtree_add(int u, int father, long long z) {
    a[u] = (a[u] + z) % mod;
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == father) continue;
        subtree_add(v, u, z);
    }
}

// 子树和：DFS 枚举 u 子树内每个节点，逐个累加。
long long subtree_sum(int u, int father) {
    long long answer = a[u];
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == father) continue;
        answer = (answer + subtree_sum(v, u)) % mod;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> root >> mod;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] %= mod;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    build_parent();

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            long long z;
            cin >> x >> y >> z;
            path_add(x, y, z % mod);
        } else if (op == 2) {
            int x, y;
            cin >> x >> y;
            cout << path_sum(x, y) << '\n';
        } else if (op == 3) {
            int x;
            long long z;
            cin >> x >> z;
            // 以 fa[x] 作为"不要进入的节点"，保证只枚举 x 的子树。
            subtree_add(x, fa[x], z % mod);
        } else {
            int x;
            cin >> x;
            cout << subtree_sum(x, fa[x]) << '\n';
        }
    }

    return 0;
}
