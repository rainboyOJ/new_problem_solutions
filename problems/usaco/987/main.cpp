/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:24
 * update_at: 2026-07-11 14:25
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, k;
string word[MAXN]; // 第 i 个单词

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> word[i];
    }

    int current_len = 0; // 当前行已有的非空格字符数量

    for (int i = 1; i <= n; i++) {
        int len = (int)word[i].size();

        if (current_len + len > k) {
            cout << '\n' << word[i];
            current_len = len;
        } else {
            if (current_len > 0) {
                cout << ' ';
            }
            cout << word[i];
            current_len += len;
        }
    }
    cout << '\n';

    return 0;
}
