/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 01:25
 * update_at: 2026-11-11 01:25
 */

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

const int MOD = 10007;

// 状态：dp[0] 为结果为 0 的方案数，dp[1] 为结果为 1 的方案数
struct State {
    int c0;
    int c1;
};

// 合并两个子表达式的状态
State calc(const State& left, const State& right, char op) {
    State res;
    if (op == '+') { // OR 运算
        // 0 + 0 = 0
        res.c0 = (1LL * left.c0 * right.c0) % MOD;
        // 其余情况为 1
        res.c1 = (1LL * left.c1 * right.c0 + 1LL * left.c0 * right.c1 + 1LL * left.c1 * right.c1) % MOD;
    } else if (op == '*') { // AND 运算
        // 至少一个 0 则为 0
        res.c0 = (1LL * left.c0 * right.c0 + 1LL * left.c0 * right.c1 + 1LL * left.c1 * right.c0) % MOD;
        // 1 * 1 = 1
        res.c1 = (1LL * left.c1 * right.c1) % MOD;
    }
    return res;
}

// 运算符优先级：* 高于 +，括号最低
int precedence(char op) {
    if (op == '*') return 2;
    if (op == '+') return 1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int l;
    if (!(cin >> l)) return 0;
    string s;
    cin >> s;

    // 严密补全 '_'
    string expr = "";
    if (s.empty()) {
        expr = "_";
    } else {
        if (s[0] != '(') expr.push_back('_');
        for (int i = 0; i < l; ++i) {
            expr.push_back(s[i]);
            if (i + 1 < l) {
                char cur = s[i];
                char nxt = s[i + 1];
                if ((cur == '+' || cur == '*') && (nxt == '+' || nxt == '*')) expr.push_back('_');
                else if ((cur == '+' || cur == '*') && nxt == ')') expr.push_back('_');
                else if (cur == '(' && (nxt == '+' || nxt == '*')) expr.push_back('_');
                else if (cur == '(' && nxt == ')') expr.push_back('_');
            }
        }
        if (s.back() != ')') expr.push_back('_');
    }

    stack<State> num_stk;
    stack<char> op_stk;

    auto pop_op = [&]() {
        char op = op_stk.top();
        op_stk.pop();
        State r = num_stk.top(); num_stk.pop();
        State l = num_stk.top(); num_stk.pop();
        num_stk.push(calc(l, r, op));
    };

    for (char ch : expr) {
        if (ch == '_') {
            // 叶子操作数：填 0 有 1 种，填 1 有 1 种
            num_stk.push({1, 1});
        } else if (ch == '(') {
            op_stk.push(ch);
        } else if (ch == ')') {
            while (!op_stk.empty() && op_stk.top() != '(') {
                pop_op();
            }
            if (!op_stk.empty() && op_stk.top() == '(') {
                op_stk.pop();
            }
        } else {
            // 操作符 '+' 或 '*'
            while (!op_stk.empty() && precedence(op_stk.top()) >= precedence(ch)) {
                pop_op();
            }
            op_stk.push(ch);
        }
    }

    while (!op_stk.empty()) {
        pop_op();
    }

    cout << (num_stk.empty() ? 0 : num_stk.top().c0) << "\n";

    return 0;
}
