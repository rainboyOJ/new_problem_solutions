/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

char s[55]; // 原始密码字符串
int n;      // 位移量

int main() {
    cin >> n >> s;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        // 字母编号 0~25，平移 n 位后取模
        int idx = (s[i] - 'a' + n) % 26;
        s[i] = 'a' + idx;
    }
    cout << s;
    return 0;
}
