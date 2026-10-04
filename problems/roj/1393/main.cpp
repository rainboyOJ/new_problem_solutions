/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:33
 * update_at: 2026-10-05 00:33
 */

// 解法：必选边先全部累加费用并并入并查集（相当于缩点），
// 剩下的任务就是把若干连通块用可选边连成最小生成树，
// 直接在同一套并查集上对可选边按费用跑 Kruskal 即可。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 2005;
const int MAXM = 10005;

int n, m;
int father[MAXN]; // 并查集父指针，下标 1..n

struct Edge {
    ll u;
    ll v;
    ll w;
};

Edge opt[MAXM]; // 只保存可选边 (u, v, w)

// 找 x 的代表元，顺手路径压缩
int find(int x) {
    int root = x;
    while (father[root] != root) root = father[root];
    while (father[x] != root) { // 第二遍把路径上的点全部挂到 root
        int t = father[x];
        father[x] = root;
        x = t;
    }
    return root;
}

// 比较两条可选边，费用小的排前面
bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) father[i] = i; // 并查集初始化，每个点自成一块

    ll total = 0; // 答案：必选边费用 + 被选中的可选边费用
    int cnt = 0;  // 可选边的条数

    // 第一阶段：必选边没有自由度，费用直接累加，并把两端合并成一个连通块
    for (int i = 1; i <= m; i++) {
        int p, u, v;
        ll w;
        cin >> p >> u >> v >> w;
        if (p == 1) {
            total += w; // 同一对 u,v 的多条必选边全部要选，费用累加
            int ru = find(u), rv = find(v);
            if (ru != rv) father[ru] = rv;
        } else {
            cnt++;
            opt[cnt].u = u;
            opt[cnt].v = v;
            opt[cnt].w = w;
        }
    }

    // 第二阶段：每个并查集集合看成一个缩点，对可选边按费用做 Kruskal
    sort(opt + 1, opt + cnt + 1, cmp_edge);
    for (int i = 1; i <= cnt; i++) {
        int ru = find(opt[i].u), rv = find(opt[i].v);
        if (ru != rv) { // 不在一个连通块内，选这条边最划算
            total += opt[i].w;
            father[ru] = rv;
        }
    }

    cout << total << endl;
    return 0;
}
