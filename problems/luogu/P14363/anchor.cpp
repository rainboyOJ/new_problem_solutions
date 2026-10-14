/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-14 23:06
 * update_at: 2026-10-14 23:06
 */
// anchor.cpp：首个差异对齐，每条规则只检查一个起点。
// 适用于中等数据及所有 q=1 的数据，一般数据下仍需逐询问扫描所有规则。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Rule {
    string a, b;
    ll first_diff; // 规则左右串第一个不同位置，0-based；-1 表示不改变字符
};

ll n, q;
vector<Rule> rules;

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
        if (a.size() != b.size()) {
            cout << 0 << '\n';
            continue;
        }
        ll L = -1, R = -1;
        ll m = a.size();
        for (ll i = 0; i < m; i++) {
            if (a[i] != b[i]) {
                if (L == -1) L = i;
                R = i;
            }
        }
        ll answer = 0;
        if (L != -1) {
            for (ll i = 0; i < n; i++) {
                if (check_rule(rules[i], a, b, L, R)) answer++;
            }
        }
        cout << answer << '\n';
    }
    return 0;
}
