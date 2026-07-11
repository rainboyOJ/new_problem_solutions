/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:40
 * update_at: 2026-07-11 13:44
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

bool can_hear(string alphabet, string heard, int times) {
    string hummed = "";
    for (int i = 1; i <= times; i++) {
        hummed += alphabet;
    }

    int p = 0;
    for (int i = 0; i < (int)hummed.size() && p < (int)heard.size(); i++) {
        if (hummed[i] == heard[p]) {
            p++;
        }
    }
    return p == (int)heard.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string alphabet, heard;
    cin >> alphabet >> heard;

    // 最坏每听到一个字母都需要新唱一遍，所以答案不超过 heard 的长度。
    for (int times = 1; times <= (int)heard.size(); times++) {
        if (can_hear(alphabet, heard, times)) {
            cout << times << '\n';
            return 0;
        }
    }

    return 0;
}
