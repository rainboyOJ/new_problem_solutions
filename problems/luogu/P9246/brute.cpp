/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 11:50
 * update_at: 2026-10-03 11:50
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 思路：直接实现题面。枚举砍掉哪一条边，把剩下的 n-2 条边用并查集连起来，
//       再逐对检查 (a_i, b_i) 是否都不连通；可行的边都试一遍，最后输出编号最大的。
//       完全不利用树的结构，只依赖“删一条边把图分成两半”的直观事实，正确性最直接。
// 规模：每条边都要重建一次并查集，复杂度 O(n^2 α(n))，只适合 n <= 3000 的小数据。
#include <iostream>
using namespace std;

const int MAXN = 3005;

int n, m;
int eu[MAXN], ev[MAXN]; // 树的 n-1 条边，从 1 号下标开始
int qa[MAXN], qb[MAXN]; // m 个待分离的数对
int fa[MAXN];           // 并查集

int find_root(int x) {
    while (fa[x] != x) {
        fa[x] = fa[fa[x]]; // 路径减半，防止链状数据退化
        x = fa[x];
    }
    return x;
}

// 砍掉编号为 cut 的边后，检查是不是每一对 (a_i, b_i) 都不连通。
bool check_after_cut(int cut) {
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= n - 1; i++) {
        if (i == cut) continue; // 这条边被砍掉了，不参与合并
        int ru = find_root(eu[i]);
        int rv = find_root(ev[i]);
        if (ru != rv) fa[ru] = rv;
    }
    for (int i = 1; i <= m; i++) {
        if (find_root(qa[i]) == find_root(qb[i])) return false; // 还有连通的点对
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n - 1; i++) {
        cin >> eu[i] >> ev[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> qa[i] >> qb[i];
    }

    int ans = -1;
    for (int cut = 1; cut <= n - 1; cut++) {
        if (check_after_cut(cut)) ans = cut; // 编号递增，最后留下的就是最大编号
    }

    cout << ans << '\n';
    return 0;
}
