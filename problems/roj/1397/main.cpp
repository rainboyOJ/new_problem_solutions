/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:44
 * update_at: 2026-10-05 12:44
 */

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long ll;

char s[105]; // 输入行

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入整行，保留空格以便定位运算符
    cin.getline(s, sizeof(s));

    ll a = 0, b = 0;
    char op = 0;
    int i = 0;
    int n = strlen(s);

    // 跳过前导空格，解析左运算数
    while (i < n && s[i] == ' ') i++;
    while (i < n && isdigit(s[i])) {
        a = a * 10 + (s[i] - '0');
        i++;
    }

    // 跳过运算符前的空格，取运算符
    while (i < n && s[i] == ' ') i++;
    op = s[i];
    i++;

    // 跳过运算符后的空格，解析右运算数
    while (i < n && s[i] == ' ') i++;
    while (i < n && isdigit(s[i])) {
        b = b * 10 + (s[i] - '0');
        i++;
    }

    ll ans = 0;
    if (op == '+') ans = a + b;
    else if (op == '-') ans = a - b;
    else if (op == '*') ans = a * b;
    else if (op == '/') ans = a / b;
    else if (op == '%') ans = a % b;

    cout << ans << '\n';
    return 0;
}
