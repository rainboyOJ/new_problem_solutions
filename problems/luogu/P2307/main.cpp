/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 11:30
 * update_at: 2026-08-05 11:30
 */
// 并查集：迷宫合法当且仅当 无环 且 所有出现过的房间连通（即是一棵树）。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int fa[MAXN];          // 并查集父节点
bool appear[MAXN];     // 该房间编号是否在本组数据中出现过

void init() {
    for (int i = 1; i <= 100000; i++) fa[i] = i;
    memset(appear, 0, sizeof(appear));
}

int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);   // 路径压缩
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();
    bool has_edge = false;    // 本组数据是否至少有一条边
    bool ok = true;           // 是否满足无环且连通

    int u, v;
    while (cin >> u >> v) {
        if (u == -1 && v == -1) break;   // 整个文件结束
        if (u == 0 && v == 0) {          // 一组数据结束
            // 有边时检查连通：找一个出现过的节点做基准根
            int root = -1;
            for (int i = 1; i <= 100000; i++) {
                if (appear[i]) {
                    root = find(i);
                    break;
                }
            }
            // 所有出现过的节点必须在同一个集合里
            if (root != -1) {
                for (int i = 1; i <= 100000; i++) {
                    if (appear[i] && find(i) != root) {
                        ok = false;
                        break;
                    }
                }
            }
            cout << (ok ? 1 : 0) << '\n';
            init();
            has_edge = false;
            ok = true;
            continue;
        }

        // 本组数据内的一条边
        has_edge = true;
        appear[u] = true;
        appear[v] = true;
        int ru = find(u), rv = find(v);
        if (ru == rv) ok = false;   // 两点已经连通：出现环
        else fa[ru] = rv;
    }

    return 0;
}
