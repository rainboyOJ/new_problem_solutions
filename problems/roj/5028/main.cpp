/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:19
 * update_at: 2026-10-08 22:22
 */
// 一本通 2026《【例4.12】阶乘和》：输入正整数 n，求 S = 1! + 2! + ... + n!。
// 数据范围（题面【提示】）：1 <= n <= 10。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n; // 输入的正整数 n，题面保证 1 <= n <= 10

// 递推求阶乘和：fac 始终保存当前项 i!，sum 累加 1!..i!，单重循环 O(n)。
// n = 10 时 10! = 3628800、S = 4037913，int 也装得下；
// 但按本仓库规范「题目数据默认 ll」，仍统一用 long long，越界输入也不会溢出。
void solve() {
    ll fac = 1; // fac：进入第 i 轮后乘上 i 即为 i!
    ll sum = 0; // sum：1! + 2! + ... + i!
    for (ll i = 1; i <= n; i++) {
        fac *= i;
        sum += fac;
    }
    cout << sum << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) {
        return 0; // 空输入时直接退出
    }
    solve();

    return 0;
}
