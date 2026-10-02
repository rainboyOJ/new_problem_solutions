/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:31
 * update_at: 2026-10-01 22:31
 */
// main.cpp：满分做法，统计"禁止位"后用公式 2^free_cnt - n 得到答案。
// 核心思路：当前动物园已有动物的位掩码决定哪些规则的饲料已买，
// 未买饲料对应的位就是"禁止位"，新动物这些位必须为 0。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int MAXM = 1000005;

ll m, c, k;          // 要求数、饲料种数、二进制位数
ull n;               // 动物数量（需要无符号做减法，见下方 2^64 边界处理）
int rule_p[MAXM];    // rule_p[j] = 第 j 条规则的二进制位编号（0 ~ k-1）
int rule_q[MAXM];    // rule_q[j] = 第 j 条规则对应的饲料编号（1 ~ c）
ull zoo_mask;        // 当前动物园里，哪些二进制位曾经出现过 1
ull bad_mask;        // 新动物这些位必须是 0，否则会引入新饲料
unordered_set<int> bought_feed; // 当前已购买的饲料集合

// 判断 x 的第 p 位是否为 1。
bool has_bit(ull x, int p) {
    return (x >> p) & 1ULL;
}

// 读入所有动物编号，合并为一个位掩码。
void read_animals() {
    zoo_mask = 0;
    for (ull i = 0; i < n; i++) {
        ull x;
        cin >> x;
        zoo_mask |= x;
    }
}

// 读入规则，同时标记哪些饲料已经被购买。
void read_rules() {
    bought_feed.clear();
    bought_feed.reserve((size_t)m * 2 + 5);
    bought_feed.max_load_factor(0.7f);

    for (ll i = 1; i <= m; i++) {
        cin >> rule_p[i] >> rule_q[i];

        // 如果当前动物园里已有动物在第 p 位上是 1，这条规则的饲料一定买过了。
        if (has_bit(zoo_mask, rule_p[i])) {
            bought_feed.insert(rule_q[i]);
        }
    }
}

// 构建禁止位掩码：未买饲料对应的位，新动物不能取 1。
void build_bad_mask() {
    bad_mask = 0;
    for (ll i = 1; i <= m; i++) {
        // 如果第 q 种饲料还没买，新动物一旦在第 p 位取 1 就会触发新饲料。
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
    int free_cnt = (int)k - bad_cnt; // 自由位数（不在禁止掩码中的位）

    // free_cnt == 64 只在 k == 64 且 bad_mask == 0 时出现。
    // 此时总方案数是 2^64，超出 ull 的正向表示范围，需要特殊处理。
    if (free_cnt == 64) {
        if (n == 0) {
            cout << "18446744073709551616\n"; // 2^64
        } else {
            ull ans = 0;
            ans -= n; // 等价于 2^64 - n（ull 回绕）
            cout << ans << '\n';
        }
        return;
    }

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
