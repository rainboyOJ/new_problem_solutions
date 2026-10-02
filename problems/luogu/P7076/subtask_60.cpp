/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:31
 * update_at: 2026-10-01 22:31
 */
// subtask_60.cpp：60% 数据 k ≤ 30，用公式 2^free_cnt - n 直接算答案。
// 核心思路：统计"禁止位"（未买饲料对应的位），自由位数 = k - 禁止位数。
// 因为 k ≤ 30，free_cnt ≤ 30，2^30 远小于 ull 上限，无需溢出处理。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int MAXM = 1000005;

ll m, c, k;
ll n;
int rule_p[MAXM];
int rule_q[MAXM];
ull zoo_mask;
ull bad_mask;
unordered_set<int> bought_feed;

bool has_bit(ull x, int p) {
    return (x >> p) & 1ULL;
}

// 读入动物编号，合并为位掩码。
void read_animals() {
    zoo_mask = 0;
    for (ll i = 0; i < n; i++) {
        ull x;
        cin >> x;
        zoo_mask |= x;
    }
}

// 读入规则，标记已购买的饲料。
void read_rules() {
    bought_feed.clear();
    for (ll i = 1; i <= m; i++) {
        cin >> rule_p[i] >> rule_q[i];
        if (has_bit(zoo_mask, rule_p[i])) {
            bought_feed.insert(rule_q[i]);
        }
    }
}

// 构建禁止位掩码。
void build_bad_mask() {
    bad_mask = 0;
    for (ll i = 1; i <= m; i++) {
        if (bought_feed.find(rule_q[i]) == bought_feed.end()) {
            bad_mask |= (1ULL << rule_p[i]);
        }
    }
}

void solve() {
    read_animals();
    read_rules();
    build_bad_mask();

    int bad_cnt = __builtin_popcountll(bad_mask);
    int free_cnt = (int)k - bad_cnt;

    // k ≤ 30 保证 free_cnt ≤ 30，1ULL << 30 不会溢出。
    ull total = 1ULL << free_cnt;
    ull ans = total - n;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> c >> k;
    solve();

    return 0;
}
