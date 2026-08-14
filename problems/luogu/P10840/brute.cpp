/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:01
 * update_at: 2026-08-14 15:20
 */
// brute.cpp：小数据暴力解，直接模拟操作过程：
// 反复寻找相邻不同的位置，删除右元素并把左元素改成"全新值"（当前最大值+1），
// 直到无法操作，统计操作次数。用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int n;
vector<long long> a; // 当前序列

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int ans = 0;
    while (true) {
        // 找第一处相邻不同的位置
        int pos = -1;
        for (int i = 0; i + 1 < (int)a.size(); i++) {
            if (a[i] != a[i + 1]) {
                pos = i;
                break;
            }
        }
        if (pos == -1) break; // 没有相邻不同，无法操作

        // 找当前最大值，构造一个与所有元素都不同的新值
        long long mx = 0;
        for (long long x : a) mx = max(mx, x);

        // 删除 a[pos+1]，把 a[pos] 改成全新值
        a[pos] = mx + 1;
        a.erase(a.begin() + pos + 1);
        ans++;
    }

    cout << ans << '\n';
    return 0;
}
