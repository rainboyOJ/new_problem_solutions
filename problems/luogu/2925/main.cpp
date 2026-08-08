/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:13
 * update_at: 2026-08-08 23:13
 * 01背包可行性，bitset
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 50005;
int c, h;
bitset<maxn> dp;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> c >> h;
    dp[0] = 1;
    for (int i = 1; i <= h; ++i) {
        int v; cin >> v;
        dp |= (dp << v);
    }
    for (int j = c; j >= 0; --j)
        if (dp[j]) { cout << j << "\n"; break; }
    return 0;
}
