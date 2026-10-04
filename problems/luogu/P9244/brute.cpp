/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 11:36
 * update_at: 2026-10-03 11:36
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接按定义枚举所有子串：左端点 i、右端点 j，
// 只要长度 j - i + 1 >= K 且 s[i] == c1 且 s[j] == c2 就计数。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5005;

int K;
int n;
char s[maxn];
char c1, c2;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> K;
    cin >> (s + 1) >> c1 >> c2;
    n = (int)strlen(s + 1);

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (j - i + 1 < K) {
                continue; // 长度不够，不配使用简写
            }
            if (s[i] == c1 && s[j] == c2) {
                ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
