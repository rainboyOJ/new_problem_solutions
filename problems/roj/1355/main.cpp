/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:53
 * update_at: 2026-10-05 11:53
 */

#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXL = 260; // 每行字符串长度不超过 255，多留一点余量

char s[MAXL]; // 当前读入的括号串
int stk[MAXL]; // 栈：从底到顶存未闭合左括号的编号，正好是从外到内的嵌套顺序
int top; // 栈顶指针（栈内元素个数）

// 把括号字符映射成编码；返回 -1 表示不是括号（本题不会出现）。
int get_level(char c) {
    if (c == '{') return 0;
    if (c == '[') return 1;
    if (c == '(') return 2;
    if (c == '<') return 3;
    if (c == '}') return 4;
    if (c == ']') return 5;
    if (c == ')') return 6;
    return 7; // '>'
}

// 判断一个括号串是否合法：既要两两配对，又要内层优先级不低于外层
bool check() {
    top = 0; // 每个串开始前清空栈
    ll len = strlen(s);
    for (ll i = 0; i < len; ++i) {
        int code = get_level(s[i]);
        if (code < 4) { // 左括号
            // 新左括号只能插在最内层：编号小于栈顶说明它比当前最内层还靠外，非法
            if (top > 0 && code < stk[top - 1])
                return false;
            stk[top++] = code;
        } else { // 右括号
            if (top == 0) // 没有可配对的左括号
                return false;
            --top;
            if (code - stk[top] != 4) // 与弹出的左括号不同种
                return false;
        }
    }
    return top == 0; // 还留着没闭合的左括号时栈非空
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s); // 括号串不含空白，用 %s 读即可
        if (check())
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
