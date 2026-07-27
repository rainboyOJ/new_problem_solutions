/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P1106 删数问题 */
/* 从左到右扫描，如果当前数字比栈顶小，就删除栈顶（贪心：让高位尽量小）。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXL = 255;

char s[MAXL];
int k;
char stk[MAXL]; // 字符栈
int top = 0;    // 栈顶指针

int main() {
    cin >> s >> k;
    int len = strlen(s);

    // 单调栈：尽量让前面的数字小
    for (int i = 0; i < len; i++) {
        // 还可以删除，且栈顶比当前数字大，就弹出栈顶
        while (k > 0 && top > 0 && stk[top] > s[i]) {
            top--;
            k--;
        }
        stk[++top] = s[i];
    }

    // 如果还没删够，从末尾删
    top -= k;

    // 去掉前导零
    int start = 1;
    while (start <= top && stk[start] == '0') start++;

    if (start > top) {
        cout << "0\n";
    } else {
        for (int i = start; i <= top; i++) {
            cout << stk[i];
        }
        cout << "\n";
    }

    return 0;
}
