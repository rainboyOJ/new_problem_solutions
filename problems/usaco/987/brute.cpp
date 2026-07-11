/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:24
 * update_at: 2026-07-11 14:25
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, k;
string word[MAXN]; // 第 i 个单词
vector<string> lines[MAXN];
int line_cnt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> word[i];
    }

    line_cnt = 1;
    int current_len = 0;

    // 朴素模拟：先把单词放进每一行的数组里，最后统一输出。
    for (int i = 1; i <= n; i++) {
        int len = (int)word[i].size();
        if (current_len + len > k) {
            line_cnt++;
            current_len = 0;
        }

        lines[line_cnt].push_back(word[i]);
        current_len += len;
    }

    for (int i = 1; i <= line_cnt; i++) {
        for (int j = 0; j < (int)lines[i].size(); j++) {
            if (j > 0) {
                cout << ' ';
            }
            cout << lines[i][j];
        }
        cout << '\n';
    }

    return 0;
}
