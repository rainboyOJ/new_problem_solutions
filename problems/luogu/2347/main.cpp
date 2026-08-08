/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:13
 * update_at: 2026-08-08 23:13
 * 多重背包可行性，bitset
 */
#include <bits/stdc++.h>
using namespace std;

const int maxw = 1005;
int cnt[6];
int w[6] = {1, 2, 3, 5, 10, 20};
bitset<maxw> dp;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    dp[0] = 1;
    for (int i = 0; i < 6; ++i) {
        cin >> cnt[i];
        for (int k = 0; k < cnt[i]; ++k)
            dp |= (dp << w[i]);
    }
    int ans = dp.count() - 1;
    cout << "Total=" << ans << "\n";
    return 0;
}
