/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 23:50
 * update_at: 2026-08-28 23:50
 */
// brute.cpp：小数据暴力解，逐位枚举填数：每层递归给 b[dep] 选一个值 v ∈ [1, a[dep]]。
// 生成完整的 b[1..n] 后，在叶子节点检查"任意相邻两项不等"这个合法条件再计数。
// 只适合小数据（n <= 8，a_i <= 5），用于帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 15;

int n;
int a[MAXN];   // 输入序列
int b[MAXN];   // 当前填出的完整序列
ll ans;        // 好序列个数

// 检查完整 b[1..n] 是否是好序列：任意相邻两项不等
bool check() {
    for (int i = 1; i < n; i++) {
        if (b[i] == b[i + 1]) return false;
    }
    return true;
}

// 第 dep 层在给 b[dep] 选择一个值，选完后递归下一层
void dfs(int dep) {
    if (dep == n + 1) { // 一条完整序列已经生成
        if (check()) ans++;
        return;
    }
    for (int v = 1; v <= a[dep]; v++) {
        b[dep] = v;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    ans = 0;
    dfs(1);

    cout << ans << '\n';
    return 0;
}