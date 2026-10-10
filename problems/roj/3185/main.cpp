/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 秘密的牛奶运输：按 Kruskal 顺序累加“补全完全图”所需的最小新增边权
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 500005;

int parent[MAXN];
ll sz[MAXN]; // 只有根节点的 size 有意义

int find_root(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

struct Edge { // 树边：权值放首位便于排序
    ll w;
    int x;
    int y;
};

bool cmp(const Edge& a, const Edge& b) {
    if (a.w != b.w) {
        return a.w < b.w;
    }
    if (a.x != b.x) {
        return a.x < b.x; // 与 Python 元组排序的并列处理保持一致
    }
    return a.y < b.y;
}

int main() {
    int cases;
    if (scanf("%d", &cases) != 1) {
        return 0;
    }
    for (int tc = 0; tc < cases; tc++) {
        int n;
        scanf("%d", &n);
        vector<Edge> edges(n > 1 ? n - 1 : 0);
        for (int i = 0; i + 1 < n; i++) {
            int x, y;
            ll w;
            scanf("%d %d %lld", &x, &y, &w);
            edges[i].w = w;
            edges[i].x = x;
            edges[i].y = y;
        }
        sort(edges.begin(), edges.end(), cmp);

        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
        ll total = 0;
        for (int i = 0; i < (int)edges.size(); i++) {
            int rx = find_root(edges[i].x), ry = find_root(edges[i].y);
            // 这两块之间除这条树边外的点对，每条最小可行权值都是 w+1
            total += (sz[rx] * sz[ry] - 1) * (edges[i].w + 1);
            if (sz[rx] < sz[ry]) { // 按大小合并
                int t = rx;
                rx = ry;
                ry = t;
            }
            parent[ry] = rx;
            sz[rx] += sz[ry];
        }
        printf("%lld\n", total);
    }
    return 0;
}
