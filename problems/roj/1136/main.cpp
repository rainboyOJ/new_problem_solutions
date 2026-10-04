/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:07
 * update_at: 2026-10-05 03:07
 */

#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
typedef long long ll;

string s; // 待加密的整行字符串（长度小于 80）

// 对单个字符加密：字母在各自 26 环上右移一位，z/Z 绕回，其他字符不变
char encode(char c) {
    if (c >= 'a' && c <= 'z') return (c - 'a' + 1) % 26 + 'a';
    if (c >= 'A' && c <= 'Z') return (c - 'A' + 1) % 26 + 'A';
    return c;
}

int main() {
    // 用 getline 整行读入，保证空格、标点原样保留
    getline(cin, s);
    ll len = s.size(); // 长度小于 80，用 ll 存下标足够
    for (ll i = 0; i < len; i++) s[i] = encode(s[i]);
    cout << s << "\n";
    return 0;
}
