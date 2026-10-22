/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 20:20
 * update_at: 2026-10-21 20:20
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 01 序列枚举：每层递归决定「第 dep 条边选 / 不选」，生成完整 choose[] 后，
// 在叶子处用并查集检查选中的边是否构成生成树（恰好 n-1 条且无环即连通无环），
// 统计所有生成树权值，输出「严格大于 MST 权值」的最小者。
// 与 main.cpp 的 Kruskal + 倍增换边完全不共享实现，因此适合独立验证。
// 生成树数量最多 C(28,7) 级别，只适合 n <= 8 的对拍数据。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 12;
const int maxm = 40;

int n, m;
int eu[maxm], ev[maxm], ew[maxm]; // 第 i 条边的两端点与权值
int choose[maxm];                 // choose[i]：1 表示选第 i 条边
ll best, second;                  // 最小生成树权值、严格次小生成树权值
ll mst_cnt;                       // 生成树计数（调试用，确认至少存在两棵不同权值）

int fa[maxn];                     // 叶子检查用的并查集

// 检查当前 choose[] 是否构成生成树；是则更新 best / second
void check() {
    for (int i = 1; i <= n; ++i) fa[i] = i;
    int cnt = 0;
    ll sum = 0;
    for (int i = 1; i <= m; ++i) {
        if (!choose[i]) continue;
        // 找两端点的根（数据极小，不压缩也无所谓）
        int ru = eu[i], rv = ev[i];
        while (fa[ru] != ru) ru = fa[ru];
        while (fa[rv] != rv) rv = fa[rv];
        if (ru == rv) return;     // 有环，不是树
        fa[ru] = rv;
        cnt++;
        sum += ew[i];
    }
    if (cnt != n - 1) return;     // 边数不对（不连通或自环浪费）
    mst_cnt++;
    if (sum < best) { second = best; best = sum; }
    else if (sum > best && sum < second) second = sum;  // 严格大于才参与次小
}

// 这一层在决定第 dep 条边选不选
void dfs_choose(int dep) {
    if (dep == m + 1) {           // 完整方案已生成
        check();
        return;
    }
    choose[dep] = 0;
    dfs_choose(dep + 1);
    choose[dep] = 1;
    dfs_choose(dep + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) cin >> eu[i] >> ev[i] >> ew[i];

    best = second = LLONG_MAX;
    mst_cnt = 0;
    dfs_choose(1);

    // second 仍为 LLONG_MAX 说明不存在严格次小生成树；本题数据保证存在
    if (second == LLONG_MAX)
        cout << -1 << endl;
    else
        cout << second << endl;
    return 0;
}
