/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

string s;
int idx;

string decode() {
    string res;
    while (idx < (int)s.size() && s[idx] != ']') {
        if (isupper(s[idx])) { res += s[idx]; idx++; }
        else if (s[idx] == '[') {
            idx++; // 跳过 '['
            int repeat = 0;
            while (isdigit(s[idx])) {
                repeat = repeat * 10 + (s[idx] - '0');
                idx++;
            }
            string inner = decode();
            for (int i = 0; i < repeat; i++) res += inner;
        } else idx++;
    }
    if (idx < (int)s.size() && s[idx] == ']') idx++;
    return res;
}

int main() {
    cin >> s;
    idx = 0;
    cout << decode() << endl;
    return 0;
}
