/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int n;             // 题目数量
char op;           // 当前运算类型 a/b/c
char line[1005];   // 每行输入

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> line; // 读取第一个 token
        if (line[0] >= 'a' && line[0] <= 'c') {
            op = line[0]; // 有运算符，更新当前类型
            cin >> a >> b;
        } else {
            sscanf(line, "%d", &a); // 第一个 token 是数字
            cin >> b;
        }

        int res;
        char sym;
        if (op == 'a') { res = a + b; sym = '+'; }
        else if (op == 'b') { res = a - b; sym = '-'; }
        else { res = a * b; sym = '*'; }

        // 计算表达式字符串的长度
        char expr[1005];
        sprintf(expr, "%d%c%d=%d", a, sym, b, res);
        cout << expr << "\n" << strlen(expr) << "\n";
    }
    return 0;
}
