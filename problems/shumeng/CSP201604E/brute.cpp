/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:30
 */
// brute.cpp：小数据暴力解，递归枚举每条边选或不选。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int MAXM = 3005;
const long long INF = (1LL << 60);

struct Edge {
    int u, v, w;
};

int n, m, p;
int is_user[MAXN];
int choose_edge[MAXM];
Edge edges[MAXM];
int parent[MAXN];
long long answer;

int find_root(int x) {
    if (parent[x] == x) {
        return x;
    }
    parent[x] = find_root(parent[x]);
    return parent[x];
}

bool check_connected() {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        if (!choose_edge[i]) {
            continue;
        }
        int x = find_root(edges[i].u);
        int y = find_root(edges[i].v);
        if (x != y) {
            parent[x] = y;
        }
    }

    int root = 0;
    for (int i = 1; i <= n; i++) {
        if (!is_user[i]) {
            continue;
        }
        if (root == 0) {
            root = find_root(i);
        } else if (root != find_root(i)) {
            return false;
        }
    }
    return true;
}

void dfs(int index, long long cost) {
    if (cost >= answer) {
        return;
    }
    if (index > m) {
        if (check_connected()) {
            answer = cost;
        }
        return;
    }

    choose_edge[index] = 0;
    dfs(index + 1, cost);
    choose_edge[index] = 1;
    dfs(index + 1, cost + edges[index].w);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;
    while (test_count--) {
        cin >> n >> m >> p;
        string users;
        cin >> users;
        for (int i = 1; i <= n; i++) {
            is_user[i] = users[i - 1] == '1';
        }
        for (int i = 1; i <= m; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }

        answer = INF;
        dfs(1, 0);
        cout << answer << '\n';
    }

    return 0;
}
