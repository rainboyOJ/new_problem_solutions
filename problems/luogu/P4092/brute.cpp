/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:59
 * update_at: 2026-08-12 22:59
 */
// brute.cpp：小数据暴力解，每次查询从节点沿父亲链向上爬，找最近的已标记祖先。
// 复杂度 O(n) 每次操作，只适合小数据，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, q;
int parent[MAXN];  // parent[u] 记录 u 的父亲（输入是 u -> v 的有向边）
bool marked[MAXN]; // marked[u] 记录 u 是否已被标记

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    // 读入 n-1 条有向边 u -> v，表示 u 是 v 的父亲。
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        parent[v] = u;
    }

    marked[1] = true; // 初始只有根 1 有标记

    while (q--) {
        char opt;
        int u;
        cin >> opt >> u;
        if (opt == 'C') {
            marked[u] = true; // 标记操作：直接置 true（重复标记没有额外效果）
        } else {
            // 询问：从 u 沿父亲链向上爬，第一个被标记的就是最近的标记祖先。
            int cur = u;
            while (!marked[cur])
                cur = parent[cur];
            cout << cur << '\n';
        }
    }

    return 0;
}
