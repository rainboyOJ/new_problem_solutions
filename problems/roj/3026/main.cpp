/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:42
 * update_at: 2026-10-06 14:42
 */

// 糖果传递：环上均分糖果，最小化相邻传递总代价。
// 设 c[i] 为前 i 个人的 (a[i]-s) 前缀和，即第 i 人传给第 i+1 人的净流量
//（负号表示反向传），总代价 = Σ|c[i] - x|，x 取 c 的中位数时最小。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

typedef long long ll;

ll n;
ll a[MAXN]; // a[i]：第 i 个小朋友的初始糖果数
ll c[MAXN]; // c[i]：(a[i]-s) 的前缀和，即边上净流量关于 x_1 的偏移

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    ll sum = 0;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    ll s = sum / n; // 最终每人手里的糖果数（数据保证有解，即 n 整除 sum）

    // 前缀和：c[i] = c[i-1] + a[i] - s，第 n 项恰好回到 0（环闭合）
    for (ll i = 1; i <= n; i++) {
        c[i] = c[i - 1] + a[i] - s;
    }

    // 总代价 = Σ|c[i] + x_1|，数轴上选 -x_1 到各点距离和最小 -> 取中位数
    sort(c + 1, c + n + 1);
    ll mid = c[(n + 1) / 2]; // 中位数（n 为奇数取正中，偶数取任意一个皆最优）

    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        ans += llabs(c[i] - mid);
    }
    cout << ans << endl;

    return 0;
}
