/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 13:50
 * update_at: 2026-10-26 13:50
 */
// main.cpp：把每只鼹鼠看成一个事件，dp[i] 表示最后打死第 i 只时的最大数目，O(m^2) 转移。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 10005;

struct Mole {
    ll t; // 出现时刻
    ll x; // 行
    ll y; // 列
};

ll n, m;
Mole mole[MAXM]; // 输入的事件序列，按时间不降给出
ll dp[MAXM];     // dp[i]：以第 i 只鼹鼠作为最后一只时，最多能打死的数目

// 从第 j 只赶到第 i 只需要的时间：曼哈顿距离。机器人在 td 个时刻内可以走 td 格。
bool reachable(int j, int i) {
    ll td = mole[i].t - mole[j].t;
    ll dist = llabs(mole[i].x - mole[j].x) + llabs(mole[i].y - mole[j].y);
    return dist <= td;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (ll i = 1; i <= m; i++) {
        cin >> mole[i].t >> mole[i].x >> mole[i].y;
    }

    ll ans = 1;
    for (ll i = 1; i <= m; i++) {
        // 初始位置可以自由选择，所以每只鼹鼠都能被当作第一只。
        dp[i] = 1;
        for (ll j = 1; j < i; j++) {
            if (reachable(j, i) && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > ans) {
            ans = dp[i];
        }
    }

    cout << ans << '\n';
    return 0;
}
