/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 20:19
 * update_at: 2026-10-01 20:39
 */
// brute.cpp：小数据暴力解，逐个构造根到结点的括号串，再枚举所有子串检查是否合法。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;   // 暴力只用于小数据对拍，n 取到 100 左右

int n;
char bracket_char[MAXN];   // bracket_char[u]：结点 u 上的括号
int parent_node[MAXN];     // parent_node[u]：u 的父亲，根结点 1 的父亲记为 0

// 判断 s[l..r] 是否为合法括号串：任意前缀和非负，且最终总和为 0。
bool is_valid(const string &s, ll l, ll r) {
    ll balance = 0;
    for (ll i = l; i <= r; i++) {
        if (s[i] == '(') {
            balance++;
        } else {
            balance--;
        }
        if (balance < 0) {
            return false;
        }
    }
    return balance == 0;
}

// 拼出根到结点 u 的括号串：先按 u 到根的顺序取字符，再整体反转。
string build_path_string(int u) {
    string path_string;
    while (u != 0) {
        path_string.push_back(bracket_char[u]);
        u = parent_node[u];
    }
    reverse(path_string.begin(), path_string.end());
    return path_string;
}

// 枚举 s 的所有子串，统计其中合法括号串的个数。
ll count_valid_substrings(const string &s) {
    ll len = s.size();
    ll count_answer = 0;
    for (ll l = 0; l < len; l++) {
        for (ll r = l; r < len; r++) {
            if (is_valid(s, l, r)) {
                count_answer++;
            }
        }
    }
    return count_answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> (bracket_char + 1);   // 直接读到下标 1 开始，和结点编号对齐
    for (int i = 2; i <= n; i++) {
        cin >> parent_node[i];
    }

    ll answer = 0;
    for (int u = 1; u <= n; u++) {
        string path_string = build_path_string(u);
        ll k_u = count_valid_substrings(path_string);
        answer ^= u * k_u;
    }

    cout << answer << '\n';
    return 0;
}
