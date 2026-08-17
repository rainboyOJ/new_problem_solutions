/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

// 判断正整数 x 的二进制表示中 1 和 0 的个数是否相等。
bool is_balanced(unsigned int x) {
    int ones = 0;   // 二进制中 1 的个数
    int zeros = 0;  // 二进制中 0 的个数
    while (x > 0) {
        if (x & 1U) {
            ones++;
        } else {
            zeros++;
        }
        x >>= 1;
    }
    return ones == zeros;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int answer = 0;
    for (int i = 0; i < n; i++) {
        unsigned int value;
        cin >> value;
        if (is_balanced(value)) {
            answer++;
        }
    }
    cout << answer << '\n';
    return 0;
}