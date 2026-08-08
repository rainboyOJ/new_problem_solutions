/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 11:44
 * update_at: 2026-07-19 11:44
 */
// main2.cpp：建朋友关系图 + 并查集数连通分量（教学版）
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
int parent[MAXN];
int sz[MAXN];
vector<int> enemies[MAXN]; // enemies[i]：i 的直接敌人列表

int find_root(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void unite(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a == b) {
        return;
    }
    if (sz[a] < sz[b]) {
        swap(a, b);
    }
    parent[b] = a;
    sz[a] += sz[b];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    for (int i = 1; i <= m; i++) {
        char op;
        int a, b;
        cin >> op >> a >> b;
        if (op == 'F') {
            // 朋友：图中直接连边
            unite(a, b);
        } else {
            // 敌人：先记下来，后面统一处理
            enemies[a].push_back(b);
            enemies[b].push_back(a);
        }
    }

    // 敌人的敌人是朋友：同一个人的所有敌人两两并到同一集合
    for (int person = 1; person <= n; person++) {
        int cnt = (int)enemies[person].size();
        if (cnt < 2) {
            continue;
        }
        int first = enemies[person][0];
        for (int j = 1; j < cnt; j++) {
            unite(first, enemies[person][j]);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (find_root(i) == i) {
            ans++;
        }
    }
    cout << ans << '\n';
    return 0;
}
