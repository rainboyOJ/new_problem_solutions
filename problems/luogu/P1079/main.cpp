/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:20
 * update_at: 2026-11-11 00:20
 */
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string k, c;
    if (!(cin >> k >> c)) return 0;

    int k_len = k.size();
    string m = "";
    m.reserve(c.size());

    for (size_t i = 0; i < c.size(); ++i) {
        // 提取密钥在 0~25 的偏移量
        int shift = tolower(k[i % k_len]) - 'a';

        char orig;
        if (isupper(c[i])) {
            int cur = c[i] - 'A';
            orig = static_cast<char>('A' + (cur - shift + 26) % 26);
        } else {
            int cur = c[i] - 'a';
            orig = static_cast<char>('a' + (cur - shift + 26) % 26);
        }
        m.push_back(orig);
    }

    cout << m << "\n";

    return 0;
}
