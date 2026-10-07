/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:55
 * update_at: 2026-10-06 14:55
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string key;    // 密钥串，长度不超过 100，仅含字母
string cipher; // 密文串，长度不超过 1000，仅含字母，密钥不足时循环使用

// 求单个密文字母的明文：按密文自身大小写解码，'A'/'a' 为 0
char decode_char(char c, char k) {
    int cv = tolower(c) - 'a';          // 密文数值
    int kv = tolower(k) - 'a';          // 密钥数值
    int mv = (cv - kv + 26) % 26;       // 模 26 减法，负数加 26 回到 [0,26)
    char base = isupper(c) ? 'A' : 'a'; // 大小写沿用密文
    char plain_char = base + mv;
    return plain_char;
}

int main() {
    cin >> key >> cipher;

    ll n = key.size();
    ll m = cipher.size();
    string plain;
    // 逐位解密，密钥下标 i % n 实现密钥循环重复使用
    for (ll i = 0; i < m; i++) {
        plain += decode_char(cipher[i], key[i % n]);
    }

    cout << plain << endl;
    return 0;
}
