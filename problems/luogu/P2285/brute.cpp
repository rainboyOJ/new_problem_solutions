/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 13:50
 * update_at: 2026-10-26 13:50
 */
// brute.cpp：小数据暴力解，用 01 序列递归枚举"这只鼹鼠打不打"，到叶子统一检查是否都赶得上。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 25;

ll n, m;
ll t[MAXM], x[MAXM], y[MAXM]; // 第 i 只鼹鼠的时刻与位置
int choose_[MAXM];            // choose_[i] = 1 表示去打第 i 只，0 表示放弃
ll best;

// 检查当前选出的鼹鼠序列是否可行：相邻两只之间的曼哈顿距离不超过时间差。
bool check() {
    ll last = -1;
    for (ll i = 1; i <= m; i++) {
        if (choose_[i] == 0) {
            continue;
        }
        if (last != -1) {
            ll td = t[i] - t[last];
            ll dist = llabs(x[i] - x[last]) + llabs(y[i] - y[last]);
            if (dist > td) {
                return false;
            }
        }
        last = i;
    }
    return true;
}

ll count_chosen() {
    ll cnt = 0;
    for (ll i = 1; i <= m; i++) {
        cnt += choose_[i];
    }
    return cnt;
}

// 第 dep 层决定第 dep 只鼹鼠打不打。
void dfs(int dep) {
    if (dep == m + 1) {
        if (check()) {
            ll cnt = count_chosen();
            if (cnt > best) {
                best = cnt;
            }
        }
        return;
    }
    choose_[dep] = 0;
    dfs(dep + 1);
    choose_[dep] = 1;
    dfs(dep + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (ll i = 1; i <= m; i++) {
        cin >> t[i] >> x[i] >> y[i];
    }

    best = 0;
    dfs(1);
    cout << best << '\n';
    return 0;
}
