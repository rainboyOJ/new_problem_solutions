/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 09:55
 * update_at: 2026-11-10 12:10
 */
// MTREECOL - Color a tree
// 贪心：每次挑选等效权值（平均值）最大的非根块，并入其父节点所在的块；
// 贡献法：块 u 接在父块 f 后面时，u 内所有点整体延后 siz[f] 个时刻，代价增量为 siz[f] * w[u]。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1005;

int n, root;
ll  w[MAXN];    // 连通块当前的总点权和
int siz[MAXN];  // 连通块当前包含的点数
int fa[MAXN];   // 原树上每个点的父节点
int p[MAXN];    // 普通并查集：定位每个点所属的连通块代表元

int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> root && (n || root)) {
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            cin >> w[i];
            ans += w[i]; // 初始基准代价：假定所有点都在第 1 个时刻染色
            siz[i] = 1;
            p[i] = i;
        }

        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            fa[v] = u;
        }

        // 不断将当前平均权值最大的非根块并入其父块，共合并 n - 1 次
        for (int step = 1; step < n; step++) {
            int u = -1;
            for (int i = 1; i <= n; i++) {
                if (i == root || find(i) != i) continue;
                // 十字相乘比较平均值：w[i]/siz[i] > w[u]/siz[u]
                if (u == -1 || w[i] * siz[u] > w[u] * siz[i]) {
                    u = i;
                }
            }

            int f = find(fa[u]);
            // 物理意义：块 u 紧随块 f 染色，u 内所有点被延后 siz[f] 个时刻
            ans += (ll)siz[f] * w[u];

            // 并查集合并
            p[u] = f;
            siz[f] += siz[u];
            w[f] += w[u];
        }

        cout << ans << "\n";
    }

    return 0;
}
