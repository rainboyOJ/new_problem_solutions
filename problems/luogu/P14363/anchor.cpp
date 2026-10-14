/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-14 23:06
 * update_at: 2026-10-15 00:05
 */
// anchor.cpp：首个差异对齐，每条规则只检查一个起点。
// 适用于中等数据及所有 q=1 的数据，一般数据下仍需逐询问扫描所有规则。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Rule {
    string a, b;   // 规则的替换前串、替换后串
    ll first_diff; // 规则左右串第一个不同位置，0-based；-1 表示不改变字符
};

ll n, q;
vector<Rule> rules; // 所有规则，编号从 0 开始

// 判断规则 rule 能否在 t1=a 中恰好替换一次得到 t2=b。
// [L, R] 是 a、b 的首尾不同位置；规则若生效，替换起点只能由 L - first_diff 唯一确定。
// 随后要求整个替换区间落在串内、覆盖 R，并且区间内 a 匹配左串、b 匹配右串。
bool check_rule(const Rule &rule, const string &a, const string &b, ll L, ll R) {
    if (rule.first_diff == -1) return false;

    ll len = rule.a.size();
    ll m = a.size();
    ll start = L - rule.first_diff;
    // 起点唯一，且替换区间必须在串内并覆盖最后一个不同位置。
    if (start < 0 || start + len > m || start + len - 1 < R) return false;

    for (ll i = 0; i < len; i++) {
        if (a[start + i] != rule.a[i] || b[start + i] != rule.b[i]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    rules.resize(n);
    // 预处理每条规则的第一个差异位置，供 check_rule 反推唯一替换起点
    for (ll i = 0; i < n; i++) {
        cin >> rules[i].a >> rules[i].b;
        rules[i].first_diff = -1;
        ll len = rules[i].a.size();
        for (ll j = 0; j < len; j++) {
            if (rules[i].a[j] != rules[i].b[j]) {
                rules[i].first_diff = j;
                break;
            }
        }
    }

    while (q--) {
        string a, b;
        cin >> a >> b;
        // 替换不改变长度
        if (a.size() != b.size()) {
            cout << 0 << '\n';
            continue;
        }
        // 先求出询问两串的首尾不同位置 [L, R]
        ll L = -1, R = -1;
        ll m = a.size();
        for (ll i = 0; i < m; i++) {
            if (a[i] != b[i]) {
                if (L == -1) L = i;
                R = i;
            }
        }
        ll answer = 0;
        // L = -1 表示两串完全相同，而题目保证 t1 != t2，答案必为 0
        if (L != -1) {
            for (ll i = 0; i < n; i++) {
                if (check_rule(rules[i], a, b, L, R)) answer++;
            }
        }
        cout << answer << '\n';
    }
    return 0;
}
