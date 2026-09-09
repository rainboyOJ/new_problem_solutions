/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 21:26
 * update_at: 2026-08-28 21:26
 */
#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 思路：按压缩规则把压缩串直接展开成完整的旋律字符串，
// 再按下标 c % len 直接取第 c 个音符。展开的长度受小数据限制。

string s;     // 压缩旋律串
long long c;  // 询问的第 c 个音符

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s >> c;

    // 展开：先读一个字母，再把后面连续的数字拼成次数。
    string melody;
    int n = (int)s.length();
    int i = 0;
    while (i < n) {
        char ch = s[i];
        i++;
        long long cnt = 0;
        while (i < n && s[i] >= '0' && s[i] <= '9') {
            cnt = cnt * 10 + (s[i] - '0');
            i++;
        }
        for (long long j = 0; j < cnt; j++) {
            melody.push_back(ch);
        }
    }

    // 无限循环 = 周期重复，取余后直接按下标取音符。
    long long k = c % (long long)melody.length();
    cout << melody[k] << '\n';

    return 0;
}