/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 21:26
 * update_at: 2026-08-28 21:26
 */
// brute.cpp：小数据暴力解，使用 01 序列 / 选择序列递归枚举所有可能。
// choose[i] = 0/1 表示第 i 个数放入 A / B 集合，枚举完整的 choose[1..n]
// 后到叶子节点统一检查 OR(A) 是否等于 OR(B)。只适合 n <= 20 的小数据。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
int a[MAXN];
int choose[MAXN]; // choose[i] = 0 表示第 i 个数分给 A，1 表示分给 B
long long ans;

// 检查当前完整的 choose[1..n] 是否合法：OR(A) == OR(B)
bool check() {
    int orA = 0, orB = 0;
    for (int i = 1; i <= n; i++) {
        if (choose[i] == 0) orA |= a[i];
        else orB |= a[i];
    }
    return orA == orB;
}

// 枚举第 dep 个数的去向（选择序列），生成完整序列后在叶子统一检查
void dfs(int dep) {
    if (dep == n + 1) {
        if (check()) ans++; // 合法方案数加 1
        return;
    }
    for (int c = 0; c <= 1; c++) {
        choose[dep] = c;
        dfs(dep + 1);
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    dfs(1);
    cout << ans % 998244353 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
