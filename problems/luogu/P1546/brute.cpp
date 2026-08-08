// brute.cpp：按定义枚举所有可能的生成树，只适合很小的数据。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAXM = 50;
const int INF = 1e9;

struct Edge {
    int u, v, w;
} edges[MAXM];

int n;
int edge_cnt;
int picked[MAXM];
int best_answer = INF;

int fa[MAXN];

void init_dsu() {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}

int find_root(int x) {
    if (fa[x] == x) {
        return x;
    }
    fa[x] = find_root(fa[x]);
    return fa[x];
}

void unite(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if (x != y) {
        fa[x] = y;
    }
}

bool check_tree(int picked_cnt) {
    if (picked_cnt != n - 1) {
        return false;
    }

    init_dsu();
    for (int i = 1; i <= picked_cnt; i++) {
        int id = picked[i];
        unite(edges[id].u, edges[id].v);
    }

    int root = find_root(1);
    for (int i = 2; i <= n; i++) {
        if (find_root(i) != root) {
            return false;
        }
    }
    return true;
}

void dfs(int pos, int picked_cnt, int sum) {
    if (picked_cnt > n - 1) {
        return;
    }
    if (sum >= best_answer) {
        return;
    }
    if (pos > edge_cnt) {
        if (check_tree(picked_cnt)) {
            best_answer = min(best_answer, sum);
        }
        return;
    }

    picked[picked_cnt + 1] = pos;
    dfs(pos + 1, picked_cnt + 1, sum + edges[pos].w);
    dfs(pos + 1, picked_cnt, sum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int w;
            cin >> w;
            if (j > i) {
                edges[++edge_cnt] = {i, j, w};
            }
        }
    }

    dfs(1, 0, 0);
    cout << best_answer << '\n';

    return 0;
}
