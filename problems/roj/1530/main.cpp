/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:35
 * update_at: 2026-10-06 00:35
 */
#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int fa[MAXN];       // 并查集父节点
int deg[MAXN];      // 每个点的度数
int odd[MAXN];      // odd[root] 表示该连通块中奇度点的个数
bool has_edge[MAXN]; // 标记该点是否在某个含边连通块中出现过

// 并查集查找
int find_fa(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find_fa(fa[x]);
}

// 并查集合并
void unite(int x, int y) {
    int fx = find_fa(x);
    int fy = find_fa(y);
    if (fx != fy) fa[fx] = fy;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    // 多组数据，按输入流直到结束
    while (cin >> n >> m) {
        // 初始化
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
            deg[i] = 0;
            odd[i] = 0;
            has_edge[i] = false;
        }

        for (int i = 1; i <= m; i++) {
            int a, b;
            cin >> a >> b;
            deg[a]++;
            deg[b]++;
            unite(a, b);
        }

        // 统计每个含边连通块的奇度点数量
        for (int i = 1; i <= n; i++) {
            if (deg[i] == 0) continue; // 忽略孤立点
            int root = find_fa(i);
            has_edge[root] = true;
            if (deg[i] % 2 == 1) odd[root]++;
        }

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (!has_edge[i]) continue;
            if (odd[i] == 0) ans += 1;
            else ans += odd[i] / 2;
        }

        cout << ans << "\n";
    }

    return 0;
}
