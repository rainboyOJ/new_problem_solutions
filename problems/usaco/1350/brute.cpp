/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:53
 * update_at: 2026-07-11 18:56
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 4000000000000000000LL;

int n;
ll m, k;
vector<ll> cows;    // 小数据下展开后的所有奶牛重量
deque<ll> towers;   // 每座塔当前最上方奶牛的重量

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        ll w, a;
        cin >> w >> a;
        for (ll j = 1; j <= a; j++) {
            cows.push_back(w);
        }
    }

    // 朴素做法：逐头处理奶牛，只适合总奶牛数较小的测试。
    sort(cows.begin(), cows.end(), greater<ll>());

    ll tower_cnt = min(m, (ll)cows.size());
    for (ll i = 1; i <= tower_cnt; i++) {
        towers.push_back(INF);
    }

    ll ans = 0;
    for (int i = 0; i < (int)cows.size(); i++) {
        ll w = cows[i];
        if (!towers.empty() && w + k <= towers.front()) {
            towers.pop_front();
            towers.push_back(w);
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}
