/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:19
 * update_at: 2026-10-05 05:19
 */
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // 最多 token 数量

char tok[MAXN][32]; // 每个 token
int n;              // token 总数
int pos;            // 当前读取位置

// 递归求值前缀表达式
long double eval_expr() {
    char *s = tok[pos++];
    if (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/') {
        // 当前是运算符，递归求左右两个子表达式的值
        long double left = eval_expr();
        long double right = eval_expr();
        if (s[0] == '+') return left + right;
        if (s[0] == '-') return left - right;
        if (s[0] == '*') return left * right;
        return left / right;
    }
    // 当前是数字，直接返回浮点值
    return strtold(s, NULL);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入所有 token
    while (cin >> tok[n]) {
        ++n;
    }

    pos = 0;
    long double ans = eval_expr();

    cout.setf(ios::fixed);
    cout << setprecision(6) << (double)ans << "\n";
    return 0;
}
