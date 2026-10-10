/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int INF = 1000000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll length;
    int min_jump, max_jump, stone_count;
    cin >> length >> min_jump >> max_jump >> stone_count;
    vector<ll> stones(stone_count);
    for (int i = 0; i < stone_count; i++) cin >> stones[i];
    sort(stones.begin(), stones.end());

    // S == T：每次跳固定距离，必踩所有 S 的倍数点
    if (min_jump == max_jump) {
        int ans = 0;
        for (int i = 0; i < stone_count; i++)
            if (stones[i] % min_jump == 0) ans++;
        cout << ans << "\n";
        return 0;
    }

    // 截断：每段间距取 min(gap, cap)
    int period = max_jump - min_jump;
    int lead = (2 * max_jump - 1 + period - 1) / period;
    int cap = 1 + max_jump + max_jump * lead;

    vector<ll> crossed;
    ll prev_orig = 0, new_pos = 0;
    for (int i = 0; i <= stone_count; i++) {
        ll pos = (i < stone_count) ? stones[i] : length;
        new_pos += min(pos - prev_orig, (ll)cap);
        crossed.push_back(new_pos);
        prev_orig = pos;
    }
    ll bridge = crossed.back();
    set<ll> has_stone(crossed.begin(), crossed.end() - 1);

    vector<int> dp(bridge + 1, INF);
    dp[0] = 0;
    for (ll i = 1; i <= bridge; i++) {
        if (i < min_jump) continue;
        int best = INF;
        ll lo = max(0LL, i - max_jump);
        ll hi = i - min_jump;
        for (ll j = lo; j <= hi; j++)
            if (dp[j] < best) best = dp[j];
        if (best < INF)
            dp[i] = best + (has_stone.count(i) ? 1 : 0);
    }
    int ans = INF;
    ll lo = max(0LL, bridge - max_jump);
    for (ll i = lo; i <= bridge; i++)
        if (dp[i] < ans) ans = dp[i];
    cout << ans << "\n";
    return 0;
}
