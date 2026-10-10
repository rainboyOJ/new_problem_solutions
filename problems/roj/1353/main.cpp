/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:15
 * update_at: 2026-10-07 15:27
 */
// main.cpp：表达式括号匹配。从左往右扫到 @ 为止，左括号入栈、右括号必须配掉栈顶左括号；
// 中途栈空（右括号多余）或收尾栈非空（左括号多余）都判 NO。与 main.py 同一算法。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const char END_MARK = '@'; // 表达式结束标志，它之后的内容一律不看
const char LEFT_BRACKET = '(';  // 左圆括号：入栈
const char RIGHT_BRACKET = ')';  // 右圆括号：与栈顶左括号配对出栈
const int MAXL = 300; // 表达式长度 < 255；栈里只放左括号，栈深最多 19

char stack_buf[MAXL]; // 栈：从栈底到栈顶依次是还没等到右括号的左括号，全是 '('
ll top;               // 栈内元素个数，栈顶是 stack_buf[top - 1]；top == 0 表示栈空

// 判断 @ 之前的括号是否匹配：前缀中不能出现无左括号可配的右括号，收尾时栈必须为空。
bool is_matched(const string &expr) {
    top = 0;
    ll len = expr.size();
    for (ll i = 0; i < len; i++) {
        char ch = expr[i];
        if (ch == END_MARK) break; // @ 之后的内容一律不看
        if (ch == LEFT_BRACKET) {
            stack_buf[top++] = ch; // 左括号入栈，等一个右括号来配它
        } else if (ch == RIGHT_BRACKET) {
            if (top == 0) return false; // 栈空说明这个右括号没有左括号可配，必错
            top--;                      // 与栈顶左括号配成一对，出栈
        }
    }
    return top == 0; // 收尾栈空才算全部配完；还剩左括号就是左括号多余
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string expr;
    getline(cin, expr); // 整行读入，字母、运算符、括号和空格都原样保留

    cout << (is_matched(expr) ? "YES" : "NO") << "\n";

    return 0;
}
