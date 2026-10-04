/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 21:36
 * update_at: 2026-10-04 21:36
 */
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

string s;              // 输入的密码串
string bucket[5];      // bucket[1..4] 分别对应小写、大写、数字、其他四类字符

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    // 一次扫描，把字符按 ASCII 区间分到四个桶，append 顺序天然保序
    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        if ('a' <= c && c <= 'z') {
            bucket[1].push_back(c);
        } else if ('A' <= c && c <= 'Z') {
            bucket[2].push_back(c);
        } else if ('0' <= c && c <= '9') {
            bucket[3].push_back(c);
        } else {
            bucket[4].push_back(c);
        }
    }

    int level = 0;
    for (int i = 1; i <= 4; i++) {
        if (!bucket[i].empty()) {
            level++;
        }
    }

    cout << "password level:" << level << "\n";
    for (int i = 1; i <= 4; i++) {
        if (bucket[i].empty()) {
            cout << "(Null)\n";
        } else {
            cout << bucket[i] << "\n";
        }
    }

    return 0;
}
