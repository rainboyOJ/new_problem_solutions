/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:35
 * update_at: 2026-11-10 23:35
 */
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;

const int MAXN = 200005;

int fa[MAXN];
int dis[MAXN]; // dis[x] 表示 x 到其父节点 fa[x] 的距离（压缩后到根的距离）

// 带权并查集路径压缩
int find(int x) {
    if (fa[x] != x) {
        int root = find(fa[x]);
        dis[x] += dis[fa[x]];
        fa[x] = root;
    }
    return fa[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
        dis[i] = 0;
    }

    int min_cycle = n + 1;

    for (int i = 1; i <= n; ++i) {
        int to;
        cin >> to;

        int root_u = find(i);
        int root_v = find(to);

        if (root_u != root_v) {
            // 合并 i 所在集合到 to 所在集合
            fa[root_u] = to;
            dis[i] = 1; // i -> to 的边长为 1
        } else {
            // 在同一集合内发现有向环，环长为 dis[i] + dis[to] + 1
            min_cycle = min(min_cycle, dis[i] + dis[to] + 1);
        }
    }

    cout << min_cycle << "\n";

    return 0;
}
