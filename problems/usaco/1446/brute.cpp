/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:32
 * update_at: 2026-07-11 18:35
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

map<vector<ll>, ll> memo;

ll dfs_game(vector<ll> cakes) {
    if ((int)cakes.size() == 1) {
        return cakes[0];
    }

    if (memo.count(cakes) != 0) {
        return memo[cakes];
    }

    ll best;
    int len = cakes.size();

    if (len % 2 == 0) {
        // Bessie's turn：选择一对相邻蛋糕合并，最大化自己最后得到的蛋糕。
        best = -1;
        for (int i = 0; i + 1 < len; i++) {
            vector<ll> next_cakes;
            for (int j = 0; j < len; j++) {
                if (j == i) {
                    next_cakes.push_back(cakes[j] + cakes[j + 1]);
                    j++;
                } else {
                    next_cakes.push_back(cakes[j]);
                }
            }
            ll value = dfs_game(next_cakes);
            if (value > best) {
                best = value;
            }
        }
    } else {
        // Elsie's turn：拿走左端或右端，等价于最小化 Bessie 最后得到的蛋糕。
        best = (1LL << 62);

        vector<ll> left_removed;
        for (int i = 1; i < len; i++) {
            left_removed.push_back(cakes[i]);
        }
        best = min(best, dfs_game(left_removed));

        vector<ll> right_removed;
        for (int i = 0; i + 1 < len; i++) {
            right_removed.push_back(cakes[i]);
        }
        best = min(best, dfs_game(right_removed));
    }

    memo[cakes] = best;
    return best;
}

void solve_one_case() {
    int n;
    cin >> n;

    vector<ll> cakes;
    ll total = 0;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        cakes.push_back(x);
        total += x;
    }

    memo.clear();
    ll bessie = dfs_game(cakes);
    cout << bessie << ' ' << total - bessie << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_one_case();
    }

    return 0;
}
