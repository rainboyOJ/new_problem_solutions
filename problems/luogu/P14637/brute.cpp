// brute.cpp：第 u 层枚举节点 u 的权值，到完整赋值后计算所有子树 mex。
// 只用于 n<=6 左右的小规模验证；数组与位集合按 n<10 设置。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
// 小数据 n<10，权值位集合和答案均能用 int 表示。
int n, m, parent[MAXN], value[MAXN], mask[MAXN], answer;

int calc_value() {
    for (int u = 1; u <= n; u++) mask[u] = 1 << value[u];
    // 题面保证 parent[u]<u，倒序合并即可得到每棵子树的权值集合。
    for (int u = n; u >= 2; u--) mask[parent[u]] |= mask[u];
    int result = 0;
    for (int u = 1; u <= n; u++) {
        int mex = 0;
        while (mask[u] & (1 << mex)) mex++;
        result += mex;
    }
    return result;
}

void dfs_assign(int u) {
    if (u == n + 1) {
        answer = max(answer, calc_value());
        return;
    }
    for (int x = 0; x < n; x++) {
        value[u] = x;
        dfs_assign(u + 1);
    }
}

void solve() {
    cin >> n >> m;
    for (int u = 2; u <= n; u++) cin >> parent[u];
    answer = 0;
    dfs_assign(1);
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    while (tests--) solve();
    return 0;
}
