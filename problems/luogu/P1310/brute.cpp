/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 01:25
 * update_at: 2026-11-11 01:25
 */

// brute.cpp：小数据暴力枚举每个横线填 0 或 1 验证
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int precedence(char op) {
    if (op == '*') return 2;
    if (op == '+') return 1;
    return 0;
}

int eval(const string& expr, const vector<int>& vals) {
    stack<int> num;
    stack<char> ops;
    size_t val_idx = 0;

    auto pop_op = [&]() {
        char op = ops.top(); ops.pop();
        int r = num.top(); num.pop();
        int l = num.top(); num.pop();
        if (op == '+') num.push(l | r);
        else num.push(l & r);
    };

    for (char ch : expr) {
        if (ch == '_') {
            num.push(vals[val_idx++]);
        } else if (ch == '(') {
            ops.push(ch);
        } else if (ch == ')') {
            while (!ops.empty() && ops.top() != '(') pop_op();
            if (!ops.empty()) ops.pop();
        } else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(ch)) pop_op();
            ops.push(ch);
        }
    }
    while (!ops.empty()) pop_op();
    return num.top();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int l;
    if (!(cin >> l)) return 0;
    string s;
    cin >> s;

    string expr = "";
    if (s.empty()) expr = "_";
    else {
        if (s[0] != '(') expr.push_back('_');
        for (int i = 0; i < l; ++i) {
            expr.push_back(s[i]);
            if (i + 1 < l) {
                char cur = s[i], nxt = s[i + 1];
                if ((cur == '+' || cur == '*') && (nxt == '+' || nxt == '*')) expr.push_back('_');
                else if ((cur == '+' || cur == '*') && nxt == ')') expr.push_back('_');
                else if (cur == '(' && (nxt == '+' || nxt == '*')) expr.push_back('_');
                else if (cur == '(' && nxt == ')') expr.push_back('_');
            }
        }
        if (s.back() != ')') expr.push_back('_');
    }

    int var_count = 0;
    for (char c : expr) if (c == '_') var_count++;

    int ans = 0;
    for (int mask = 0; mask < (1 << var_count); ++mask) {
        vector<int> vals(var_count);
        for (int i = 0; i < var_count; ++i) vals[i] = (mask >> i) & 1;
        if (eval(expr, vals) == 0) ans++;
    }

    cout << (ans % 10007) << "\n";
    return 0;
}
