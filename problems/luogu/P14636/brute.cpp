/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-01 09:34
 * update_at: 2026-11-01 09:34
 */
// brute.cpp：枚举定价，以密度贪心与同一定价下的 0/1 背包比较，只用于小规模。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 25;
const ll MOD = 998244353;
ll n, budget;
ll value[MAXN], price[MAXN]; // 原价与当前枚举的清仓价
ll order_id[MAXN]; // 密度排序后的原编号
ll dp[2 * MAXN]; // 恰好花费若干元时的最大原价和，-1 为不可达

bool compare_item(ll first, ll second) {
    ll left = value[first] * price[second];
    ll right = value[second] * price[first];
    if (left != right) return left > right;
    if (value[first] != value[second]) return value[first] > value[second];
    return first < second;
}

// 完整照题目模拟，买不起二元糖果后仍继续考虑后面的糖果。
ll greedy_value() {
    for (ll i = 1; i <= n; i++) order_id[i] = i;
    sort(order_id + 1, order_id + n + 1, compare_item);
    ll money = budget, result = 0;
    for (ll i = 1; i <= n; i++) {
        ll id = order_id[i];
        if (money >= price[id]) {
            money -= price[id];
            result += value[id];
        }
    }
    return result;
}

// 每个糖果只能买一次，求这份定价下真正的最优值。
ll optimal_value() {
    fill(dp, dp + budget + 1, -1);
    dp[0] = 0;
    for (ll i = 1; i <= n; i++) {
        for (ll money = budget; money >= price[i]; money--) {
            if (dp[money - price[i]] >= 0) {
                dp[money] = max(dp[money], dp[money - price[i]] + value[i]);
            }
        }
    }
    return *max_element(dp, dp + budget + 1);
}

void solve() {
    cin >> n >> budget;
    for (ll i = 1; i <= n; i++) cin >> value[i];
    ll answer = 0;
    for (ll mask = 0; mask < (1LL << n); mask++) {
        for (ll i = 1; i <= n; i++) price[i] = 1 + ((mask >> (i - 1)) & 1);
        if (greedy_value() == optimal_value()) answer++;
    }
    cout << answer % MOD << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll control_id, tests;
    cin >> control_id >> tests;
    while (tests--) solve();
    return 0;
}
