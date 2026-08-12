/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:10
 * update_at: 2026-08-12 22:10
 */
// brute.cpp：小数据暴力解，直接模拟每次翻转并重新扫描最长交替段，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, q;
int s[MAXN]; // s[i] = 0 表示字符 L，1 表示字符 R

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    // 初始序列全部为 L（0）。
    for (int i = 1; i <= n; i++)
        s[i] = 0;

    while (q--) {
        int x;
        cin >> x;
        // 翻转位置 x：L 变 R，R 变 L。
        s[x] ^= 1;

        // 重新扫描一遍，统计最长「相邻字符互不相同」的连续段长度。
        int ans = 1, cur = 1;
        for (int i = 2; i <= n; i++) {
            if (s[i] != s[i - 1])
                cur++;
            else
                cur = 1;
            if (cur > ans)
                ans = cur;
        }
        cout << ans << '\n';
    }

    return 0;
}
