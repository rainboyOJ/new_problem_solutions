/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 00:52
 * update_at: 2026-10-07 01:02
 */
// 这是 STL 写法：用 stack<char> 保存还没配对上的左括号，
// 扫到 ')' 就弹出栈顶配对，扫到 '@' 结束，最后栈空才输出 YES。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string expr;    // 读入的整个表达式，以 '@' 结尾
stack<char> st; // 还没有配对上的左括号：后进先出，弹出的总是最近的那个左括号

// 扫描表达式，判断其中的圆括号是否匹配。
bool brackets_match() {
    ll len = expr.size();
    for (ll i = 0; i < len; i++) {
        if (expr[i] == '@') {
            break; // '@' 是结束符，它后面的字符都不属于表达式
        }
        if (expr[i] == '(') {
            st.push('('); // 左括号压栈，等后面的右括号来配对
        } else if (expr[i] == ')') {
            if (st.empty()) {
                return false; // 栈空说明右括号多了，没有左括号可以配
            }
            st.pop(); // 和最近的那个左括号配掉
        }
    }
    return st.empty(); // 栈空说明没有多余的左括号
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> expr;

    if (brackets_match()) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';
    }

    return 0;
}
