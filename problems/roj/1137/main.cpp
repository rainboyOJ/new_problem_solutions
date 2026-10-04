/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:07
 * update_at: 2026-10-05 03:07
 */

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

typedef long long ll;

string s; // 密文字符串，长度小于 50，只含大小写字母

// 把字符 c 在大小写字母环上循环右移 3 位
char shift_right(char c) {
    if (c >= 'a' && c <= 'z') return (c - 'a' + 3) % 26 + 'a';
    if (c >= 'A' && c <= 'Z') return (c - 'A' + 3) % 26 + 'A';
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> s;

    // 解密按加密逆序撤销：先大小写反转，再逆序，最后循环右移 3
    for (ll i = 0; i < (ll)s.size(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') s[i] = s[i] - 'a' + 'A';
        else s[i] = s[i] - 'A' + 'a';
    }

    reverse(s.begin(), s.end()); // 逆序撤销

    for (ll i = 0; i < (ll)s.size(); i++) s[i] = shift_right(s[i]); // 右移 3

    cout << s << '\n';
    return 0;
}
