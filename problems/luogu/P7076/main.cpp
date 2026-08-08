#include <bits/stdc++.h>
using namespace std;

const int MAXM = 1000005;

int n, m, c, k;
int rule_p[MAXM];
int rule_q[MAXM];
unsigned long long zoo_mask;   // 当前动物园里，哪些二进制位曾经出现过 1
unsigned long long bad_mask;   // 新动物这些位必须是 0，否则会引入新饲料
unordered_set<int> bought_feed;

// 判断 x 的第 p 位是否为 1。
bool has_bit(unsigned long long x, int p) {
    return (x >> p) & 1ULL;
}

void read_animals() {
    zoo_mask = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long x;
        cin >> x;
        zoo_mask |= x;
    }
}

void read_rules() {
    bought_feed.clear();
    bought_feed.reserve((size_t)m * 2 + 5);
    bought_feed.max_load_factor(0.7f);

    for (int i = 1; i <= m; i++) {
        cin >> rule_p[i] >> rule_q[i];

        // 如果当前动物园里已经存在某种动物在第 p 位上是 1，
        // 那么这条规则对应的饲料一定已经被买过了。
        if (has_bit(zoo_mask, rule_p[i])) {
            bought_feed.insert(rule_q[i]);
        }
    }
}

void build_bad_mask() {
    bad_mask = 0;

    for (int i = 1; i <= m; i++) {
        // 如果第 q 种饲料现在还没买，那么新动物一旦在第 p 位取 1，
        // 就会触发一份新的饲料清单，于是这种位必须保持为 0。
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
    int free_cnt = k - bad_cnt;

    // free_cnt == 64 只会在 k == 64 且 bad_mask == 0 时出现。
    // 此时总方案数是 2^64，已经超出 unsigned long long 的正向表示范围。
    if (free_cnt == 64) {
        if (n == 0) {
            cout << "18446744073709551616\n";
        } else {
            unsigned long long ans = 0;
            ans -= (unsigned long long)n;  // 等价于 2^64 - n
            cout << ans << '\n';
        }
        return;
    }

    unsigned long long total = 1ULL << free_cnt;
    unsigned long long ans = total - (unsigned long long)n;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> c >> k;
    solve();

    return 0;
}
