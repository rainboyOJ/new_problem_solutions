/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:52
 * update_at: 2026-10-05 11:52
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

typedef long long ll;

char expr[1000005]; // 输入算式
vector<char> ops;   // 运算符栈
vector<ll> nums;    // 后缀求值栈

// 运算符优先级
ll precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// 整数除法，商向零截断
ll trunc_div(ll left, ll right) {
    ll quotient = abs(left) / abs(right);
    if ((left < 0) != (right < 0)) return -quotient;
    return quotient;
}

// 执行一次二元运算，先弹出的是右操作数
ll calc(char op, ll left, ll right) {
    if (op == '+') return left + right;
    if (op == '-') return left - right;
    if (op == '*') return left * right;
    if (op == '/') return trunc_div(left, right);
    ll result = 1;
    for (ll i = 0; i < right; i++) result *= left; // 幂次很小，直接乘
    return result;
}

// 弹出栈顶算子并归约
void pop_op() {
    char op = ops.back();
    ops.pop_back();
    ll right = nums.back(); nums.pop_back();
    ll left = nums.back(); nums.pop_back();
    nums.push_back(calc(op, left, right));
}

int main() {
    scanf("%s", expr);
    ll len = strlen(expr);
    ll num = 0;
    bool has_num = false;
    for (ll i = 0; i < len; i++) {
        char ch = expr[i];
        if (ch >= '0' && ch <= '9') {
            num = num * 10 + (ch - '0');
            has_num = true;
            continue;
        }
        if (has_num) {
            nums.push_back(num);
            has_num = false;
            num = 0;
        }
        if (ch == '(') {
            ops.push_back(ch);
        } else if (ch == ')') {
            while (ops.back() != '(') pop_op(); // 弹到左括号
            ops.pop_back(); // 丢掉左括号
        } else { // + - * / ^
            while (!ops.empty() && ops.back() != '(' &&
                   precedence(ops.back()) >= precedence(ch)) {
                pop_op(); // 先算优先级更高或同级的
            }
            ops.push_back(ch);
        }
    }
    if (has_num) nums.push_back(num);
    while (!ops.empty()) pop_op();
    printf("%lld\n", nums.back());
    return 0;
}
