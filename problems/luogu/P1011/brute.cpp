/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 22:48
 * update_at: 2026-11-10 22:48
 */
// brute.cpp：暴力枚举第 2 站上车人数 y，直接模拟整趟列车
#include <iostream>
#include <vector>

using namespace std;

// 模拟给定第 2 站上车人数 y 后的过程
// 若模拟到第 n-1 站车上人数恰好为 m，则返回第 x 站人数，否则返回 -1
int simulate(int a, int n, int m, int x, int y) {
    vector<int> u(n + 1, 0); // 每站上车人数
    vector<int> s(n + 1, 0); // 每站开出时人数

    u[1] = a;
    s[1] = a;

    u[2] = y;
    s[2] = a; // 第 2 站下车也是 y，净增 0

    for (int i = 3; i <= n - 1; ++i) {
        u[i] = u[i - 1] + u[i - 2];
        int down = u[i - 1]; // 下车人数
        s[i] = s[i - 1] + u[i] - down;
    }

    if (s[n - 1] == m) {
        return s[x];
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, n, m, x;
    if (!(cin >> a >> n >> m >> x)) return 0;

    if (x == 1 || x == 2) {
        cout << a << "\n";
        return 0;
    }

    // 枚举 y，由于人数单调递增且非负，y 最大不超过 m
    for (int y = 0; y <= m; ++y) {
        int ans = simulate(a, n, m, x, y);
        if (ans != -1) {
            cout << ans << "\n";
            return 0;
        }
    }

    return 0;
}
