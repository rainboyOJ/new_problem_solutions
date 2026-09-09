/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 23:40
 * update_at: 2026-08-28 23:40
 */
// brute.cpp：小数据暴力解，使用 01 序列 / 选择序列递归枚举所有可能。
// 每本书一个选择 choose[i]：0 不带走，1 带走。
// 只适合 n <= 15 的小数据（2^n 种方案），用于验证思路并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int n, m;
long long a[MAXN], b[MAXN]; // a[i] 带走收益，b[i] 不带走收益
int choose[MAXN];           // choose[i]：第 i 本书的选择，0 不带走，1 带走
long long ans;

// 检查当前完整 choose[1..n] 是否合法：带走的数量不超过 m
bool check() {
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (choose[i] == 1) cnt++;
    return cnt <= m;
}

// 统计当前完整 choose[1..n] 的总收益
long long calc_answer() {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        if (choose[i] == 1) sum += a[i];
        else sum += b[i];
    }
    return sum;
}

// 这一层枚举第 dep 本书的 01 选择：0 不带走，1 带走
void dfs(int dep) {
    if (dep == n + 1) {
        // 一条完整选择序列生成后，统一检查合法性并更新答案
        if (check()) {
            long long value = calc_answer();
            if (ans < value) ans = value;
        }
        return;
    }
    for (int i = 0; i <= 1; i++) {
        choose[dep] = i;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    ans = LLONG_MIN;
    dfs(1);
    cout << ans << '\n';
    return 0;
}
