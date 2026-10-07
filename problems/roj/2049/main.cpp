/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:29
 * update_at: 2026-10-06 10:29
 */
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const ll PARTS = 3;     // 原料种数：大麦、燕麦、小麦
const ll LIMIT = 100;   // 每种饲料份数的上界（题面：份数都小于 100）

ll target[PARTS];       // 目标配比
ll feed[PARTS][PARTS];  // 三种饲料的配比，feed[i][j] 表示第 i 种饲料的第 j 味原料

// 判断混合结果 mix 是否是目标配比的正整数倍；若是返回 k，否则返回 0
// axis 是目标配比中第一个非零下标，用于确定候选倍数 k
ll check_ratio(ll mix[], ll axis) {
    if (axis < 0) { // 目标配比全为 0：只有零混合符合
        return (mix[0] == 0 && mix[1] == 0 && mix[2] == 0) ? 1 : 0;
    }
    if (mix[axis] % target[axis] != 0) return 0;
    ll k = mix[axis] / target[axis];
    if (k <= 0) return 0;
    for (ll j = 0; j < PARTS; ++j) {
        if (mix[j] != k * target[j]) return 0;
    }
    return k;
}

// 按份数总和递增枚举，返回第一组可行解 (a, b, c, k)；无解返回 false
bool solve(ll ans[]) {
    ll axis = -1;
    for (ll j = 0; j < PARTS; ++j) {
        if (target[j] != 0) {
            axis = j;
            break;
        }
    }
    ll most = (LIMIT - 1) * PARTS; // 份数总和的上界 99+99+99
    for (ll total = 0; total <= most; ++total) {
        ll a_max = min(total, LIMIT - 1);
        for (ll a = 0; a <= a_max; ++a) {
            ll b_low = max(0LL, total - a - (LIMIT - 1)); // 保证 c 不超过 99
            ll b_high = min(total - a, LIMIT - 1);
            for (ll b = b_low; b <= b_high; ++b) {
                ll c = total - a - b;
                ll mix[PARTS];
                for (ll j = 0; j < PARTS; ++j) {
                    mix[j] = a * feed[0][j] + b * feed[1][j] + c * feed[2][j];
                }
                ll k = check_ratio(mix, axis);
                if (k > 0) {
                    ans[0] = a; ans[1] = b; ans[2] = c; ans[3] = k;
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    for (ll j = 0; j < PARTS; ++j) cin >> target[j];
    for (ll i = 0; i < PARTS; ++i)
        for (ll j = 0; j < PARTS; ++j)
            cin >> feed[i][j];
    ll ans[4];
    if (solve(ans)) {
        cout << ans[0] << " " << ans[1] << " " << ans[2] << " " << ans[3] << "\n";
    } else {
        cout << "NONE\n";
    }
    return 0;
}
