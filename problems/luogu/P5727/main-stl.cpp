/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 23:38
 * update_at: 2026-10-06 23:38
 */

// main-stl.cpp：STL 写法，用 vector 保存冰雹序列（长度事先不知道）。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    vector<ll> sequence; // sequence 保存冰雹序列：下标 0 是起始数，最后一个元素一定是 1
    sequence.push_back(n);
    // 按题目规则一直模拟到 1，每一步产生的数都追加到 vector 尾部
    while (n != 1) {
        if (n % 2 == 1)
            n = n * 3 + 1; // 奇数：乘 3 再加 1
        else
            n = n / 2; // 偶数：除以 2
        sequence.push_back(n);
    }

    // 题目要求从最后的 1 开始倒序输出：用下标从 size()-1 递减到 0
    ll len = sequence.size();
    for (ll i = len - 1; i >= 0; i--) {
        cout << sequence[i] << ' ';
    }
    cout << '\n';

    return 0;
}
