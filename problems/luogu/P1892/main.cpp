/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 11:44
 * update_at: 2026-07-19 11:44
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
int parent[MAXN * 2]; // x: 真人 x；x+n: x 的对立侧
int sz[MAXN * 2];

int find_root(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

// 按秩（按大小）合并
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
    for (int i = 1; i <= 2 * n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    for (int i = 1; i <= m; i++) {
        char op;
        int a, b;
        cin >> op >> a >> b;
        if (op == 'F') {
            // 朋友：只合并真人
            unite(a, b);
        } else {
            // 敌人：a 与 b 的对立侧同组，b 与 a 的对立侧同组
            unite(a, b + n);
            unite(b, a + n);
        }
    }

    // 统计 1..n 的连通分量个数
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (find_root(i) == i) {
            ans++;
        }
    }
    cout << ans << '\n';
    return 0;
}
