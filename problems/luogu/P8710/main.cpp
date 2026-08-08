#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXV = 20005;

int n, m;
int tot;
int fa[MAXV];
int tree_parent[MAXV];
int left_child[MAXV], right_child[MAXV];
long long add_tag[MAXV];
long long answer[MAXN];

void init_dsu(int n) {
    tot = n;
    for (int i = 1; i < MAXV; i++) {
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

// 有效合并时，新建一个虚点作为两个连通块的新根。
void merge_block(int x, int y) {
    int rx = find_root(x);
    int ry = find_root(y);

    if (rx == ry) {
        return;
    }

    ++tot;
    left_child[tot] = rx;
    right_child[tot] = ry;
    tree_parent[rx] = tot;
    tree_parent[ry] = tot;

    fa[rx] = tot;
    fa[ry] = tot;
    fa[tot] = tot;
}

void dfs(int u, long long sum) {
    sum += add_tag[u];

    if (u <= n) {
        answer[u] = sum;
        return;
    }

    if (left_child[u] != 0) {
        dfs(left_child[u], sum);
    }
    if (right_child[u] != 0) {
        dfs(right_child[u], sum);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    init_dsu(n);

    for (int i = 1; i <= m; i++) {
        int op, x, y;
        cin >> op >> x >> y;

        if (op == 1) {
            merge_block(x, y);
        } else {
            int root = find_root(x);
            add_tag[root] += y;
        }
    }

    for (int i = 1; i <= tot; i++) {
        if (tree_parent[i] == 0) {
            dfs(i, 0);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << answer[i];
    }
    cout << '\n';

    return 0;
}
