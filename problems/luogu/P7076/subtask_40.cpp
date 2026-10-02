/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:31
 * update_at: 2026-10-01 22:31
 */
// subtask_40.cpp：40% 数据 k ≤ 20，枚举所有 2^k 只动物逐只判断。
// 时间 O(2^k · m)，空间 O(n + m)。覆盖 20% 和 40% 两档。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

ll n, m, c, k;
vector<ull> animals;
vector<int> rule_p;
vector<int> rule_q;
unordered_set<ull> exist_animal;
unordered_set<int> current_feed;

bool has_bit(ull x, int p) {
    return (x >> p) & 1ULL;
}

// 枚举所有动物和规则，算出当前已购买的饲料。
void build_current_feed() {
    current_feed.clear();
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (has_bit(animals[i], rule_p[j])) {
                current_feed.insert(rule_q[j]);
            }
        }
    }
}

// 判断新动物 x 能否加入：不触发任何"当前还没买"的饲料规则。
bool can_add(ull x) {
    for (ll j = 0; j < m; j++) {
        if (has_bit(x, rule_p[j]) && current_feed.find(rule_q[j]) == current_feed.end()) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> c >> k;

    animals.resize(n);
    for (ll i = 0; i < n; i++) {
        cin >> animals[i];
        exist_animal.insert(animals[i]);
    }

    rule_p.resize(m);
    rule_q.resize(m);
    for (ll i = 0; i < m; i++) {
        cin >> rule_p[i] >> rule_q[i];
    }

    build_current_feed();

    // 枚举所有编号，跳过已饲养的，统计能加入的。
    ull limit = 1ULL << k;
    ull ans = 0;
    for (ull x = 0; x < limit; x++) {
        if (exist_animal.find(x) != exist_animal.end()) {
            continue;
        }
        if (can_add(x)) {
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
