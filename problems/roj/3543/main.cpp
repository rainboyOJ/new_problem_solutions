/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string s;
int pos;

ll parse_expr(ll x);
ll parse_term(ll x);
ll parse_power(ll x);
ll parse_atom(ll x);

ll parse_expr(ll x) {
    ll value = parse_term(x);
    while (pos < (int)s.size() && (s[pos] == '+' || s[pos] == '-')) {
        char op = s[pos]; pos++;
        ll rhs = parse_term(x);
        value = (op == '+') ? value + rhs : value - rhs;
    }
    return value;
}

ll parse_term(ll x) {
    ll value = parse_power(x);
    while (pos < (int)s.size() && s[pos] == '*') {
        pos++;
        value *= parse_power(x);
    }
    return value;
}

ll parse_power(ll x) {
    ll value = parse_atom(x);
    while (pos < (int)s.size() && s[pos] == '^') {
        pos++;
        ll e = parse_atom(x);
        ll r = 1;
        for (ll i = 0; i < e; i++) r *= value;
        value = r;
    }
    return value;
}

ll parse_atom(ll x) {
    if (s[pos] == 'a') { pos++; return x; }
    if (s[pos] == '(') {
        pos++;
        ll v = parse_expr(x);
        pos++;  // 跳过 ')'
        return v;
    }
    ll num = 0;
    while (pos < (int)s.size() && isdigit((unsigned char)s[pos])) {
        num = num * 10 + (s[pos] - '0');
        pos++;
    }
    return num;
}

ll calc(const string& tokens, ll x) {
    s = tokens;
    // 去掉空格
    string clean;
    for (size_t i = 0; i < tokens.size(); i++)
        if (tokens[i] != ' ') clean.push_back(tokens[i]);
    s = clean;
    pos = 0;
    return parse_expr(x);
}

bool same(const string& expr, const string& other) {
    for (ll x = 0; x < 4; x++)
        if (calc(expr, x) != calc(other, x)) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        // 去掉末尾 \r
        if (!line.empty() && line.back() == '\r') line.pop_back();
        lines.push_back(line);
    }
    // 处理可能带空行；第一行是标准表达式
    int idx = 0;
    while (idx < (int)lines.size() && lines[idx].empty()) idx++;
    string std_expr = lines[idx];
    idx++;
    while (idx < (int)lines.size() && lines[idx].empty()) idx++;
    int n = 0;
    if (idx < (int)lines.size()) n = atoi(lines[idx].c_str());
    idx++;
    string out;
    for (int i = 0; i < n; i++) {
        while (idx < (int)lines.size() && lines[idx].empty()) idx++;
        if (idx >= (int)lines.size()) break;
        if (same(std_expr, lines[idx]))
            out.push_back((char)('A' + i));
        idx++;
    }
    cout << out << "\n";
    return 0;
}
