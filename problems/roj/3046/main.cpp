/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:32
 * update_at: 2026-10-06 11:32
 */
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 100005; // 字符串长度上限

char s[MAXN];    // 输入的括号序列
int stk[MAXN];   // 栈：存放尚未配对的左括号下标
int top;         // 栈顶指针，栈内元素为 stk[1..top]

// 返回右括号 ch 对应的左括号；若不是右括号则返回 0
char match_left(char ch) {
    if (ch == ')') return '(';
    if (ch == ']') return '[';
    if (ch == '}') return '{';
    return 0;
}

int main() {
    if (scanf("%s", s + 1) != 1) return 0; // 从下标 1 开始读入
    int n = strlen(s + 1);

    int ans = 0;
    int barrier = 0; // 最近一个无法配对的右括号下标，合法子段不能跨过它
    top = 0;
    for (int i = 1; i <= n; i++) {
        char left_ch = match_left(s[i]);
        if (left_ch == 0) {
            // 左括号：下标入栈，等待将来的右括号
            stk[++top] = i;
        } else if (top > 0 && s[stk[top]] == left_ch) {
            // 与栈顶左括号配对：以 i 结尾的合法子段左端紧靠栈内更靠下的
            // 未配对左括号（或断点）
            top--;
            int left = (top > 0) ? stk[top] : barrier;
            if (i - left > ans) ans = i - left;
        } else {
            // 配不上的右括号：成为新断点，之前的左括号因配对不能交叉而全部作废
            top = 0;
            barrier = i;
        }
    }
    printf("%d\n", ans);
    return 0;
}
