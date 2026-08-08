/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

char s[105];   // 单词
int cnt[26];   // cnt[i] 记录字母 'a'+i 出现的次数

// 判断一个数是否为质数
bool is_prime(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) return false;
    return true;
}

int main() {
    cin >> s;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        cnt[s[i] - 'a']++;
    }
    // 找最大和最小出现次数（只考虑出现过的字母）
    int maxn = 0, minn = 100;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] > 0) {
            if (cnt[i] > maxn) maxn = cnt[i];
            if (cnt[i] < minn) minn = cnt[i];
        }
    }
    int diff = maxn - minn;
    if (is_prime(diff)) {
        cout << "Lucky Word\n" << diff;
    } else {
        cout << "No Answer\n0";
    }
    return 0;
}
