/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 08:59
 * update_at: 2026-10-06 08:59
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 1005;

ll a[MAXN]; // 每只史莱姆过桥时间，升序排序

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n); // 升序：最快的在左，最慢的在右

    ll cost = 0;
    int tail = n - 1; // 当前未过桥的最慢者下标

    // 每轮送走最慢的两只，两种送法取小
    while (tail > 2) {
        // 送法一：最快往返接送 (a0,an)过、a0回、(a0,a_{n-1})过、a0回
        ll shuttle = 2 * a[0] + a[tail] + a[tail - 1];
        // 送法二：最快与次快结伴 (a0,a1)过、a0回、(a_{n-1},an)过、a1回
        ll relay   = a[0] + 2 * a[1] + a[tail];
        cost += min(shuttle, relay);
        tail -= 2; // 本轮消化两只最慢的
    }

    // 剩余3只以内直接收尾
    if (tail == 2)      cost += a[0] + a[1] + a[2]; // 三只：最快陪两次去程、回一次程
    else if (tail == 1) cost += a[1];               // 两只：按慢者计时
    else if (tail == 0) cost += a[0];               // 一只：自己提灯过

    cout << cost << "\n";
    return 0;
}
