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

// 暴力版本：对每个字符枚举 26 个候选字符，通过正向加密匹配
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string k, c;
    if (!(cin >> k >> c)) return 0;

    int k_len = k.size();
    string m = "";

    for (size_t i = 0; i < c.size(); ++i) {
        int shift = tolower(k[i % k_len]) - 'a';
        char target = c[i];
        bool found = false;

        if (isupper(target)) {
            for (char cand = 'A'; cand <= 'Z'; ++cand) {
                char enc = static_cast<char>('A' + (cand - 'A' + shift) % 26);
                if (enc == target) {
                    m.push_back(cand);
                    found = true;
                    break;
                }
            }
        } else {
            for (char cand = 'a'; cand <= 'z'; ++cand) {
                char enc = static_cast<char>('a' + (cand - 'a' + shift) % 26);
                if (enc == target) {
                    m.push_back(cand);
                    found = true;
                    break;
                }
            }
        }
    }

    cout << m << "\n";

    return 0;
}
