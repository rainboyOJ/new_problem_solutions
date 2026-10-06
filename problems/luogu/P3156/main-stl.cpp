/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 23:39
 * update_at: 2026-10-06 23:39
 */

// main-stl.cpp：STL 写法，用 vector 保存学号；vector 的长度由输入的 n 决定，
// 正是“长度可以变的数组”这个教学点。查询直接用下标 a[x] 读出答案。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    // n、m 最大到 2e6 / 1e5，用快速 IO（关同步 + 解绑 cin/cout）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    // vector 的长度在运行时才由 n 决定：开 n+1 个格子，下标 1..n 对应第 1..n 个进入教室的同学
    vector<int> a(n + 1); // 学号在 1..1e9，用 int 存足够
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 每次询问第 x 个进入教室的同学，题目下标从 1 开始，直接读 a[x]
    for (ll i = 1; i <= m; i++) {
        ll x;
        cin >> x;
        cout << a[x] << '\n';
    }

    return 0;
}
