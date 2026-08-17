/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:41
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
int price[MAXN];      // 第一天各商店的菜价
int next_price[MAXN]; // 第二天各商店的菜价

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> price[i];
    }

    // 两端商店只有一个邻居，取两项的平均值。
    next_price[1] = (price[1] + price[2]) / 2;
    next_price[n] = (price[n - 1] + price[n]) / 2;

    // 中间商店取自己与左右邻居三项的平均值。
    for (int i = 2; i <= n - 1; i++) {
        next_price[i] = (price[i - 1] + price[i] + price[i + 1]) / 3;
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << ' ';
        cout << next_price[i];
    }
    cout << '\n';

    return 0;
}