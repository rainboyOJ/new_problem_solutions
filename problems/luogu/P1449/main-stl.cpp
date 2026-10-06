/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 00:49
 * update_at: 2026-10-07 01:03
 */
// 这是 STL 写法：操作数直接放进 stack<ll>，读到数字压栈，读到运算符弹出两个操作数算完再压回。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

stack<ll> num_stack; // 操作数栈，栈顶是最近读入的那个操作数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    ll number = 0; // 正在拼的数字，遇到 '.' 时说明这个操作数读完
    ll len = s.size();

    for (ll i = 0; i < len; i++) {
        char ch = s[i];
        if ('0' <= ch && ch <= '9') {
            number = number * 10 + (ch - '0'); // 逐位拼成整数
        } else if (ch == '.') {
            // 数字以 '.' 结尾，把它压入栈顶
            num_stack.push(number);
            number = 0;
        } else if (ch == '@') {
            break; // '@' 表示整个表达式结束
        } else {
            // 先弹出的是右操作数，后弹出的才是左操作数
            ll right = num_stack.top();
            num_stack.pop();
            ll left = num_stack.top();
            num_stack.pop();

            if (ch == '+') {
                num_stack.push(left + right);
            } else if (ch == '-') {
                num_stack.push(left - right);
            } else if (ch == '*') {
                num_stack.push(left * right);
            } else {
                num_stack.push(left / right); // 题目保证除数不为 0，C++ 除法向 0 取整
            }
        }
    }

    // 表达式处理完，栈里只剩一个数，栈顶就是答案
    cout << num_stack.top() << '\n';

    return 0;
}
