#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
const long long MOD = 1000000007LL;

struct Edge {
    int u, v, t;
};

int n, r_limit;
Edge edges[MAXN];

int dsu_parent[MAXN];
int dsu_size[MAXN];
int comp_id[MAXN];
int comp_weight[MAXN];
int comp_cnt;

vector<int> g[MAXN];
int color_part[MAXN];

int find_root(int x) {
    if (dsu_parent[x] == x) {
        return x;
    }
    dsu_parent[x] = find_root(dsu_parent[x]);
    return dsu_parent[x];
}

void unite(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a == b) {
        return;
    }
    if (dsu_size[a] < dsu_size[b]) {
        swap(a, b);
    }
    dsu_parent[b] = a;
    dsu_size[a] += dsu_size[b];
}

long long mod_pow(long long a, int e) {
    long long res = 1;
    while (e > 0) {
        if (e & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> r_limit;
    for (int i = 1; i <= n; i++) {
        dsu_parent[i] = i;
        dsu_size[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].t;
        if (edges[i].t == 2) {
            unite(edges[i].u, edges[i].v);
        }
    }

    for (int i = 1; i <= n; i++) {
        comp_id[i] = 0;
        comp_weight[i] = 0;
        g[i].clear();
        color_part[i] = -1;
    }

    for (int i = 1; i <= n; i++) {
        int root = find_root(i);
        if (comp_id[root] == 0) {
            comp_id[root] = ++comp_cnt;
        }
        int id = comp_id[root];
        comp_weight[id]++;
    }

    int zero_edge_cnt = 0;
    for (int i = 1; i < n; i++) {
        if (edges[i].t != 0) {
            continue;
        }
        int a = comp_id[find_root(edges[i].u)];
        int b = comp_id[find_root(edges[i].v)];
        // 在树上缩掉 t=2 后，不会出现 a == b 的情况；这里保守防一下。
        if (a == b) {
            cout << 0 << ' ' << 0 << '\n';
            return 0;
        }
        g[a].push_back(b);
        g[b].push_back(a);
        zero_edge_cnt++;
    }

    if (r_limit == 1 && zero_edge_cnt > 0) {
        cout << 0 << ' ' << 0 << '\n';
        return 0;
    }

    long long ways = 1;
    long long min_sum = 0;
    for (int i = 1; i <= comp_cnt; i++) {
        if (color_part[i] != -1) {
            continue;
        }

        long long part_sum[2] = {0, 0};
        int edge_in_component = 0;
        queue<int> q;
        q.push(i);
        color_part[i] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            part_sum[color_part[u]] += comp_weight[u];
            edge_in_component += (int)g[u].size();

            for (size_t j = 0; j < g[u].size(); j++) {
                int v = g[u][j];
                if (color_part[v] == -1) {
                    color_part[v] = color_part[u] ^ 1;
                    q.push(v);
                }
            }
        }

        if (edge_in_component == 0) {
            // 没有敌对边约束的独立点，直接放最小值 1 即可。
            ways = ways * r_limit % MOD;
            min_sum += part_sum[0];
        } else {
            int edge_cnt = edge_in_component / 2;
            ways = ways * r_limit % MOD;
            ways = ways * mod_pow(r_limit - 1, edge_cnt) % MOD;
            // 这个连通块一定是树，最优只需要用颜色 1 和 2，
            // 再把较小的一侧放颜色 2。
            min_sum += part_sum[0] + part_sum[1] + min(part_sum[0], part_sum[1]);
        }
    }

    cout << ways % MOD << ' ' << min_sum << '\n';
    return 0;
}
