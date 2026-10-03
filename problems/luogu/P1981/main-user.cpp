/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 16:10
 * update_at: 2026-10-03 17:05
 */
// main-user.cpp：P1981 表达式求值的另一种写法，走「中缀转后缀 + 扫一遍后缀求值」。
// 这条路线不利用“只有 + 和 *”的特殊结构，换成任意优先级的运算符也能套用；
// 代价是要把表达式切成 token 并存一份后缀，常数比 main.cpp 的加号分段法大。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 运算符最多 1e5 个，切出来的 token 最多 2 * 1e5 + 1 个
const ll MAXL = 200005;
const ll mod = 10000;  // 题目要求只输出最后 4 位

string s;                  // 输入的中缀表达式

string token[MAXL];        // 词法分析结果：数字串或运算符，下标从 1 开始
ll token_cnt;

string postfix[MAXL];      // 后缀表达式，仍然按 token 存（下标从 1 开始）
ll postfix_cnt;

string op_stack[MAXL];     // 调度场算法的运算符栈
ll value_stack[MAXL];      // 求值栈，存放还没有参与运算的操作数

// 判断是不是运算符（本题只有加和乘）
bool is_op(char ch) {
    return ch == '+' || ch == '*';
}

// 判断一个 token 是不是数字串
bool is_number(const string &t) {
    return t[0] >= '0' && t[0] <= '9';
}

// 运算符优先级：'*' 高于 '+'。本题同级从左到右算，所以优先级相等时也要弹栈
ll priority_of(const string &op) {
    if (op == "*") {
        return 2;
    }
    return 1;
}

// 第一步：词法分析。逐字符扫描，把表达式切成数字串和单个运算符。
// 必须先把多位数字看成一个 token，否则后面的转换会把它拆成一个个数字。
void read_tokens() {
    token_cnt = 0;

    for (ll i = 0; i < (ll)s.size();) {
        if (is_op(s[i])) {
            token[++token_cnt] = s.substr(i, 1);
            i++;
        } else {
            ll j = i;
            while (j < (ll)s.size() && !is_op(s[j])) {
                j++;
            }
            token[++token_cnt] = s.substr(i, j - i);
            i = j;
        }
    }
}

// 第二步：调度场算法，中缀表达式 -> 后缀表达式。
// 数字 token 直接追加到结果里；运算符入栈前，先把栈顶那些“应该先算”的弹出来，
// 栈里剩下的就是还没轮到它计算的运算符。
void infix_to_postfix() {
    ll op_top = 0;
    postfix_cnt = 0;

    for (ll i = 1; i <= token_cnt; i++) {
        if (is_number(token[i])) {
            postfix[++postfix_cnt] = token[i];
        } else {
            while (op_top > 0 && priority_of(op_stack[op_top]) >= priority_of(token[i])) {
                postfix[++postfix_cnt] = op_stack[op_top--];
            }
            op_stack[++op_top] = token[i];
        }
    }

    while (op_top > 0) {
        postfix[++postfix_cnt] = op_stack[op_top--];
    }
}

// 把数字串转成数值，边读边对 10000 取模（题目只要求最后 4 位，不必用高精度）
ll string_to_num(const string &t) {
    ll num = 0;
    for (ll i = 0; i < (ll)t.size(); i++) {
        num = (num * 10 + (t[i] - '0')) % mod;
    }
    return num;
}

// 第三步：从左到右扫描后缀表达式求值。
// 后缀里没有括号，运算符出现的顺序就是真正的计算顺序：
// 遇到数字就入栈，遇到运算符就弹出栈顶两个数（先弹出的是右操作数）算完再压回去。
ll evaluate_postfix() {
    ll top = 0;

    for (ll i = 1; i <= postfix_cnt; i++) {
        if (is_number(postfix[i])) {
            value_stack[++top] = string_to_num(postfix[i]);
        } else {
            ll right_num = value_stack[top--];
            ll left_num = value_stack[top--];

            if (postfix[i] == "*") {
                value_stack[++top] = left_num * right_num % mod;
            } else {
                value_stack[++top] = (left_num + right_num) % mod;
            }
        }
    }

    return value_stack[top];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    read_tokens();
    infix_to_postfix();
    ll answer = evaluate_postfix();

    // 取模后的数直接按整数输出，前导 0 不会被打出来
    cout << answer << '\n';
    return 0;
}
