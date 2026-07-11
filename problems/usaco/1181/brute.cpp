/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:58
 * update_at: 2026-07-11 18:02
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 25;
const ll INF = (1LL << 60);

int n;
ll h[MAXN], tmp_h[MAXN];

ll calc_cost(ll final_hunger) {
    for (int i = 1; i <= n; i++) {
        tmp_h[i] = h[i];
    }

    ll cost = 0;
    for (int i = 1; i <= n - 1; i++) {
        if (tmp_h[i] < final_hunger) {
            return INF;
        }

        ll need = tmp_h[i] - final_hunger;
        tmp_h[i] -= need;
        tmp_h[i + 1] -= need;
        cost += need * 2;
    }

    if (tmp_h[n] != final_hunger) {
        return INF;
    }
    return cost;
}

ll work_one_case() {
    cin >> n;

    ll min_h = INF;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        if (h[i] < min_h) {
            min_h = h[i];
        }
    }

    ll ans = INF;
    // 枚举最终共同饥饿度，只适合小数据。
    for (ll final_hunger = 0; final_hunger <= min_h; final_hunger++) {
        ll cost = calc_cost(final_hunger);
        if (cost < ans) {
            ans = cost;
        }
    }

    if (ans == INF) {
        return -1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cout << work_one_case() << '\n';
    }

    return 0;
}
