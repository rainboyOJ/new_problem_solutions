/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 22:48
 * update_at: 2026-11-10 22:48
 */
#include <iostream>

using namespace std;

// 线性组合结构体：表示 k * a + b * y
struct Linear {
    int a;
    int y;

    Linear operator+(const Linear& other) const {
        return {a + other.a, y + other.y};
    }
};

const int MAXN = 30;
Linear u[MAXN]; // u[i]: 第 i 站上车人数的多项式系数
Linear s[MAXN]; // s[i]: 第 i 站开出时车上人数的多项式系数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, n, m, x;
    if (!(cin >> a >> n >> m >> x)) return 0;

    // 特殊情况：如果求前两站
    if (x == 1 || x == 2) {
        cout << a << "\n";
        return 0;
    }

    // 第 1 站和第 2 站的初始化
    // 设第 2 站上车人数为未知数 y
    u[1] = {1, 0};
    s[1] = {1, 0};

    u[2] = {0, 1};
    s[2] = {1, 0}; // 第 2 站上下车人数相同，开出时车上人数仍为 a

    // 递推计算第 3 站到第 n-1 站
    for (int i = 3; i <= n - 1; ++i) {
        // 第 i 站上车人数等于前两站上车人数之和
        u[i] = u[i - 1] + u[i - 2];
        // 第 i 站开出时的人数 = 上一站人数 + 本站净增人数(u[i] - u[i-1] = u[i-2])
        s[i] = s[i - 1] + u[i - 2];
    }

    // 由第 n 站全员下车，得到第 n-1 站开出时车上人数为 m
    // 即 s[n - 1].a * a + s[n - 1].y * y = m
    int y = 0;
    if (s[n - 1].y != 0) {
        y = (m - s[n - 1].a * a) / s[n - 1].y;
    }

    // 计算第 x 站开出时的人数
    int ans = s[x].a * a + s[x].y * y;
    cout << ans << "\n";

    return 0;
}
