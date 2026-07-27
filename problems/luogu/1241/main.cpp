/**
 * P1241 括号序列
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

char s[MAXN];       // 原括号字符串
bool match[MAXN];   // match[i] = true 表示位置 i 已配对
int st[MAXN];       // 数组模拟栈，存左括号的下标
int top = 0;        // 栈顶指针

int main() {
    scanf("%s", s);
    int len = strlen(s);
    // 扫描一遍：右括号只看栈顶（最近未匹配左括号）
    for (int i = 0; i < len; ++i) {
        if (s[i] == '(' || s[i] == '[') {
            st[++top] = i; // 左括号入栈
        } else {
            // 栈非空 且 栈顶左括号与当前右括号类型匹配
            if (top && (
                (s[i] == ')' && s[st[top]] == '(') ||
                (s[i] == ']' && s[st[top]] == '[')
            )) {
                match[i] = match[st[top]] = true;
                --top; // 匹配成功，弹栈
            }
            // 类型不匹配 => 当前右括号作废，栈顶左括号继续保留
        }
    }
    // 按原顺序输出
    for (int i = 0; i < len; ++i) {
        if (match[i]) {
            putchar(s[i]);
        } else {
            // 未匹配的括号输出补全的一对
            if (s[i] == '(' || s[i] == ')') printf("()");
            else printf("[]");
        }
    }
    putchar('\n');
    return 0;
}
