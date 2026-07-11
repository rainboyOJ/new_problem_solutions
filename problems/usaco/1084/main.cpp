/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:45
 * update_at: 2026-07-11 13:49
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int even_cnt = 0;
    int odd_cnt = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (x % 2 == 0) {
            even_cnt++;
        } else {
            odd_cnt++;
        }
    }

    // 两个奇数可以合成一个偶数组，相当于 odd 减 2，even 加 1。
    while (odd_cnt > even_cnt) {
        odd_cnt -= 2;
        even_cnt++;
    }

    // 偶数组最多只能比奇数组多 1 个，因为照片从偶数组开始交替。
    if (even_cnt > odd_cnt + 1) {
        even_cnt = odd_cnt + 1;
    }

    cout << even_cnt + odd_cnt << '\n';

    return 0;
}
