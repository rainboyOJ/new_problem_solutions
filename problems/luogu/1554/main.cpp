/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int cnt[10]; // cnt[d] 记录数字 d 出现的次数
int m, n;

int main() {
    cin >> m >> n;
    for (int x = m; x <= n; x++) {
        int t = x;
        // 不断取最低位，统计数码
        while (t) {
            cnt[t % 10]++;
            t /= 10;
        }
    }
    for (int i = 0; i <= 9; i++) cout << cnt[i] << " ";
    return 0;
}
