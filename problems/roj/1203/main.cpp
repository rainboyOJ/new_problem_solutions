/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:27
 * update_at: 2026-10-05 05:28
 */
// main.cpp：括号匹配。栈存尚未配对的左括号下标，"最近的左括号"就是栈顶。

#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

const int MAXN = 105;       // 单行长度 ≤ 100，留 5 个余量
int st[MAXN];               // 栈：尚未配对的左括号下标
int top_;                   // 栈顶指针（用 top_ 避免和 std 冲突）
bool badL[MAXN];            // badL[i] = 第 i 个 '(' 无法配对
bool badR[MAXN];            // badR[i] = 第 i 个 ')' 无法配对

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    // 多组输入，按行读直到 EOF
    while (getline(cin, s)) {
        if ((int)s.size() > MAXN) continue;     // 题目限制外直接跳过
        // 重新初始化当前行的标记
        for (int i = 0; i <= (int)s.size(); ++i) { badL[i] = badR[i] = false; }
        top_ = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            char ch = s[i];
            if (ch == '(') {
                st[++top_] = i;                 // 入栈：当前 '(' 成为最近的未配对左括号
            } else if (ch == ')') {
                if (top_ > 0) {
                    --top_;                     // 与栈顶配对
                } else {
                    badR[i] = true;             // 栈空：右括号失配
                }
            } // 字母不入栈也不打标记
        }
        // 扫描结束仍留在栈里的左括号永远找不到搭档
        while (top_ > 0) { badL[st[top_--]] = true; }
        // 输出原串与标注串
        cout << s << '\n';
        for (int i = 0; i < (int)s.size(); ++i) {
            if (badL[i]) cout << '$';
            else if (badR[i]) cout << '?';
            else cout << ' ';
        }
        cout << '\n';
    }
    return 0;
}
