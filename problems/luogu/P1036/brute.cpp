/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:19
 * update_at: 2026-08-13 13:21
 */
// brute.cpp：小数据暴力解，使用 01 序列 / 选择序列递归枚举所有可能。
/* 每层递归决定第 i 个数选/不选，叶子节点统一检查选了 k 个且和为素数。 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, k;
int a[MAXN];      // 输入数组
int choose[MAXN]; // choose[i] = 1 表示选了第 i 个数
int ans;

// 判断 x 是否为素数：只需试除到 sqrt(x)
bool is_prime(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

// 检查当前完整 choose[1..n]：选了恰好 k 个且和为素数
void check() {
    int cnt = 0, sum = 0;
    for (int i = 1; i <= n; i++) {
        if (choose[i]) {
            cnt++;
            sum += a[i];
        }
    }
    if (cnt == k && is_prime(sum)) ans++;
}

// dfs(dep)：正在决定第 dep 个数的选择（0 不选，1 选）
void dfs(int dep) {
    if (dep == n + 1) {
        check(); // 一条完整 01 序列生成完毕，在叶子节点统一检查
        return;
    }

    // 这一层枚举第 dep 个数的 01 选择
    for (int x = 0; x <= 1; x++) {
        choose[dep] = x;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    dfs(1); // 从第 1 个数开始做选择
    cout << ans << "\n";
    return 0;
}
