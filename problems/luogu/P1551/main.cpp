/**
 * P1551 亲戚
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;

int fa[MAXN], sz[MAXN];

int find(int x) {
    while (fa[x] != x) {
        fa[x] = fa[fa[x]]; // 路径压缩
        x = fa[x];
    }
    return x;
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (sz[x] < sz[y]) swap(x, y); // 按大小合并
    fa[y] = x;
    sz[x] += sz[y];
}

int main() {
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= n; ++i) fa[i] = i, sz[i] = 1;
    for (int i = 1; i <= m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        unite(a, b);
    }
    for (int i = 1; i <= p; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        puts(find(a) == find(b) ? "Yes" : "No");
    }
    return 0;
}
