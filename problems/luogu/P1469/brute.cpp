/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 11:59
 * update_at: 2026-07-19 11:59
 */
#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据朴素解，统计每个长度出现次数的奇偶性。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    map<int, int> parity;
    for (int i = 1; i <= n; i++) {
        int length;
        cin >> length;
        parity[length] ^= 1;
    }

    for (map<int, int>::iterator it = parity.begin(); it != parity.end(); it++) {
        if (it->second == 1) {
            cout << it->first << '\n';
            break;
        }
    }
    return 0;
}
