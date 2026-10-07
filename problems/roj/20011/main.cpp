/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 02:04
 * update_at: 2026-10-06 02:04
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXS = 8;    // 菜品数最多 8
const int MAXM = 105;  // 无关系厨师最多 100
const int MAXSTATE = 6561 * 2 + 5;  // 每道菜 3 种有效状态（0/1/≥2），状态数 ≤ 3^8

typedef long long ll;

ll s, n, m;
ll rel_wage;                       // 亲戚工资总和，无条件照付
ll wage[MAXM];                     // wage[i] = 第 i 名零工的工资
ll mask_free[MAXM];                // mask_free[i] = 第 i 名零工会做的菜的 bitmask
ll one, two;                       // one/two 第 d 位 = 菜 d+1 覆盖数恰为 1 / 已满 2
ll dp[MAXSTATE];                   // dp[(one<<s)|two] = 达到该覆盖状态的最小零工工资
pair<ll, ll> states[MAXSTATE];     // 已经达过的覆盖状态列表，避免每轮清空整个 dp 数组
ll state_cnt;                      // states 中的状态个数
ll old_cost[MAXSTATE];             // 每轮开始时旧状态的 dp 快照，防止同轮改进值被重复当源用

// 把一行「工资 菜1 菜2 ...」解析出来，返回会做菜的 bitmask（第 d 位 = 会做菜 d+1）。
// 题面每行先给工资，后面直接跟菜品编号，菜品个数由行内数字个数决定。
ll cook_mask(ll &w) {
    string line;
    getline(cin, line);
    stringstream ss(line);
    ss >> w;
    ll res = 0, dish;
    while (ss >> dish) res |= 1LL << (dish - 1);
    return res;
}

// 读取全部厨师：亲戚只统计工资和覆盖数，零工记录工资和菜品掩码
void read_input() {
    string first_line;
    getline(cin, first_line);
    stringstream ss(first_line);
    ss >> s >> n >> m;

    ll covered[MAXS];  // covered[d] = 亲戚里会做菜 d+1 的人数（封顶前）
    for (ll d = 0; d < s; d++) covered[d] = 0;

    rel_wage = 0;
    for (ll i = 1; i <= n; i++) {
        ll w, mk = cook_mask(w);
        rel_wage += w;  // 亲戚必须保留，工资先付出
        for (ll d = 0; d < s; d++) {
            if (mk & (1LL << d)) covered[d]++;  // 统计亲戚覆盖数
        }
    }
    // 覆盖数超过 2 与恰好 2 等价，封顶后生成初始状态
    one = 0;
    two = 0;
    for (ll d = 0; d < s; d++) {
        if (covered[d] == 1) one |= 1LL << d;
        if (covered[d] >= 2) two |= 1LL << d;
    }

    for (ll i = 1; i <= m; i++) {
        mask_free[i] = cook_mask(wage[i]);
    }
}

// 比较两个覆盖状态哪个更接近满员（two 位数多者优先，其次 one 位数少者优先）。
// 0/1 背包式 DP 要求本轮零工只从旧状态转移，这里按可比较排序消除后效性。
bool state_cmp(pair<ll, ll> a, pair<ll, ll> b) {
    if (a.second != b.second) return a.second > b.second;
    return a.first < b.first;
}

void solve() {
    // 零工按工资升序排序：先处理便宜的，转移单调向更满状态推进
    // （选择排序，简单直观）
    for (ll i = 1; i <= m; i++) {
        ll best = i;
        for (ll j = i + 1; j <= m; j++) {
            if (wage[j] < wage[best]) best = j;
        }
        swap(wage[i], wage[best]);
        swap(mask_free[i], mask_free[best]);
    }

    ll all_two = (1LL << s) - 1;  // 全部菜都满员的目标状态
    for (ll st = 0; st < MAXSTATE; st++) dp[st] = -1;  // -1 表示未达

    // 初始状态：由亲戚的覆盖情况给出，零工工资为 0
    ll init_key = (one << s) | two;
    dp[init_key] = 0;
    state_cnt = 1;
    states[1] = make_pair(one, two);

    // 逐名零工做 0/1 背包式转移：每个旧状态可以选择不雇（保持）或雇（向更满状态转移）
    for (ll i = 1; i <= m; i++) {
        // 0/1 背包：本轮只能从「处理这名零工之前」的状态转移。
        // 先快照旧状态的 dp 值，否则同轮里刚被刷小的 dp 值会再被用一次，
        // 相当于同一名零工被雇两次。
        ll before_cnt = state_cnt;
        for (ll k = 1; k <= before_cnt; k++) {
            old_cost[k] = dp[(states[k].first << s) | states[k].second];
        }
        for (ll k = 1; k <= before_cnt; k++) {
            ll a = states[k].first;   // 原本恰好一人的菜
            ll b = states[k].second;  // 已满员的菜
            ll cost = old_cost[k];

            ll mask = mask_free[i];
            ll new_two = b | (a & mask);         // 原本一人、被他补一刀的菜凑满两名
            ll new_one = (a | mask) & ~new_two;  // 剩下的差一人菜
            ll ncost = cost + wage[i];

            ll nkey = (new_one << s) | new_two;
            if (dp[nkey] == -1 || dp[nkey] > ncost) {
                if (dp[nkey] == -1) {
                    // 新状态先登记，再更新值
                    state_cnt++;
                    states[state_cnt] = make_pair(new_one, new_two);
                }
                dp[nkey] = ncost;
            }
        }
    }

    // 在所有满员状态里取最小工资（理论上满员状态唯一，取 min 更稳妥）
    ll ans = -1;
    for (ll st = 0; st < MAXSTATE; st++) {
        if (dp[st] == -1) continue;
        ll t = st & ((1LL << s) - 1);
        if (t != all_two) continue;
        if (ans == -1 || dp[st] < ans) ans = dp[st];
    }
    cout << rel_wage + ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
