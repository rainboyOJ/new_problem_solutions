/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 19:35
 * update_at: 2026-07-11 19:38
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXK = 16;

int k, m, n;
ll patch_x[MAXK], patch_t[MAXK];
ll enemy_x[MAXK];
ll candidate_x2[500];
int candidate_cnt;
bool reach[20][1 << MAXK];

bool is_enemy_position(ll x2) {
    for (int i = 1; i <= m; i++) {
        if (x2 == 2 * enemy_x[i]) {
            return true;
        }
    }
    return false;
}

ll nearest_enemy_dist2(int id) {
    ll best = (1LL << 60);
    for (int i = 1; i <= m; i++) {
        ll d = llabs(patch_x[id] - enemy_x[i]) * 2;
        if (best > d) best = d;
    }
    return best;
}

void add_candidate(ll x2) {
    if (is_enemy_position(x2)) return;
    for (int i = 0; i < candidate_cnt; i++) {
        if (candidate_x2[i] == x2) return;
    }
    candidate_x2[candidate_cnt++] = x2;
}

int cover_mask(ll x2) {
    int mask = 0;
    for (int i = 1; i <= k; i++) {
        ll d_john = llabs(x2 - 2 * patch_x[i]);
        ll d_enemy = nearest_enemy_dist2(i);
        if (d_john < d_enemy) {
            mask |= 1 << (i - 1);
        }
    }
    return mask;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> k >> m >> n;
    for (int i = 1; i <= k; i++) {
        cin >> patch_x[i] >> patch_t[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> enemy_x[i];
    }

    vector<ll> endpoints;
    for (int i = 1; i <= k; i++) {
        ll best = nearest_enemy_dist2(i) / 2;
        endpoints.push_back(patch_x[i] - best);
        endpoints.push_back(patch_x[i] + best);
        add_candidate(2 * patch_x[i]);
    }

    sort(endpoints.begin(), endpoints.end());
    endpoints.erase(unique(endpoints.begin(), endpoints.end()), endpoints.end());
    for (int i = 0; i + 1 < (int)endpoints.size(); i++) {
        if (endpoints[i] < endpoints[i + 1]) {
            add_candidate(endpoints[i] + endpoints[i + 1]);
        }
    }

    int full = 1 << k;
    reach[0][0] = true;
    for (int used = 0; used < n; used++) {
        for (int mask = 0; mask < full; mask++) {
            if (!reach[used][mask]) continue;
            for (int i = 0; i < candidate_cnt; i++) {
                int nxt = mask | cover_mask(candidate_x2[i]);
                reach[used + 1][nxt] = true;
            }
        }
    }

    ll ans = 0;
    for (int used = 0; used <= n; used++) {
        for (int mask = 0; mask < full; mask++) {
            if (!reach[used][mask]) continue;
            ll sum = 0;
            for (int i = 1; i <= k; i++) {
                if (mask & (1 << (i - 1))) {
                    sum += patch_t[i];
                }
            }
            if (ans < sum) ans = sum;
        }
    }

    cout << ans << '\n';

    return 0;
}
