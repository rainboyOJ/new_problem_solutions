/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:01
 * update_at: 2026-10-06 16:01
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 表达式计算4：算符优先法（操作数栈 + 运算符栈）从左往右扫一遍
// 处理三个坑：优先级与左结合、一元正负号、多余括号

string str;          // 原始表达式（已去掉所有空白字符）
vector<ll> values;   // 操作数栈
vector<char> ops;    // 运算符栈，'(' 也压在里面

// 运算符优先级：数字越大越先算。'~' 是一元负号，高于 '*' '/' 而低于 '^'，
// 与数学及 C/Python 的习惯一致：-2^2 = -(2^2) = -4，而 (-2)^2 = 4
int level(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '~') return 3;
    if (c == '^') return 4;
    return 0; // 其它字符（'('）不参与优先级比较
}

// 计算 a^b，b >= 0；快速幂写法
ll pow_ll(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

// 结算运算符栈顶：取负号只弹 1 个操作数，二元运算符弹 2 个，孤立的 '(' 只丢弃
void reduce_top() {
    char op = ops.back();
    ops.pop_back();
    if (op == '(') return;              // 多余的左括号：无害跳过
    if (op == '~') {                    // 一元负号
        values.back() = -values.back();
        return;
    }
    ll b = values.back(); values.pop_back();
    ll a = values.back(); values.pop_back();
    ll res;
    if (op == '+') res = a + b;
    else if (op == '-') res = a - b;
    else if (op == '*') res = a * b;
    else if (op == '/') res = a / b;    // C++ 整除本来就向零取整：-7/2 = -3
    else res = pow_ll(a, b);            // '^' 乘方
    values.push_back(res);
}

// 丢掉左边没有 '(' 可配对的右括号，防止"结算到 '('"的循环在空栈上取栈顶崩溃；
// 多余的左括号不用预处理，收尾清栈时自然被跳过
string drop_extra_close() {
    string kept;
    int depth = 0; // 当前未配对的 '(' 个数
    for (size_t i = 0; i < str.size(); i++) {
        char c = str[i];
        if (c == ')' && depth == 0) continue; // 没人能跟它配对，直接删
        if (c == '(') depth++;
        if (c == ')') depth--;
        kept += c;
    }
    return kept;
}

int main() {
    // cin >> 自动跳过空白，把整行表达式拼进 str
    char ch;
    while (cin >> ch) str += ch;

    string s = drop_extra_close();
    size_t n = s.size();

    // 该位置应出现操作数：串首、'(' 之后、运算符之后
    // 此时读到的 '+'/'-' 是一元正负号，而不是二元运算符
    bool expect_operand = true;

    size_t i = 0;
    while (i < n) {
        char c = s[i];
        if (c >= '0' && c <= '9') {         // 读完整个多位数
            ll num = 0;
            while (i < n && s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            values.push_back(num);
            expect_operand = false;
            continue;
        }
        i++;
        if (c == '(') {                     // '(' 压栈，挡住跨括号的比较
            ops.push_back('(');
            expect_operand = true;
        }
        else if (c == ')') {                // 括号内部先算干净，再丢掉配对的 '('
            while (ops.back() != '(') reduce_top();
            ops.pop_back();
            expect_operand = false;
        }
        else if (expect_operand) {          // 操作数位置上的正负号：一元运算符
            if (c == '-') ops.push_back('~');
            // 一元正号不改值，直接忽略
        }
        else {
            // 栈顶优先级 >= 当前运算符说明它先算；取等号让同级从左到右（左结合）
            while (!ops.empty() && ops.back() != '(' && level(ops.back()) >= level(c))
                reduce_top();
            ops.push_back(c);
            expect_operand = true;
        }
    }

    while (!ops.empty()) reduce_top();      // 收尾清空运算符栈
    cout << values.back() << endl;
    return 0;
}
