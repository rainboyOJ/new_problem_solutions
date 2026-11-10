/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 01:15
 * update_at: 2026-11-11 01:15
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string cipher, plain, query;
    if (!(cin >> cipher >> plain >> query)) return 0;

    char c2p[26] = {0}; // 密文到明文
    char p2c[26] = {0}; // 明文到密文

    int n = cipher.size();
    for (int i = 0; i < n; ++i) {
        char c = cipher[i];
        char p = plain[i];

        int cid = c - 'A';
        int pid = p - 'A';

        // 检查密文映射冲突
        if (c2p[cid] != 0 && c2p[cid] != p) {
            cout << "Failed\n";
            return 0;
        }
        // 检查明文映射冲突
        if (p2c[pid] != 0 && p2c[pid] != c) {
            cout << "Failed\n";
            return 0;
        }

        c2p[cid] = p;
        p2c[pid] = c;
    }

    // 检查 26 个字母是否全部映射
    int mapped_count = 0;
    for (int i = 0; i < 26; ++i) {
        if (c2p[i] != 0) {
            mapped_count++;
        }
    }

    if (mapped_count < 26) {
        cout << "Failed\n";
        return 0;
    }

    // 解密待翻译的密文
    string ans = "";
    for (char c : query) {
        ans += c2p[c - 'A'];
    }

    cout << ans << "\n";

    return 0;
}
