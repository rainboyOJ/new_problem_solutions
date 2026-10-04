/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:27
 * update_at: 2026-10-05 03:27
 */

// main.cpp：判断字符串是否为回文。输入一整行字符串（无空白），输出 yes / no。
// 做法：双指针从两端向中间扫描，逐对比较字符，任何一对不等则不是回文。

#include <cstring>
#include <iostream>

using namespace std;

typedef long long ll;

const ll MAXN = 105;

char s[MAXN]; // 存读入的字符串（题面 n ≤ 100，开 105 留余）
ll n;         // 字符串实际长度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入一整行；题面保证串内没有空白字符，所以 cin >> s 即可。
    cin >> s;
    n = strlen(s);

    // 双指针 i、j 从两端向中间收缩，逐对比较字符是否相等。
    ll i = 0, j = n - 1;
    while (i < j && s[i] == s[j]) {
        i++;
        j--;
    }

    // i >= j 表示所有对称位都配对成功，是回文；否则不是。
    if (i >= j)
        cout << "yes\n";
    else
        cout << "no\n";

    return 0;
}